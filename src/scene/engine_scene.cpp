#include "Engine.h"

using namespace Engine;


const char* vertex_shader_src = ""
"#version 330 core\n"

"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec2 texCoord;\n"

"uniform mat4 vp_matrix = mat4(1.0);\n"

"out vec2 UVS;\n"
"out vec3 TransNormals;\n"

"void main()\n"
"{\n"

    "gl_Position = vp_matrix * vec4(position, 1.0);\n"
    "UVS = texCoord;\n"
    "TransNormals = normal;\n"
"}\n"
"";

const char* fragment_shader_src = ""
"#version 330 core\n"

"in vec2 UVS;\n"
"in vec3 TransNormals;\n"

"out vec4 FinalColor;\n"

"void main()\n"
"{\n"
    "FinalColor = vec4((TransNormals.x + 1) / 2, (TransNormals.y + 1) / 2, (TransNormals.z + 1) / 2, 1.0);\n"
"}\n"
"";

EScene::EScene(const EString& name)
    : fActiveCamera(nullptr), fSceneFrameBuffer(nullptr), fName(name), fViewPortWidth(1270), fViewPortHeight(720)

{
    fShader = EShader::Create(vertex_shader_src, fragment_shader_src);
}

EScene::~EScene()
{
}

void EScene::Render()
{
    if (!fActiveCamera) { std::cout << "No active camera set to scene!" << std::endl; return; }

    if (!fSceneFrameBuffer)
    {
        fSceneFrameBuffer = EFrameBuffer::Create(fViewPortWidth, fViewPortHeight, EFramebufferFormat::RGBA8);
    }
    fSceneFrameBuffer->Resize(fViewPortWidth, fViewPortHeight);

    fSceneFrameBuffer->Bind();
    
    // Render components
    ERenderer::Begin(fActiveCamera, {});
    auto view = fRegistry.view<EMeshComponent>();
    for (EEntity entity : view)
    {
        EMeshComponent meshComponent = view.get<EMeshComponent>(entity);
        if (meshComponent.Mesh)
        {
            ERenderer::Draw(meshComponent.Mesh->fVertexArray, fShader);
        }

    }
    ERenderer::End();

    fSceneFrameBuffer->Unbind();
}

void EScene::RenderUI()
{
    if (!fActiveCamera)
    {
        ImGui::Begin("No Camera##NOCAM");
        ImGui::Text("No active camera set to scene \"%s\"\n", fName.c_str());
        ImGui::End();
    }


    ImGui::Begin("SceneView##SCENEVIEW");
    // Render frame buffer
    auto viewportSize = ImGui::GetContentRegionAvail();
    fViewPortWidth = viewportSize.x;
    fViewPortHeight = viewportSize.y;
    
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fSceneFrameBuffer->GetColorAttachment());
    ImGui::Image((void*)(u64)fSceneFrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });
    fActiveCamera->UpdateImGui();

    glBindTexture(GL_TEXTURE_2D, 0);
    ImGui::End();

    // Render all objects for now
    ImGui::Begin("SceneTree");
    fRegistry.each([this](EEntity handle)
    {
        EObject object(handle, this);
        if (object.HasComponent<ENameComponent>())
        {
            ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
            ImGui::Selectable(nameComponent.Name.c_str());
        }
        else
        {
            ImGui::Selectable("Unknown");
        }
    });
    ImGui::End();
}

void EScene::Update(float delta)
{
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    return object;
}

void EScene::SetActiveCamera(const ERef<ECamera>& camera)
{
    fActiveCamera = camera;
}

const ERef<ECamera>& EScene::GetActiveCamera() const
{
    return fActiveCamera;
}
