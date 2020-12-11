#pragma once


namespace Engine {

	enum class EShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Matrix3, Matrix4, Int, Int2, Int3, Int4, UInt, Byte4, Bool, Texture2D, TextureCube
	};

	static u32 ShaderDataTypeSize(EShaderDataType type)
	{
		switch (type)
		{
		case EShaderDataType::Float:			return 4;
		case EShaderDataType::Float2:			return 4 * 2;
		case EShaderDataType::Float3:			return 4 * 3;
		case EShaderDataType::Float4:			return 4 * 4;
		case EShaderDataType::Matrix3:			return 4 * 3 * 3;
		case EShaderDataType::Matrix4:			return 4 * 4 * 4;
		case EShaderDataType::Int:				return 4;
		case EShaderDataType::Texture2D:		return 4;
		case EShaderDataType::TextureCube:		return 4;
		case EShaderDataType::Int2:				return 4 * 2;
		case EShaderDataType::Int3:				return 4 * 3;
		case EShaderDataType::Int4:				return 4 * 4;
		case EShaderDataType::UInt:				return 4;
		case EShaderDataType::Byte4:			return 4;
		case EShaderDataType::Bool:				return 1;
		case EShaderDataType::None:				break;
		}

		std::cout << "Unknown EShaderDataType" << std::endl;
		return 0;
	}

	static EShaderDataType ShaderDataTypeFromString(const EString& typeString)
	{
		if (typeString == "float") return EShaderDataType::Float;
		else if (typeString == "vec2") return EShaderDataType::Float2;
		else if (typeString == "vec3") return EShaderDataType::Float3;
		else if (typeString == "vec4") return EShaderDataType::Float4;
		else if (typeString == "bool") return EShaderDataType::Bool;
		else if (typeString == "dont know") return EShaderDataType::Byte4;
		else if (typeString == "int") return EShaderDataType::Int;
		else if (typeString == "ivec2") return EShaderDataType::Int2;
		else if (typeString == "ivec3") return EShaderDataType::Int3;
		else if (typeString == "ivec4") return EShaderDataType::Int4;
		else if (typeString == "mat3") return EShaderDataType::Matrix3;
		else if (typeString == "mat4") return EShaderDataType::Matrix4;
		else if (typeString == "sampler2D") return EShaderDataType::Texture2D;
		else if (typeString == "samplerCube") return EShaderDataType::TextureCube;

		return EShaderDataType::None;
	}

	struct EBufferElement
	{
		EShaderDataType Type;
		EString Name;
		size_t Size;
		size_t Offset;
		bool Normalized;

		EBufferElement() {}

		EBufferElement(EShaderDataType type, const EString& name, bool normalized = false)
			: Name(name), Type(type), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0)
		{}

		u32 GetComponentCount() const
		{
			switch (Type)
			{
			case EShaderDataType::Float:		return 1;
			case EShaderDataType::Float2:		return 2;
			case EShaderDataType::Float3:		return 3;
			case EShaderDataType::Float4:		return 4;
			case EShaderDataType::Matrix3:		return 3 * 3;
			case EShaderDataType::Matrix4:		return 4 * 4;
			case EShaderDataType::Int:			return 1;
			case EShaderDataType::Int2:			return 2;
			case EShaderDataType::Int3:			return 3;
			case EShaderDataType::Int4:			return 4;
			case EShaderDataType::UInt:			return 1;
			case EShaderDataType::Byte4:		return 4;
			case EShaderDataType::Bool:			return 1;
			case EShaderDataType::Texture2D: 	return 1;
			case EShaderDataType::TextureCube:	return 1;
			case EShaderDataType::None:			break;
			}

			//TODO: Add ASSERT
			//IN_CORE_ASSERT(false, "Unknown Shader Type");
			return 0;
		}
	};

	class EBufferLayout
	{
	public:
		EBufferLayout() {}

		EBufferLayout(const std::initializer_list<EBufferElement>& elements)
			: fElements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline u32 GetStride() const { return fStride; }
		inline const std::vector<EBufferElement>& GetElements() const { return fElements; }

		std::vector<EBufferElement>::iterator begin() { return fElements.begin(); }
		std::vector<EBufferElement>::iterator end() { return fElements.end(); }
		std::vector<EBufferElement>::const_iterator begin() const { return fElements.begin(); }
		std::vector<EBufferElement>::const_iterator end() const { return fElements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			u32 offset = 0;
			fStride = 0;
			for (auto& element : fElements)
			{
				element.Offset = offset;
				offset += element.Size;
				fStride += element.Size;
			}
		}
	private:
		std::vector<EBufferElement> fElements;
		u32 fStride = 0;
	};

	class EVertexBuffer
	{
	public:
		virtual ~EVertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const EBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const EBufferLayout& layout) = 0;

		// Call this in a IN_RENDER({})
		virtual void* Map() = 0;
		// DO NOT Call this in a IN_RENDER({})
		virtual void Unmap() = 0;

		static EVertexBuffer* Create(const void* data, u32 size);
	};

	class EIndexBuffer
	{
	public:
		virtual ~EIndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual u32 GetCount() const = 0;

		static EIndexBuffer* Create(const u32* indices, u32 count);
	};

	class EVertexArray
	{
	public:
		virtual ~EVertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void AddVertexBuffer(EVertexBuffer* vertexBuffer) = 0;
		virtual EIndexBuffer* GetIndexBuffer() const = 0;
		virtual void SetIndexBuffer(EIndexBuffer* indexBuffer) = 0;

		static EVertexArray* Create();
	};

}