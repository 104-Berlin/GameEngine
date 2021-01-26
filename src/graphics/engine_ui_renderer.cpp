#include "Engine.h"

using namespace Engine;


const char* fragment_shader =
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "uniform sampler2D Texture;\n"
        "layout (location = 0) out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

const char* vertex_shader =
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "uniform mat4 ProjMtx;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";


void Render_Window(ImGuiViewport* vp, void* data)
{
    // Data shoulw be the current UIRenderer
}


 
EUIRenderer::EUIRenderer() 
{
    
}

void EUIRenderer::Init(ERef<EWindow> window) 
{
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "104-engine";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

    ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
    platform_io.Renderer_RenderWindow = &Render_Window;
    CreateRenderingStorage();
}

void EUIRenderer::Begin() 
{
}

void EUIRenderer::Render() 
{
    
}

void EUIRenderer::End() 
{
    
}

void EUIRenderer::CreateRenderingStorage() 
{
    fVertexArray = EVertexArray::Create();
    fVertexBuffer = EVertexBuffer::Create(nullptr, 0);

    fShader = EShader::Create(vertex_shader, fragment_shader);

    CreateFontAtlas();
}

void EUIRenderer::CreateFontAtlas() 
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    fFontTexture = ETexture2D::Create(ETextureFormat::RGBA, width, height);
    IN_RENDER_S({
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->TexID = (ImTextureID)(intptr_t)self->fFontTexture->GetRendererID();
    });

    fFontTexture->SetTextureData(pixels, width, height);
}

void EUIRenderer::RenderWindow(ImGuiViewport* viewport, void* data) 
{
    
}
