#include "Engine.h"

namespace Engine {

	ERenderer* ERenderer::s_Instance = nullptr;

	void CreateDefaults()
	{
		EString vertexSource = R"(#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Binormal;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out VertexOutput
{
	vec3 WorldPosition;
    vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
} vs_Output;

void main()
{
	vs_Output.WorldPosition = vec3(mat4(u_ModelMatrix) * vec4(a_Position, 1.0));
    vs_Output.Normal = a_Normal;
	vs_Output.TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
	vs_Output.WorldNormals = mat3(u_ModelMatrix) * mat3(a_Tangent, a_Binormal, a_Normal);

	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}
		)";

		EString fragmentSource = R"(#version 430 core

const float PI = 3.141592;
const float Epsilon = 0.00001;
const float TO_RADIANS = (PI / 180.0);

const int LightCount = 1;

// Constant normal incidence Fresnel factor for all dielectrics.
const vec3 Fdielectric = vec3(0.04);

struct Light {
	vec3 Direction;
	vec3 Radiance;
};

in VertexOutput
{
	vec3 WorldPosition;
    vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
} vs_Input;

layout(location=0) out vec4 color;

uniform Light lights;
uniform vec3 u_CameraPosition;

// PBR texture inputs
uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_MetalnessTexture;
uniform sampler2D u_RoughnessTexture;

// Environment maps
uniform samplerCube u_EnvRadianceTex;
uniform samplerCube u_EnvIrradianceTex;

// BRDF LUT
uniform sampler2D u_BRDFLUTTexture;

uniform vec3 u_AlbedoColor;
uniform float u_Metalness;
uniform float u_Roughness;

uniform float u_EnvMapRotation;

// Toggles
uniform float u_RadiancePrefilter;
uniform bool u_AlbedoTexToggle;
uniform bool u_NormalTexToggle;
uniform bool u_MetalnessTexToggle;
uniform bool u_RoughnessTexToggle;

struct PBRParameters
{
	vec3 Albedo;
	float Roughness;
	float Metalness;

	vec3 Normal;
	vec3 View;
	float NdotV;
};

PBRParameters fParams;

// GGX/Towbridge-Reitz normal distribution function.
// Uses Disney's reparametrization of alpha = roughness^2
float ndfGGX(float cosLh, float roughness)
{
	float alpha = roughness * roughness;
	float alphaSq = alpha * alpha;

	float denom = (cosLh * cosLh) * (alphaSq - 1.0) + 1.0;
	return alphaSq / (PI * denom * denom);
}

// Single term for separable Schlick-GGX below.
float gaSchlickG1(float cosTheta, float k)
{
	return cosTheta / (cosTheta * (1.0 - k) + k);
}

// Schlick-GGX approximation of geometric attenuation function using Smith's method.
float gaSchlickGGX(float cosLi, float NdotV, float roughness)
{
	float r = roughness + 1.0;
	float k = (r * r) / 8.0; // Epic suggests using this roughness remapping for analytic lights.
	return gaSchlickG1(cosLi, k) * gaSchlickG1(NdotV, k);
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// Shlick's approximation of the Fresnel factor.
vec3 fresnelSchlick(vec3 F0, float cosTheta)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(vec3 F0, float cosTheta, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
} 

// ---------------------------------------------------------------------------------------------------
// The following code (from Unreal Engine 4's paper) shows how to filter the environment map
// for different roughnesses. This is mean to be computed offline and stored in cube map mips,
// so turning this on online will cause poor performance
float RadicalInverse_VdC(uint bits) 
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), RadicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX(vec2 Xi, float Roughness, vec3 N)
{
	float a = Roughness * Roughness;
	float Phi = 2 * PI * Xi.x;
	float CosTheta = sqrt( (1 - Xi.y) / ( 1 + (a*a - 1) * Xi.y ) );
	float SinTheta = sqrt( 1 - CosTheta * CosTheta );
	vec3 H;
	H.x = SinTheta * cos( Phi );
	H.y = SinTheta * sin( Phi );
	H.z = CosTheta;
	vec3 UpVector = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
	vec3 TangentX = normalize( cross( UpVector, N ) );
	vec3 TangentY = cross( N, TangentX );
	// Tangent to world space
	return TangentX * H.x + TangentY * H.y + N * H.z;
}

float TotalWeight = 0.0;

vec3 PrefilterEnvMap(float Roughness, vec3 R)
{
	vec3 N = R;
	vec3 V = R;
	vec3 PrefilteredColor = vec3(0.0);
	int NumSamples = 1024;
	for(int i = 0; i < NumSamples; i++)
	{
		vec2 Xi = Hammersley(i, NumSamples);
		vec3 H = ImportanceSampleGGX(Xi, Roughness, N);
		vec3 L = 2 * dot(V, H) * H - V;
		float NoL = clamp(dot(N, L), 0.0, 1.0);
		if (NoL > 0)
		{
			PrefilteredColor += texture(u_EnvRadianceTex, L).rgb * NoL;
			TotalWeight += NoL;
		}
	}
	return PrefilteredColor / TotalWeight;
}

// ---------------------------------------------------------------------------------------------------

vec3 RotateVectorAboutY(float angle, vec3 vec)
{
    angle = radians(angle);
    mat3x3 rotationMatrix ={vec3(cos(angle),0.0,sin(angle)),
                            vec3(0.0,1.0,0.0),
                            vec3(-sin(angle),0.0,cos(angle))};
    return rotationMatrix * vec;
}

vec3 Lighting(vec3 F0)
{
	vec3 result = vec3(0.0);
	for(int i = 0; i < LightCount; i++)
	{
		vec3 Li = -(lights.Direction * TO_RADIANS);
		vec3 Lradiance = lights.Radiance;
		vec3 Lh = normalize(Li + fParams.View);

		// Calculate angles between surface normal and various light vectors.
		float cosLi = max(0.0, dot(fParams.Normal, Li));
		float cosLh = max(0.0, dot(fParams.Normal, Lh));

		vec3 F = fresnelSchlick(F0, max(0.0, dot(Lh, fParams.View)));
		float D = ndfGGX(cosLh, fParams.Roughness);
		float G = gaSchlickGGX(cosLi, fParams.NdotV, fParams.Roughness);

		vec3 kd = (1.0 - F) * (1.0 - fParams.Metalness);
		vec3 diffuseBRDF = kd * fParams.Albedo;

		// Cook-Torrance
		vec3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * fParams.NdotV);

		result += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
	}
	return result;
}

