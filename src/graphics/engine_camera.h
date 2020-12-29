#pragma once

namespace Engine {

	class ECamera
	{
	public:
		ECamera(const glm::mat4& projectionMatrix);

		virtual void Update(const ERef<EWindow>& window);
		virtual void UpdateImGui();

		//inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { fProjectionMatrix = projectionMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return fProjectionMatrix; }

		void SetCameraSize(ECameraComponent::CameraMode cameraMode, u32 width, u32 height);
	private:
		glm::mat4 fProjectionMatrix;

		u32 fScreenHeight;
		u32 fScreenWidth;
	};


}