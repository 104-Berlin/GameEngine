#include "Engine.h"

namespace Engine {

	EVertexBuffer::EVertexBuffer(EBufferUsage usage) 
		: fBufferUsage(usage)
	{
		
	}
	
	ERef<EVertexBuffer> EVertexBuffer::Create(EBufferUsage usage)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLVertexBuffer>(new EOpenGLVertexBuffer(usage));
		case ERenderingType::None:		break;
		}
		
		return nullptr;
	}
	
	ERef<EVertexBuffer> EVertexBuffer::Create(ESharedBuffer data)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLVertexBuffer>(new EOpenGLVertexBuffer(data));
		case ERenderingType::None:		break;
		}
		
		return nullptr;
	}
	
	EIndexBuffer::EIndexBuffer(EBufferUsage usage) 
		: fBufferUsage(usage)
	{
		
	}

	ERef<EIndexBuffer> EIndexBuffer::Create(EBufferUsage usage)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLIndexBuffer>(new EOpenGLIndexBuffer(usage));
		case ERenderingType::None:		break;
		}
		return nullptr;
	}

	ERef<EIndexBuffer> EIndexBuffer::Create(ESharedBuffer data)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLIndexBuffer>(new EOpenGLIndexBuffer(data));
		case ERenderingType::None:		break;
		}
		return nullptr;
	}


	ERef<EVertexArray> EVertexArray::Create()
	{
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return ERef<EOpenGLVertexArray>(new EOpenGLVertexArray());
		case ERenderingType::None:	break;
		}
		return nullptr;
	}


	ERef<EFrameBuffer> EFrameBuffer::Create(u32 width, u32 height, EFramebufferFormat format)
	{
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return ERef<EOpenGLFrameBuffer>(new EOpenGLFrameBuffer(width, height, format));
		case ERenderingType::None:	break;
		}
		
		return nullptr;
	}

}
