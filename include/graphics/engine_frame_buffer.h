#pragma once

namespace Engine {

	enum class EFramebufferFormat
	{
		None = 0,
		RGBA8 = 1,
		RGBA16F = 2
	};

	class EFrameBuffer
	{
	public:
		virtual ~EFrameBuffer() {}

		virtual void Resize(u32 width, u32 height) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void BindTexture(u32 slot = 0) const = 0;

		virtual u32 GetColorAttachment() const { return 0; }

		static EFrameBuffer* Create(u32 width, u32 height, EFramebufferFormat format);
	};

}