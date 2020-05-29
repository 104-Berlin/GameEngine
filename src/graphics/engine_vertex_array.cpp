#include "Engine.h"

namespace Engine {

	EVertexArray* EVertexArray::Create()
	{
		IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:return new OpenGLVertexArray();
		}

		return nullptr;
	}

}
