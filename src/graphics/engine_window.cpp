#include "Engine.h"

namespace Engine {

	EWindow::EWindow(const EWindowProp& prop)
	{
		fData.title = prop.title;
		fData.width = prop.width;
		fData.height = prop.height;
		fData.altPressed = false;
		fData.leftPress = false;
		fData.rightPress = false;
		fData.middlePress = false;
		fData.mousePosition = glm::vec2();

		glfwInit();


		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);	
		fWindow = glfwCreateWindow(fData.width, fData.height, fData.title.c_str(), NULL, NULL);
		if (!fWindow)
		{
			glfwTerminate();
			std::cout << "Could not create Window" << std::endl;
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
					data.altPressed = true;
					break;
				}
				case GLFW_REPEAT: 
				{
					break;
				}
				case GLFW_RELEASE:
				{
					data.altPressed = false;
					break;
				}
			}
		});

		glfwSetCursorPosCallback(fWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);
			data.mousePosition = glm::vec2((float)xPos, (float)yPos);
		});

		glfwSetMouseButtonCallback(fWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					if (button == 0) {data.leftPress = true;}
					if (button == 1) {data.rightPress = true;}
					if (button == 2) {data.middlePress = true;}
					break;
				}
				case GLFW_RELEASE:
				{
					if (button == 0) {data.leftPress = false;}
					if (button == 1) {data.rightPress = false;}
					if (button == 2) {data.middlePress = false;}
					break;
				}
			}
		});

		glfwSetScrollCallback(fWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			EWindowData& data = *(EWindowData*)glfwGetWindowUserPointer(window);

			std::cout << "Mouse Scroll: " << xOffset << ", " << yOffset << std::endl;

			data.mouseScroll = yOffset;
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

	float EWindow::GetScroll()
	{
		float result = fData.mouseScroll;
		fData.mouseScroll = 0; 
		return result; 
	}

}