vec3 IBL(vec3 F0, vec3 Lr)
{
	vec3 irradiance = texture(u_EnvIrradianceTex, fParams.Normal).rgb;
	vec3 F = fresnelSchlickRoughness(F0, fParams.NdotV, fParams.Roughness);
	vec3 kd = (1.0 - F) * (1.0 - fParams.Metalness);
	vec3 diffuseIBL = fParams.Albedo * irradiance;

	int u_EnvRadianceTexLevels = textureQueryLevels(u_EnvRadianceTex);
	float NoV = clamp(fParams.NdotV, 0.0, 1.0);
	vec3 R = 2.0 * dot(fParams.View, fParams.Normal) * fParams.Normal - fParams.View;
	vec3 specularIrradiance = vec3(0.0);

	if (u_RadiancePrefilter > 0.5)
		specularIrradiance = PrefilterEnvMap(fParams.Roughness * fParams.Roughness, R) * u_RadiancePrefilter;
	else
		specularIrradiance = textureLod(u_EnvRadianceTex, RotateVectorAboutY(u_EnvMapRotation, Lr), sqrt(fParams.Roughness) * u_EnvRadianceTexLevels).rgb * (1.0 - u_RadiancePrefilter);

	// Sample BRDF Lut, 1.0 - roughness for y-coord because texture was generated (in Sparky) for gloss model
	vec2 specularBRDF = texture(u_BRDFLUTTexture, vec2(fParams.NdotV, 1.0 - fParams.Roughness)).rg;
	vec3 specularIBL = specularIrradiance * (F * specularBRDF.x + specularBRDF.y);

	return kd * diffuseIBL + specularIBL;
}

