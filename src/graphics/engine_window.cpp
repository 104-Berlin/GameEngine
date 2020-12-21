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
		fData.mousePosition = EVec2();

		glfwInit();


		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);	
				// Decide GL+GLSL versions
#if __APPLE__
		// GL 3.2 + GLSL 150
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
		// GL 3.0 + GLSL 130
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif



		fWindow = glfwCreateWindow(fData.width, fData.height, fData.title.c_str(), NULL, NULL);
		if (!fWindow)
		{
			glfwTerminate();
			std::cout << "Could not create Window" << std::endl;
			return;
		}

		ERenderer::Init();
		ERenderContext::Create(*this);
		UI::Init(*this);
		
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
			data.mousePosition = EVec2((float)xPos, (float)yPos);
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

			data.mouseScroll = yOffset;
		});

		
	}

	EWindow::~EWindow()
	{
		glfwTerminate();
		ERenderer::CleanUp();
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
