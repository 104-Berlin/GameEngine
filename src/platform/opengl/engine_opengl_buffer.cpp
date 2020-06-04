#include "Engine.h"

namespace Engine {
	
	EOpenGLVertexBuffer::EOpenGLVertexBuffer(const void* data, u32 size)
	{
		IN_RENDER_S2(data, size, {
				glGenBuffers(1, &self->m_RendererID);
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			})
	}

	EOpenGLVertexBuffer::~EOpenGLVertexBuffer()
	{
		std::cout  << "OpenGLVertexBuffer " << m_RendererID << " Deleted!" << std::endl;
		IN_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			})
	}

	void EOpenGLVertexBuffer::Bind() const
	{
		IN_RENDER_S({
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			})
	}

	void EOpenGLVertexBuffer::Unbind() const
	{
#ifdef IN_DEBUG
		IN_RENDER({
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			})
#endif
	}

	EOpenGLIndexBuffer::EOpenGLIndexBuffer(const u32* data, u32 count)
		: m_Count(count)
	{
		IN_RENDER_S2(data, count, {
				glGenBuffers(1, &self->m_RendererID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);
			})
	}

	EOpenGLIndexBuffer::~EOpenGLIndexBuffer()
	{
		std::cout  << "OpenGLIndexBuffer " << m_RendererID << " Deleted!" << std::endl;
		IN_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			})
	}

	void EOpenGLIndexBuffer::Bind() const
	{
		IN_RENDER_S({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			})
	}

	void EOpenGLIndexBuffer::Unbind() const
	{
#ifdef IN_DEBUG
		IN_RENDER({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			})
#endif
	}

}