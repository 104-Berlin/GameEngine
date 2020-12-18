#pragma once

namespace Engine {

    class ESprite : public EResource
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
        ESprite(const EString& path);
        ~ESprite();

        void Draw();

        virtual bool OnLoad() override;
    };

}