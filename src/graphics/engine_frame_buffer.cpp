#include "Engine.h"

namespace Engine {

	EFrameBuffer* EFrameBuffer::Create(u32 width, u32 height, EFramebufferFormat format)
	{
		// TODO: ASSERT
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return nullptr;//new OpenGLFrameBuffer(width, height, format);
		case ERenderingType::None:	 break;
		}
		return nullptr;
	}

}