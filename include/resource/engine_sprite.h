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
        EVertexArray*   fVertexArray;
        EVertexBuffer*  fVertexBuffer;
        EIndexBuffer*   fIndexBuffer;
        ETexture2D*     fTexture;
    public:
        ESprite(const EString& name, const EString& path);
        ~ESprite();

        void Draw();

        virtual bool OnLoad() override;
        virtual bool OnImport() override;
    };

}