#pragma once

namespace Engine {

    class EUIRenderer
    {
    private:
        ERef<EVertexBuffer> fVertexBuffer;
        ERef<EVertexArray>  fVertexArray;
        ERef<EShader>       fShader;
        ERef<ETexture2D>    fFontTexture;
    public:
        EUIRenderer();
        void Init(ERef<EWindow> window);

        void Begin();
        void Render();
        void End();
    private:

        void CreateRenderingStorage();
        void CreateFontAtlas();
        void RenderWindow(ImGuiViewport* viewport, void* data);
    };

}