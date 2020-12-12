#include "Engine.h"

using namespace Engine;


static EVector<ESprite::EVertex> sprite_vertex_data = {
    {{-0.5f,  0.5f},   {0.0f, 0.0f}},
    {{-0.5f, -0.5f},   {0.0f, 1.0f}},
    {{ 0.5f, -0.5f},   {1.0f, 1.0f}},
    {{ 0.5f,  0.5f},   {1.0f, 0.0f}}
};

static EVector<u32> sprite_index_data = {
    0, 1, 2,
    2, 3, 0  
};


ESprite::ESprite(const EString& name, const EString& path)
    : EResource(name, path)
{
    fTexture = nullptr;
}

ESprite::~ESprite()
{
    if (fVertexArray) { delete fVertexArray; }
    if (fVertexBuffer) { delete fVertexBuffer; }
    if (fIndexBuffer) { delete fIndexBuffer; }
}

void ESprite::Draw()
{
    if (fTexture)
    {
        fTexture->Bind(0);
    }

    ERenderer::Draw(fVertexArray);
}

bool ESprite::OnLoad()
{
    EResource::OnLoad();

    fVertexArray = EVertexArray::Create();
    fVertexBuffer = EVertexBuffer::Create(sprite_vertex_data.data(), sprite_vertex_data.size() * sizeof(ESprite::EVertex));
    fIndexBuffer = EIndexBuffer::Create(sprite_index_data.data(), sprite_index_data.size());

    EBufferLayout layout{   EBufferElement(EShaderDataType::Float2, "Position", false),
                            EBufferElement(EShaderDataType::Float2, "TexCoords", false)};
    

    fVertexBuffer->SetLayout(layout);

    fVertexArray->AddVertexBuffer(fVertexBuffer);
    fVertexArray->SetIndexBuffer(fIndexBuffer);

    fTexture = ETexture2D::Create(fFilePath.GetValue());
    
    return true;
}

bool ESprite::OnImport()
{
    return false;
}
