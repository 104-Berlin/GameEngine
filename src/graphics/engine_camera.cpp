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

	void ECamera::Update(GLFWwindow* window)
	{
	}

	void ECamera::UpdateImGui()
	{
	}
}
