#include "Engine.h"

namespace Engine {

	EVertexBuffer* EVertexBuffer::Create(const void* data, u32 size)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return new EOpenGLVertexBuffer(data, size);
		case ERenderingType::None:		break;
		}
		
		return nullptr;
	}

	EIndexBuffer* EIndexBuffer::Create(const u32* data, u32 count)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return new EOpenGLIndexBuffer(data, count);
		case ERenderingType::None:		break;
		}
		return nullptr;
	}


	EVertexArray* EVertexArray::Create()
	{
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new EOpenGLVertexArray();
		case ERenderingType::None:	break;
		}
		return nullptr;
	}


	EFrameBuffer* EFrameBuffer::Create(u32 width, u32 height, EFramebufferFormat format)
	{
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new EOpenGLFrameBuffer(width, height, format);
		case ERenderingType::None:	break;
		}
		return nullptr;
	}

}
