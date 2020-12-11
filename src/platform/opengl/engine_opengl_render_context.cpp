#include "Engine.h"

namespace Engine {

    EOpenGLRenderContext::EOpenGLRenderContext(EWindow& window)
    {
		glfwMakeContextCurrent(window.GetNativeWindow());
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        //TODO: Add ASSERT
		//IN_CORE_ASSERT(gladStatus, "Failed to initialize glad!");
        std::cout << glGetString(GL_VERSION) << std::endl;

        SetGLDefaults();
    }

    void EOpenGLRenderContext::SetGLDefaults()
    {
        IN_RENDER({
            glEnable(GL_DEPTH_TEST);
        })
    }

    EOpenGLRenderContext::~EOpenGLRenderContext()
    {
        
    }

    void EOpenGLRenderContext::SetClearColor(const EColor& color)
    {
        fClearColor = color;
    }

    void EOpenGLRenderContext::Clear()
    {
        IN_RENDER1(fClearColor, {
            glClearColor(fClearColor.r, fClearColor.g, fClearColor.b, fClearColor.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        })
    }

}
