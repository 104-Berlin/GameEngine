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
		fRotation = EVec3(0.0f, 0.0f, 0.0f);

		fFocalPoint = EVec3(0.0f);
		fDistance = glm::distance(fPosition, fFocalPoint);

		fYaw = 0;
		fPitch = 0;
		//fYaw = 3.0f * (float)M_PI / 4.0f;
		//fPitch = M_PI / 4.0f;
	}

	void ECamera::Update(const ERef<EWindow>& window)
	{
		const EVec2& mouse{ window->GetMouseX(), window->GetMouseY() };
		float speed = window->GetScroll();
		EVec2 delta = mouse - fInitialMousePosition;
		fInitialMousePosition = mouse;

		if (window->IsRightPressed())
			MousePan(delta);
		else if (window->IsLeftPressed())
			MouseRotate(delta);
			MouseZoom(speed);



		fPosition = CalculatePosition();
	


 		glm::quat orientation = GetOrientation();
		fRotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		fViewMatrix = glm::translate(glm::mat4(1.0f), EVec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -fPosition);
	}

	void ECamera::UpdateImGui()
	{
		EVec2 mouse = {ImGui::GetMousePos().x, ImGui::GetMousePos().y};
		ImGuiIO& io = ImGui::GetIO();
		float speed = io.MouseWheel;
		
		EVec2 delta = mouse - fInitialMousePosition;
		fInitialMousePosition = mouse;

		if (ImGui::IsItemHovered())
		{
			if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
			{
				MousePan(delta);
			}
			else if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
			{
				MouseRotate(delta);
			}
			MouseZoom(speed);
		}

		fPosition = CalculatePosition();

		glm::quat orientation = GetOrientation();
		fRotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		fViewMatrix = glm::translate(glm::mat4(1.0f), EVec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -fPosition);
	}

	void ECamera::MousePan(const EVec2& delta)
	{
		fFocalPoint += -GetRightDirection() * delta.x * fPanSpeed * fDistance;
		fFocalPoint += GetUpDirection() * delta.y * fPanSpeed * fDistance;
	}

	void ECamera::MouseRotate(const EVec2& delta)
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

	EVec3 ECamera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), EVec3(0.0f, 1.0f, 0.0f));
	}

	EVec3 ECamera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), EVec3(1.0f, 0.0f, 0.0f));
	}

	EVec3 ECamera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), EVec3(0.0f, 0.0f, -1.0f));
	}

	EVec3 ECamera::CalculatePosition()
	{
		return fFocalPoint - GetForwardDirection() * fDistance;
	}

	glm::quat ECamera::GetOrientation()
	{
		return glm::quat(EVec3(-fPitch, -fYaw, 0.0f));
	}

}
