#pragma once

namespace Engine {

    class EUIRenderer
    {
    private:
        ERef<EVertexArray>  fVertexArray;
        ERef<EVertexBuffer> fVertexBuffer;
        ERef<EIndexBuffer>  fIndexBuffer;
        ERef<EShader>       fShader;
        ERef<ETexture2D>    fFontTexture;

        bool                fIsInitialized;
    public:
        EUIRenderer();
        void Init(ERef<EWindow> window);

        void Begin();
        void Render();
        void End();

        bool IsInitialized() const { return fIsInitialized; }
    private:

        void CreateRenderingStorage();
        void CreateFontAtlas();
        void RenderWindow(ImGuiViewport* viewport, void* data);
    };

}