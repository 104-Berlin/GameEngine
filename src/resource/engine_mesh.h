#pragma once

namespace Engine {

    class E_API EMesh : public EResource
    {
    public:
        struct EVertex
        {
            EVec3 Position;
            EVec3 Normal;
            EVec2 TexCoord;            
        };

        ERef<EVertexArray>  fVertexArray;
        
    public:
        EMesh(const EString& enginePath);
        EMesh(const EString& enginePath, const EVector<EVertex>& vertices, const EVector<u32>& indices);
        ~EMesh();
    private:
        void Create(const EVector<EVertex>& vertices, const EVector<u32>& indices);
    };

}
