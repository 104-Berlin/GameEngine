#pragma once

namespace Engine {

    class EOpenGLRenderContext : public ERenderContext
    {
    public:
        EOpenGLRenderContext(EWindow& window);
        ~EOpenGLRenderContext();

        virtual void SetClearColor(const EColor& color);
        virtual void Clear();
    private:
        void SetGLDefaults(EWindow& window);
    private:
        EColor fClearColor;
    };

} 