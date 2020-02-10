#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace glwrap
{
	struct Face
	{
		glm::vec3 pa;
		glm::vec3 pb;
		glm::vec3 pc;

		glm::vec2 tca;
		glm::vec2 tcb;
		glm::vec2 tcc;

		glm::vec3 na;
		glm::vec3 nb;
		glm::vec3 nc;

		glm::vec3 tan;
		glm::vec3 bitan;

		glm::vec2 lmca;
		glm::vec2 lmcb;
		glm::vec2 lmcc;
	};

	class Context;

	class Part
	{

	};
}