#include "Engine.h"

namespace Engine
{
    EMat4 GetProjectionMatrix(ECameraComponent::CameraMode cameraMode, u32 screenWidth, u32 screenHeight) 
    {
		switch (cameraMode)
		{
		case ECameraComponent::CameraMode::ORTHOGRAPHIC:
			return glm::ortho(-1.0f, 1.0f, -((float) screenHeight) / ((float)screenWidth), ((float)screenHeight) / ((float)screenWidth));
		case ECameraComponent::CameraMode::PERSPECTIVE:
			return glm::perspective(30.0f, ((float)screenWidth) / ((float) screenHeight), 0.00001f, 100000.0f);
		}
    }
}