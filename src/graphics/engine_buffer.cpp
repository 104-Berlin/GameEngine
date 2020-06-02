#include "Engine.h"

namespace Engine {

	EVertexBuffer* EVertexBuffer::Create(const void* data, u32 size)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:return new EOpenGLVertexBuffer(data, size);
		}
		
		return nullptr;
	}

	EIndexBuffer* EIndexBuffer::Create(const u32* data, u32 count)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:return new EOpenGLIndexBuffer(data, count);
		}
		return nullptr;
	}

}
