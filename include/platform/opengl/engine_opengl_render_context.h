#pragma once

namespace Engine {

    class EOpenGLRenderContext : public ERenderContext
    {
    public:
        EOpenGLRenderContext(EWindow& window);
        ~EOpenGLRenderContext();
    };

} 