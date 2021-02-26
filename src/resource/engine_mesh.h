#pragma once

namespace Engine {

    E_API class EMesh : public EResource
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
        EMesh(const EString& filePath);
        EMesh(const EString& name, const EVector<EVertex>& vertices, const EVector<u32>& indices);
        ~EMesh();

        virtual bool OnLoad() override;
    private:
        void Create(const EVector<EVertex>& vertices, const EVector<u32>& indices);
    };

}
