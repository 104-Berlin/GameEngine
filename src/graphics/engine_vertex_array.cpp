#include "Engine.h"

namespace Engine {

	EVertexArray* EVertexArray::Create()
	{
		//TODO: AddAssert
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		//case ERenderingType::OpenGL:return new EOpenGLVertexArray();
		}

		return nullptr;
	}

}
