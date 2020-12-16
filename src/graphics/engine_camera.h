#pragma once

namespace Engine {

	class ECamera
	{
	public:
		ECamera(const glm::mat4& projectionMatrix);

		void Update(const ERef<EWindow>& window);
		void UpdateImGui();

		inline float GetDistance() const { return fDistance; }
		inline void SetDistance(float distance) { fDistance = distance; }

		inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { fProjectionMatrix = projectionMatrix; }

		const glm::mat4& GetProjectionMatrix() const { return fProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return fViewMatrix; }

		EVec3 GetUpDirection();
		EVec3 GetRightDirection();
		EVec3 GetForwardDirection();
		const EVec3& GetPosition() const { return fPosition; }
	private:
		void MousePan(const EVec2& delta);
		void MouseRotate(const EVec2& delta);
		void MouseZoom(float delta);

		EVec3 CalculatePosition();
		glm::quat GetOrientation();
	private:
		glm::mat4 fProjectionMatrix, fViewMatrix;
		EVec3 fPosition, fRotation, fFocalPoint;

		bool fPanning, fRotating;
		EVec2 fInitialMousePosition;
		EVec3 fInitialFocalPoint, fInitialRotation;

		float fDistance;
		float fPanSpeed, fRotationSpeed, fZoomSpeed;

		float fPitch, fYaw;
	};

}