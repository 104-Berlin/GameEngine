#include "Engine.h"

namespace Engine {

	EFrameBuffer* EFrameBuffer::Create(u32 width, u32 height, EFramebufferFormat format)
	{
		// TODO: ASSERT
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new OpenGLFrameBuffer(width, height, format);
		}
		return nullptr;
	}

}