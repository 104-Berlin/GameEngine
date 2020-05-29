#include "inpch.h"

namespace Infinit {
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint size)
	{
		IN_RENDER_S2(data, size, {
				glGenBuffers(1, &self->m_RendererID);
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			})
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		IN_CORE_INFO("OpenGLVertexBuffer {0} Deleted!", m_RendererID);
		IN_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			})
	}

	void OpenGLVertexBuffer::Bind() const
	{
		IN_RENDER_S({
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			})
	}

	void OpenGLVertexBuffer::Unbind() const
	{
#ifdef IN_DEBUG
		IN_RENDER({
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			})
#endif
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint* data, uint count)
		: m_Count(count)
	{
		IN_RENDER_S2(data, count, {
				glGenBuffers(1, &self->m_RendererID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
			})
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		IN_CORE_INFO("OpenGLIndexBuffer {0} Deleted!", m_RendererID);
		IN_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			})
	}

	void OpenGLIndexBuffer::Bind() const
	{
		IN_RENDER_S({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			})
	}

	void OpenGLIndexBuffer::Unbind() const
	{
#ifdef IN_DEBUG
		IN_RENDER({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			})
#endif
	}

}