#pragma once

namespace Engine {

	class ECamera
	{
	public:
		ECamera(const glm::mat4& projectionMatrix);

		void Update(EWindow* window);

		inline float GetDistance() const { return fDistance; }
		inline void SetDistance(float distance) { fDistance = distance; }

		inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { fProjectionMatrix = projectionMatrix; }

		const glm::mat4& GetProjectionMatrix() const { return fProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return fViewMatrix; }

		glm::vec3 GetUpDirection();
		glm::vec3 GetRightDirection();
		glm::vec3 GetForwardDirection();
		const glm::vec3& GetPosition() const { return fPosition; }
	private:
		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition();
		glm::quat GetOrientation();
	private:
		glm::mat4 fProjectionMatrix, fViewMatrix;
		glm::vec3 fPosition, fRotation, fFocalPoint;

		bool fPanning, fRotating;
		glm::vec2 fInitialMousePosition;
		glm::vec3 fInitialFocalPoint, fInitialRotation;

		float fDistance;
		float fPanSpeed, fRotationSpeed, fZoomSpeed;

		float fPitch, fYaw;
	};

}