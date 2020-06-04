#pragma once

namespace Engine {

	struct ELight
	{
		glm::vec3 Direction;
		glm::vec3 Radiance;
	};

	typedef std::vector<ELight> ELightMap;

}