#include "Engine.h"

namespace Engine {

    EOpenGLRenderContext::EOpenGLRenderContext(EWindow& window)
    {
		glfwMakeContextCurrent(window.GetNativeWindow());
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        //TODO: Add ASSERT
		//IN_CORE_ASSERT(gladStatus, "Failed to initialize glad!");
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    EOpenGLRenderContext::~EOpenGLRenderContext()
    {
        
    }

}
