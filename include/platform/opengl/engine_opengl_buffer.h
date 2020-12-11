#pragma once

namespace Engine {

	static GLenum ShaderDataTypeToOpenGLType(EShaderDataType type)
	{
		switch (type)
		{
		case EShaderDataType::Float:			
		case EShaderDataType::Float2:			
		case EShaderDataType::Float3:			
		case EShaderDataType::Float4:			
		case EShaderDataType::Matrix3:			
		case EShaderDataType::Matrix4:			return GL_FLOAT;
		case EShaderDataType::Int:				
		case EShaderDataType::Texture2D:		
		case EShaderDataType::TextureCube:		
		case EShaderDataType::Int2:				
		case EShaderDataType::Int3:				
		case EShaderDataType::Int4:				return GL_INT;
		case EShaderDataType::UInt:				return GL_UNSIGNED_INT;
		case EShaderDataType::Byte4:			return GL_UNSIGNED_BYTE;
		case EShaderDataType::Bool:				return GL_BOOL;
		case EShaderDataType::None:				break;
		}
		return 0;
	}

	class EOpenGLVertexBuffer : public EVertexBuffer
	{
	public:
		EOpenGLVertexBuffer(const void* data, u32 size);
		~EOpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void* Map() override;
		virtual void Unmap() override;

		virtual const EBufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const EBufferLayout& layout) override { m_Layout = layout; }
	private:
		void PrivBind() const;
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