void main()
{
	// Standard PBR inputs
	fParams.Albedo = u_AlbedoTexToggle ? texture(u_AlbedoTexture, vs_Input.TexCoord).rgb : u_AlbedoColor; 
	fParams.Metalness = u_MetalnessTexToggle ? texture(u_MetalnessTexture, vs_Input.TexCoord).r : u_Metalness;
	fParams.Roughness = u_RoughnessTexToggle ?  texture(u_RoughnessTexture, vs_Input.TexCoord).r : u_Roughness;
    fParams.Roughness = max(fParams.Roughness, 0.05); // Minimum roughness of 0.05 to keep specular highlight

	// Normals (either from vertex or map)
	fParams.Normal = normalize(vs_Input.Normal);
	if (u_NormalTexToggle)
	{
		fParams.Normal = normalize(2.0 * texture(u_NormalTexture, vs_Input.TexCoord).rgb - 1.0);
		fParams.Normal = normalize(vs_Input.WorldNormals * fParams.Normal);
	}

	fParams.View = normalize(u_CameraPosition - vs_Input.WorldPosition);
	fParams.NdotV = max(dot(fParams.Normal, fParams.View), 0.0);
		
	// Specular reflection vector
	vec3 Lr = 2.0 * fParams.NdotV * fParams.Normal - fParams.View;

	// Fresnel reflectance, metals use albedo
	vec3 F0 = mix(Fdielectric, fParams.Albedo, fParams.Metalness);

	vec3 lightContribution = Lighting(F0);
	vec3 iblContribution = IBL(F0, Lr);

	color = vec4(lightContribution + iblContribution, 1.0);
}
		)";

		/*Shader::DefaultShader = Shader::Create(vertexSource, fragmentSource);
		Material::DefaultMaterial = std::shared_ptr<Material>(new Material(Shader::DefaultShader));*/
	}

	void ERenderer::Init()
	{
		s_Instance = new ERenderer();

		CreateDefaults();
	}

	void ERenderer::Begin(const ERef<ECamera>& camera, const ELightMap& lightMap)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT(camera, "Set a Camera to Render properly");
		IN_RENDER({
		//Engine::ERendererAPI::s_Instance->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		//ERendererAPI::s_Instance->Clear();
			})


		s_Instance->fViewProjectionMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
		s_Instance->fCameraPosition = camera->GetPosition();
		//Make that better
		s_Instance->fLightMap.clear();
		s_Instance->fLightMap = lightMap;
	}

	void ERenderer::Draw(const ERef<EVertexArray>& vertexArray)
	{
		vertexArray->Bind();

		u32 indexCount = vertexArray->GetIndexBuffer()->GetCount();
		IN_RENDER1(indexCount, {
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
		})
	}

	void ERenderer::End()
	{
	}

/*
	void ERenderer::Draw(MeshInstance* mesh, MaterialInstance* material, const glm::mat4& modelMatrix)
	{
		IN_CORE_ASSERT(s_Instance, "No Renderer instance set!"); //Forgot to call Renderer::Init(); ?
		IN_CORE_ASSERT(mesh, "Mesh not valid");
		IN_CORE_ASSERT(s_Instance->fLightMap.size() > 0, "No lights set for the scene!");
		//IN_CORE_ASSERT(mesh->UsedMaterial, "Pls provide a Material for the model!");
		if (!material)
		{
			static bool warningShows = false;
			if (!warningShows)
				IN_CORE_WARN("Pls provide a Material fdor the model!");
			warningShows = true;
			return;
		}

		//Clean this up!

		std::weak_ptr<Shader> shader = material->GetShaderProgram();
		if (shader.expired()) return;

		shader.lock()->SetUniformBuffer("u_ViewProjectionMatrix", (byte*)&s_Instance->fViewProjectionMatrix[0][0], sizeof(float) * 4 * 4);
		shader.lock()->SetUniformBuffer("u_ModelMatrix", (byte*)&modelMatrix[0][0], sizeof(float) * 4 * 4);
		shader.lock()->SetUniformBuffer("lights", (byte*) &s_Instance->fLightMap[0], sizeof(Light));
		shader.lock()->SetUniformBuffer("u_CameraPosition", (byte*)&s_Instance->fCameraPosition, sizeof(EVec3));
		
		shader.lock()->SetUniform3f("lights.Direction", s_Instance->fLightMap[0].Direction * TO_RADIANS);
		material->Bind();

		mesh->GetVertexArray()->Bind();
		u32 vertexCount = mesh->GetVertexCount();
		IN_RENDER1(vertexCount, {
				RendererAPI::s_Instance->DrawIndexed(vertexCount);
			})
	}
*/
	void ERenderer::WaitAndRender()
	{
		if (s_Instance)
		{
			s_Instance->fCommandQueue.Execute();
		}
	}

}
