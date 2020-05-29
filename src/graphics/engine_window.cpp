#include "Engine.h"

using namespace Engine;

EWindow::EWindow(const EString& title, u32 width, u32 height)
    : fTitle(title), fWidth(width), fHeight(height)
{

}

EWindow::~EWindow()
{
    glfwDestroyWindow(fGlfwWindow);
    glfwTerminate();
}

void EWindow::Show()
{
    if (!glfwInit())
    {
        std::cout << "Could not init glfw" << std::endl;
        return;
    }


    fGlfwWindow = glfwCreateWindow(fWidth, fHeight, fTitle.c_str(), nullptr, nullptr);
    if (!fGlfwWindow)
    {
        std::cout << "Could not init Glfw Window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(fGlfwWindow);
    gladLoadGL();
}

void EWindow::Update()
{
    glfwSwapBuffers(fGlfwWindow);
    glfwPollEvents();
}

void EWindow::Clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool EWindow::IsOpen() const
{
    return !((bool) glfwWindowShouldClose(fGlfwWindow));
}