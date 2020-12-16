#pragma once

namespace Engine {

    class ESprite : public Resource
    {
    public:
        struct EVertex
        {
            EVec2 Position;
            EVec2 TexCoord;
        };
    private:
        ERef<EVertexArray>   fVertexArray;
        ERef<EVertexBuffer>  fVertexBuffer;
        ERef<EIndexBuffer>   fIndexBuffer;
        ERef<ETexture2D>     fTexture;
    public:
        ESprite(const EString& name, const EString& path);
        ~ESprite();

        void Draw();

        virtual bool OnReload() override;
    };

}