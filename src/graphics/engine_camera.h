#pragma once

namespace Engine {

	class E_API ECamera
	{
	public:
		ECamera(const glm::mat4& projectionMatrix);

		virtual void UpdateImGui();

		inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { fProjectionMatrix = projectionMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return fProjectionMatrix; }
	private:
		glm::mat4 fProjectionMatrix;
	};


}