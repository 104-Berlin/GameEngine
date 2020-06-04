#pragma once

namespace Engine {
	
	class EShader : public Resource
	{
	public:
		EShader(const EString& filePath, const EString& name = "Unknown") : Resource(name,filePath) {}

		virtual ~EShader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual byte* GetUniformBuffer(const EString& name) const = 0;
		virtual void SetUniformBuffer(const EString& name, byte* data, size_t size) = 0;

		virtual void UploadUniformBuffer() = 0;

		virtual void SetUniform1i(const EString& name, const int& value) = 0;
		virtual void SetUniform1f(const EString& name, const float& value) = 0;
		virtual void SetUniform2f(const EString& name, const glm::vec2& value) = 0;
		virtual void SetUniform3f(const EString& name, const glm::vec3& value) = 0;
		virtual void SetUniform4f(const EString& name, const glm::vec4& value) = 0;
		virtual void SetUniformMat4(const EString& name, const glm::mat4& value) = 0;

		virtual int GetResourceSlot(const EString& name) const = 0;

		virtual bool Reload(const EString& filePath) = 0;

		static EShader* Create(const EString& filePath);
		static EShader* Create(const EString& vertexSource, const EString& fragmentSource);
	public:
		static EShader* DefaultShader;
	};

}