#pragma once

namespace Engine {

    class EWindow
    {
    public:
        EWindow(const EString& title, u32 widht, u32 height);
        ~EWindow();

        void Show();

        void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);
        void Update();

        bool IsOpen() const;
    private:
        u32 fWidth;
        u32 fHeight;
        EString fTitle;

        GLFWwindow* fGlfwWindow;
    };

}