#include "Engine.h"


#include "backends/imgui_impl_glfw.h"


using namespace Engine;


EMainWindow::EMainWindow(const EString& title, u32 width, u32 height)
	: fTitle(title), fWidth(width), fHeight(height), fNativeWindowPtr(nullptr)
{
	Init();
}

EMainWindow::~EMainWindow()
{
	if (fNativeWindowPtr)
	{
		glfwDestroyWindow((GLFWwindow*)fNativeWindowPtr);
	}
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
