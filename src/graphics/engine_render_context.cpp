#include "Engine.h"

namespace Engine {

    ERenderingType ERenderContext::Renderer = ERenderingType::OpenGL;
    ERenderContext* ERenderContext::s_Instance = nullptr;

    void ERenderContext::Create(EWindow& window)
    {
        // TODO: ASSERT
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:    s_Instance = new EOpenGLRenderContext(window);
        case ERenderingType::None:		break;
		}
    }

    void ERenderContext::Destroy()
    {
        if (s_Instance)
            delete s_Instance;
    }

}
