#include "Engine.h"

namespace Engine {

	ERenderer* ERenderer::s_Instance = nullptr;


	void CreateDefaults()
	{
		



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
		ERenderContext::s_Instance->SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		ERenderContext::s_Instance->Clear();

        s_Instance->fViewProjectionMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
		s_Instance->fCameraPosition = camera->GetPosition();
		//Make that better
		s_Instance->fLightMap.clear();
		s_Instance->fLightMap = lightMap;
	}

	void ERenderer::Draw(const ERef<EVertexArray>& vertexArray, const ERef<EShader>& shader)
	{
        if (!s_Instance)
		{
			std::cout << "No render instance set. Cant draw anything" << std::endl;
			return;
		}


		shader->Bind();
		shader->SetUniformMat4("vp_matrix", s_Instance->fViewProjectionMatrix);
		vertexArray->Bind();

		u32 indexCount = vertexArray->GetIndexBuffer()->GetCount();
		IN_RENDER1(indexCount, {
			glCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL));
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
