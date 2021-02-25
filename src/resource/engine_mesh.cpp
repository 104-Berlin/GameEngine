#include "Engine.h"

using namespace Engine;

EMesh::EMesh(const EString& path)
    : EResource(path), fVertexArray(nullptr)
{

}

EMesh::EMesh(const EString& name, const EVector<EVertex>& vertices, const EVector<u32>& indices)
    : EResource("res/intern/" + name + ".rc"), fVertexArray(nullptr)
{
    Create(vertices, indices);
}

EMesh::~EMesh()
{

}

bool EMesh::OnLoad()
{
    EFile meshFile(GetFilePath());
    if (!meshFile.Exist()) { std::cout << "Cant read mesh file \"" << GetFilePath() << "\"!" << std::endl; return false; }

    EVector<EVertex>    vertices;
    EVector<u32>        indices;

    /*Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(GetFilePath(), aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_GenNormals);
    
    if (scene && scene->HasMeshes())
    {
        for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
        {
        
            const aiMesh* currentMesh = scene->mMeshes[meshIndex];
            for (size_t vertexIndex = 0; vertexIndex < currentMesh->mNumVertices; vertexIndex++)
            {
                // TODO VERIFY MESH DATA BEFORE CREATING
                aiVector3D& position = currentMesh->mVertices[vertexIndex];
                aiVector3D& normal = currentMesh->mNormals[vertexIndex];
                aiVector3D uv = aiVector3D(0, 0, 0);
                if (currentMesh->HasTextureCoords(0))
                {
                    uv = currentMesh->mTextureCoords[0][vertexIndex];
                }

                EVertex vert;
                vert.Position = EVec3(position.x, position.y, position.z);
                vert.Normal = EVec3(normal.x, normal.y, normal.z);
                vert.TexCoord = EVec2(uv.x, uv.y);
                vertices.push_back(vert);
            }

            for (size_t i = 0; i < currentMesh->mNumFaces; i++)
            {
                aiFace& currentFace = currentMesh->mFaces[i];
                for (size_t curr = 0; curr < currentFace.mNumIndices; curr++)
                {
                    indices.push_back(currentFace.mIndices[curr]);
                }
            }
        }
        Create(vertices, indices);
        return true;
    }*/



    return false;
}

void EMesh::Create(const EVector<EVertex>& vertices, const EVector<u32>& indices)
{
    fVertexArray = EVertexArray::Create();
    ERef<EVertexBuffer> vb = EVertexBuffer::Create(vertices.data(), vertices.size() * sizeof(EVertex));
    EBufferLayout layout = { EBufferElement(EShaderDataType::Float3, "POSITION"),
                            EBufferElement(EShaderDataType::Float3, "NORMAL"),
                            EBufferElement(EShaderDataType::Float2, "TEXCOORD") };
    vb->SetLayout(layout);

    ERef<EIndexBuffer> ib = EIndexBuffer::Create(indices.data(), indices.size() * sizeof(u32), indices.size());

    fVertexArray->AddVertexBuffer(vb);
    fVertexArray->SetIndexBuffer(ib);
}