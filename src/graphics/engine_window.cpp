#include "Engine.h"

using namespace Engine;

void Engine_CreateWindow(ImGuiViewport* viewport)
{

}

void Engine_DestroyWindow(ImGuiViewport* viewport)
{

}

void Engine_ShowWindow(ImGuiViewport* viewport)
{

}

void Engine_SetWindowPos(ImGuiViewport* viewport, ImVec2 pos)
{

}

ImVec2 Engine_GetWindowPos(ImGuiViewport* viewport)
{

}

void Engine_SetWindowSize(ImGuiViewport* viewport, ImVec2 size)
{

}

ImVec2 Engine_GetWindowSize(ImGuiViewport* viewort)
{

}

void Engine_SetWindowFocus(ImGuiViewport* viewport, bool focus)
{

}

bool Engine_GetWindowFocus(ImGuiViewport* viewport)
{

}

bool Engine_GetWindowMinimized(ImGuiViewport* viewport)
{

}

void Engine_SetWindowTitle(ImGuiViewport* viewport, const char* title)
{

}

void Engine_RenderWindow(ImGuiViewport* viewport)
{

}

void Engine_SwapBuffers(ImGuiViewport* viewport)
{
	
}



EMainWindow::EMainWindow(const EString& title, u32 width, u32 height)
	: fTitle(title), fWidth(width), fHeight(height), fNativeWindowPtr(nullptr)
{

}

EMainWindow::~EMainWindow()
{

}

void EMainWindow::PollEvent()
{

}

void EMainWindow::Update()
{
	if (fNativeWindowPtr) { return; }
	glfwPollEvents();
}

void EMainWindow::Present()
{
	if (!fNativeWindowPtr) { return; }
	glfwSwapBuffers((GLFWwindow*)fNativeWindowPtr);
}

bool EMainWindow::IsOpen()
{
	if (!fNativeWindowPtr) { return false; }
	return !((bool)glfwWindowShouldClose((GLFWwindow*)fNativeWindowPtr));
}

void EMainWindow::Init()
{
	if (!glfwInit()) { return; }

	fNativeWindowPtr = glfwCreateWindow(fWidth, fHeight, fTitle.c_str(), NULL, NULL);
	if (!fNativeWindowPtr) { return; }

	glfwMakeContextCurrent((GLFWwindow*)fNativeWindowPtr);
}
