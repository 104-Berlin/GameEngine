#include "Engine.h"


#ifdef M_PI
#undef M_PI
#endif

#define M_PI 3.14159f

namespace Engine {

	ECamera::ECamera(const glm::mat4& projectionMatrix)
		: fProjectionMatrix(projectionMatrix)
	{
	}

	void ECamera::Update(const ERef<EWindow>& window)
	{
	}

	void ECamera::UpdateImGui()
	{
	}
	
	void ECamera::SetCameraSize(ECameraComponent::CameraMode cameraMode, u32 width, u32 height) 
	{
		if (fScreenHeight == height && fScreenWidth == width) { return; }

		switch (cameraMode)
		{
		case ECameraComponent::CameraMode::ORTHOGRAPHIC:
			fProjectionMatrix = glm::ortho(-1.0f, 1.0f, -((float) height) / ((float)width), ((float)height) / ((float)width));
			break;
		
		case ECameraComponent::CameraMode::PERSPECTIVE:
			fProjectionMatrix = glm::perspective(30.0f, ((float)width) / ((float) height), 0.00001f, 100000.0f);
			break;
		}
	}
}
