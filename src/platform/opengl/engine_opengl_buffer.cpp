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
	fIndexBuffer = nullptr;
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

	for (const EVertexBuffer* vb : fVertexBuffers)
	{
		//vb->Bind();
	}
    if (fIndexBuffer)
    {
        //fIndexBuffer->Bind();
    }
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



EOpenGLFrameBuffer::EOpenGLFrameBuffer(u32 width, u32 height, EFramebufferFormat format)
	: m_Format(format), m_Width(0), m_Height(0), m_RendererID(0)
{
	Resize(width, height);
}

EOpenGLFrameBuffer::~EOpenGLFrameBuffer()
{

}

void EOpenGLFrameBuffer::Resize(u32 width, u32 height)
{
	if (width == m_Width && height == m_Height) return;

	m_Width = width;
	m_Height = height;

	if (m_RendererID)
	{
		IN_RENDER_S({
				glDeleteFramebuffers(1, &self->m_RendererID);
				glDeleteTextures(1, &self->m_ColorAttachment);
				glDeleteTextures(1, &self->m_DepthAttachment);
			})
	}

	IN_RENDER_S({

		glGenFramebuffers(1, &self->m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, self->m_RendererID);

		glGenTextures(1, &self->m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, self->m_ColorAttachment);

		if (self->m_Format == EFramebufferFormat::RGBA16F)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, self->m_Width, self->m_Height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		else if (self->m_Format == EFramebufferFormat::RGBA8)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->m_Width, self->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self->m_ColorAttachment, 0);

		glGenTextures(1, &self->m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, self->m_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, self->m_Width, self->m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, self->m_DepthAttachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer is incomplete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	})
}

void EOpenGLFrameBuffer::Bind() const
{
	IN_RENDER_S({
			glBindFramebuffer(GL_FRAMEBUFFER, self->m_RendererID);
			glViewport(0, 0, self->m_Width, self->m_Height);
		})
}

void EOpenGLFrameBuffer::Unbind() const
{
	IN_RENDER({
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
	})
}

void EOpenGLFrameBuffer::BindTexture(u32 slot) const
{
	IN_RENDER_S1(slot, {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, self->m_ColorAttachment);
		})
}



}
