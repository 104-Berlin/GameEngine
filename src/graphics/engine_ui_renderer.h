#pragma once

namespace Engine {

    class EUIRenderer
    {
    private:
        ERef<EVertexBuffer> fVertexBuffer;
        ERef<EVertexArray> fVertexArray;
    public:
        EUIRenderer();

        void Begin();
        void Render();
        void End();
    private:
        
    };

}