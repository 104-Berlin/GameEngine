#include "Engine.h"

namespace Engine {

	EWindow::EWindow(const EWindowProp& prop)
	{
		fData.title = prop.title;
		fData.width = prop.width;
		fData.height = prop.height;

		glfwInit();

		fWindow = glfwCreateWindow(fData.width, fData.height, fData.title.c_str(), NULL, NULL);
		if (!fWindow)
		{
			glfwTerminate();
			std::cout << "Could not create EWindow" << std::endl;
			return;
		}
		ERenderContext::Create(*this);
		glfwSetWindowUserPointer(fWindow, &fData);

		glfwSetWindowSizeCallback(fWindow, [](GLFWwindow* EWindow, int width, int height)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(EWindow);
			data.width = width;
			data.height = height;
		});

		glfwSetWindowCloseCallback(fWindow, [](GLFWwindow* EWindow)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(EWindow);
		});

		glfwSetKeyCallback(fWindow, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					break;
				}
				case GLFW_REPEAT: 
				{
					break;
				}
				case GLFW_RELEASE:
				{
					break;
				}
			}
		});

		glfwSetCursorPosCallback(fWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);
		});

		glfwSetMouseButtonCallback(fWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					break;
				}
				case GLFW_RELEASE:
				{
					break;
				}
			}
		});

		glfwSetScrollCallback(fWindow, [](GLFWwindow* EWindow, double xOffset, double yOffset)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(EWindow);
		});

		
	}

	EWindow::~EWindow()
	{
		glfwTerminate();
	}

	void EWindow::Update() const
	{
		glfwSwapBuffers(fWindow);
		glfwPollEvents();
	}

	bool EWindow::IsClosed() const
	{
		return (bool)glfwWindowShouldClose(fWindow);
	}

}
