#include "Engine.h"


#ifdef M_PI
#undef M_PI
#endif

#define M_PI 3.14159f

namespace Engine {

	ECamera::ECamera(const glm::mat4& projectionMatrix)
		: fProjectionMatrix(projectionMatrix)
	{
		// Sensible defaults
		fPanSpeed = 0.0015f;
		fRotationSpeed = 0.002f;
		fZoomSpeed = 0.2f;

		fPosition = { 0, 0, 0 };
		fRotation = glm::vec3(0.0f, 0.0f, 0.0f);

		fFocalPoint = glm::vec3(0.0f);
		fDistance = glm::distance(fPosition, fFocalPoint);

		fYaw = 0;
		fPitch = 0;
		//fYaw = 3.0f * (float)M_PI / 4.0f;
		//fPitch = M_PI / 4.0f;
	}

	void ECamera::Update(EWindow* window)
	{
		const glm::vec2& mouse{ window->GetMouseX(), window->GetMouseY() };
		float speed = window->GetScroll();
		glm::vec2 delta = mouse - fInitialMousePosition;
		fInitialMousePosition = mouse;

		if (window->IsRightPressed())
			MousePan(delta);
		else if (window->IsLeftPressed())
			MouseRotate(delta);
			MouseZoom(speed);



		fPosition = CalculatePosition();
	


 		glm::quat orientation = GetOrientation();
		fRotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		fViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -fPosition);
	}

	void ECamera::MousePan(const glm::vec2& delta)
	{
		fFocalPoint += -GetRightDirection() * delta.x * fPanSpeed * fDistance;
		fFocalPoint += GetUpDirection() * delta.y * fPanSpeed * fDistance;
	}

	void ECamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		fYaw += yawSign * delta.x * fRotationSpeed;
		fPitch += delta.y * fRotationSpeed;
	}

	void ECamera::MouseZoom(float delta)
	{
		fDistance -= delta * fZoomSpeed;
		if (fDistance < 1.0f)
		{
			fFocalPoint += GetForwardDirection();
			fDistance = 1.0f;
		}
	}

	glm::vec3 ECamera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 ECamera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 ECamera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 ECamera::CalculatePosition()
	{
		return fFocalPoint - GetForwardDirection() * fDistance;
	}

	glm::quat ECamera::GetOrientation()
	{
		return glm::quat(glm::vec3(-fPitch, -fYaw, 0.0f));
	}

}
