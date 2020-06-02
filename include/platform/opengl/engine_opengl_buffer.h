#pragma once

namespace Engine {

	class EOpenGLVertexBuffer : public EVertexBuffer
	{
	public:
		EOpenGLVertexBuffer(const void* data, u32 size);
		~EOpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const EBufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const EBufferLayout& layout) override { m_Layout = layout; }
	private:
		u32 m_RendererID = 0;
		EBufferLayout m_Layout;
	};

	class EOpenGLIndexBuffer : public EIndexBuffer
	{
	public:
		EOpenGLIndexBuffer(const u32* data, u32 count);
		~EOpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual u32 GetCount() const override { return m_Count; }
	private:
		u32 m_RendererID = 0;
		u32 m_Count;
	};

}