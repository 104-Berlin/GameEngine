#include "Engine.h"

namespace Engine {

	ERef<ETexture2D> ETexture2D::Create(const EString& path, bool srgb)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: 	return ERef<EOpenGLTexture2D>(new EOpenGLTexture2D(path, srgb));
		case ERenderingType::None:		break;
		}
		return nullptr;
	}

	ERef<ETexture2D> ETexture2D::Create(ETextureFormat format, u32 width, u32 height)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: 	return ERef<EOpenGLTexture2D>(new EOpenGLTexture2D(format, width, height));
		case ERenderingType::None:		break;
		}
		return nullptr;
	}

	ERef<ETextureCube> ETextureCube::Create(const EString& path, bool srgb)
	{
		//TODO: ADD SERRT
		//IN_CORE_ASSERT((bool)ERenderContext, "No Renderer selected!");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL: 	return ERef<EOpenGLTextureCube>(new EOpenGLTextureCube(path, srgb));
		case ERenderingType::None:		break;
		}
		return nullptr;
	}

}
