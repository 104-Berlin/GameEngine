#include "Engine.h"

namespace Engine {

    ERenderContext* ERenderContext::s_Instance = nullptr;

    void ERenderContext::Create(EWindow& window)
    {
        // TODO: ASSERT
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: s_Instance = new EOpenGLRenderContext(window);
		}
    }

    void ERenderContext::Destroy()
    {
        if (s_Instance)
            delete s_Instance;
    }

}
