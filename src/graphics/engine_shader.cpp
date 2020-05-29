#include "Engine.h"


namespace Engine {

	EShader* EShader::DefaultShader;

	EShader* EShader::Create(const EString& filePath)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:return new EOpenGLShader(filePath);
		}

		return nullptr;
	}

	EShader* EShader::Create(const EString& vertexSource, const EString& fragmentSource)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:return new EOpenGLShader(vertexSource, fragmentSource);
		}

		return nullptr;
	}

}
