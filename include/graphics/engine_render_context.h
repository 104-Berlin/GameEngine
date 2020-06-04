#pragma once

namespace Engine {

    enum class ERenderingType
    {
        None = 0,
        OpenGL = 1
    };

    class ERenderContext
    {
    public:
    static void Create(EWindow& window);
    static void Destroy();
    public:
    static ERenderingType Renderer;
    static ERenderContext* s_Instance;
    };

}