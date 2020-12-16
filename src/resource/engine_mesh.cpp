#include "Engine.h"

using namespace Engine;

EMesh::EMesh(const EString& path)
    : Resource(EFile(path).GetFileName(), path)
{

}

EMesh::EMesh(const EString& name, const EVector<EVertex>& vertices, const EVector<u32>& indices)
    : Resource(name, "")
{
    fVertexArray = EVertexArray::Create();
    ERef<EVertexBuffer> vb = EVertexBuffer::Create(vertices.data(), vertices.size() * sizeof(EVertex));
    EBufferLayout layout = { EBufferElement(EShaderDataType::Float3, "POSITION"),
                            EBufferElement(EShaderDataType::Float3, "NORMAL"),
                            EBufferElement(EShaderDataType::Float2, "TEXCOORD") };
    vb->SetLayout(layout);

    ERef<EIndexBuffer> ib = EIndexBuffer::Create(indices.data(), indices.size());

    fVertexArray->AddVertexBuffer(vb);
    fVertexArray->SetIndexBuffer(ib);
}

EMesh::~EMesh()
{

}

bool EMesh::OnReload()
{
    return false;
}