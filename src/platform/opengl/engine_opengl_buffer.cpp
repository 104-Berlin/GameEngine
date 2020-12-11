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
				self->PrivBind();
			})
	}

	void* EOpenGLVertexBuffer::Map()
	{
		return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void EOpenGLVertexBuffer::Unmap()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}



	void EOpenGLVertexBuffer::PrivBind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
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

EOpenGLVertexArray::EOpenGLVertexArray()
{
	IN_RENDER_S({
		glGenVertexArrays(1, &self->fRendererID);
		glBindVertexArray(self->fRendererID); 
	})
}

EOpenGLVertexArray::~EOpenGLVertexArray()
{		
	std::cout << "OpenGL VertexArray "<< fRendererID << " destroyed!" << std::endl;

	IN_RENDER_S({
		glDeleteVertexArrays(1, &self->fRendererID);
	})
}

void EOpenGLVertexArray::Bind() const
{
	IN_RENDER_S({
		glBindVertexArray(self->fRendererID);
	});
}

void EOpenGLVertexArray::Unbind() const
{
	IN_RENDER({
		glBindVertexArray(0);
	});
}


void EOpenGLVertexArray::AddVertexBuffer(EVertexBuffer* vertexBuffer)
{
	if (vertexBuffer->GetLayout().GetElements().size() == 0)
	{	
		std::cout << "No Vertex Layout set for the buffer" << std::endl;
		return;
	}

	fVertexBuffers.push_back(vertexBuffer);
	Bind();
	vertexBuffer->Bind();

	IN_RENDER_S1(vertexBuffer, {

		const auto & layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(self->fVertexBufferIndex);
			glVertexAttribPointer(self->fVertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(), (const void*)element.Offset);
			self->fVertexBufferIndex++;
		}
	});
}

EIndexBuffer* EOpenGLVertexArray::GetIndexBuffer() const
{
	return fIndexBuffer;
}

void EOpenGLVertexArray::SetIndexBuffer(EIndexBuffer* indexBuffer)
{
	fIndexBuffer = indexBuffer;

	IN_RENDER_S({
		glBindVertexArray(self->fRendererID);
		self->fIndexBuffer->Bind();
	});
}


}