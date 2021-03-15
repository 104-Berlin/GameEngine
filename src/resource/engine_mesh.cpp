#include "Engine.h"

using namespace Engine;

EMesh::EMesh(const EString& path)
    : EResource(path), fVertexArray(nullptr)
{

}

EMesh::EMesh(const EString& name, const EVector<EVertex>& vertices, const EVector<u32>& indices)
    : EResource("res/intern/" + name), fVertexArray(nullptr)
{
    Create(vertices, indices);
}

EMesh::~EMesh()
{

}

void EMesh::Create(const EVector<EVertex>& vertices, const EVector<u32>& indices)
{
    fVertexArray = EVertexArray::Create();
    ERef<EVertexBuffer> vb = EVertexBuffer::Create(ESharedBuffer().InitWith<EVertex>((void*)vertices.data(), vertices.size() * sizeof(EVertex)));
    EBufferLayout layout = { EBufferElement(EShaderDataType::Float3, "POSITION"),
                            EBufferElement(EShaderDataType::Float3, "NORMAL"),
                            EBufferElement(EShaderDataType::Float2, "TEXCOORD") };
    vb->SetLayout(layout);

    ERef<EIndexBuffer> ib = EIndexBuffer::Create(ESharedBuffer().InitWith<u32>((void*)indices.data(), indices.size() * sizeof(u32)));

    fVertexArray->AddVertexBuffer(vb);
    fVertexArray->SetIndexBuffer(ib);
}
