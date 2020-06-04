#include "Engine.h"

namespace Engine {

	ETexture2D* ETexture2D::Create(const EString& path, bool srgb)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new EOpenGLTexture2D(path, srgb);
		}
		return nullptr;
	}

	ETexture2D* ETexture2D::Create(ETextureFormat format, u32 width, u32 height)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new EOpenGLTexture2D(format, width, height);
		}
		return nullptr;
	}

	ETextureCube* ETextureCube::Create(const EString& path, bool srgb)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: return new EOpenGLTextureCube(path, srgb);
		}
		return nullptr;
	}

}
