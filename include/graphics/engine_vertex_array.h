#pragma once

namespace Engine {

	class EVertexArray
	{
	public:
		virtual ~EVertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<EVertexBuffer>& vertexBuffer) = 0;
		virtual const std::shared_ptr<EIndexBuffer>& GetIndexBuffer() const = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<EIndexBuffer>& indexBuffer) = 0;

		static EVertexArray* Create();
	};

}