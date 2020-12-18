#include "Engine.h"


namespace Engine {

	ERef<EShader> EShader::DefaultShader;

	EShader::EShader(const EString& filePath) : EResource(filePath) 
	{

	}


	ERef<EShader> EShader::Create(const EString& filePath)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLShader>(new EOpenGLShader(filePath));
		case ERenderingType::None:		break;
		}

		return nullptr;
	}

	ERef<EShader> EShader::Create(const EString& vertexSource, const EString& fragmentSource)
	{
		//TODO: Add ASSERT
		//IN_CORE_ASSERT((bool)ERenderContext, "No RenderAPI selected");
		switch (ERenderContext::Renderer)
		{
		case ERenderingType::OpenGL:	return ERef<EOpenGLShader>(new EOpenGLShader(vertexSource, fragmentSource));
		case ERenderingType::None:		break;
		}

		return nullptr;
	}

}
