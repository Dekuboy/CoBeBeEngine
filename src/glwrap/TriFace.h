#ifndef _GLWRAP_TRIFACE
#define _GLWRAP_TRIFACE
#include <glm/glm.hpp>
namespace glwrap
{
	/**
	* \brief Describes the values of a models tris
	*/
	struct TriFace
	{
		glm::vec3 pa; //!< Position of vertex A
		glm::vec3 pb; //!< Position of vertex B
		glm::vec3 pc; //!< Position of vertex C

		glm::vec2 tca; //!< Texture position of vertex A
		glm::vec2 tcb; //!< Texture position of vertex B
		glm::vec2 tcc; //!< Texture position of vertex C

		glm::vec3 na; //!< Normal of Vertex A
		glm::vec3 nb; //!< Normal of Vertex B
		glm::vec3 nc; //!< Normal of Vertex C

		glm::vec3 tan; //!< Tangent of tri
		glm::vec3 bitan; //!< Bitangent of tri

		//glm::vec2 lmca;
		//glm::vec2 lmcb;
		//glm::vec2 lmcc;

		float getMaxX();
		float getMinX();
		float getMaxY();
		float getMinY();
		float getMaxZ();
		float getMinZ();
	};
}
#endif