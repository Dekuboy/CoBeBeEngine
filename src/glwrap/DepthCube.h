#include <GL/glew.h>
#include <glm/glm.hpp>
#include "RenderTexture.h"

namespace glwrap
{
	class DepthCube : public RenderTexture
	{
	public:
		DepthCube(int width, int height);

		void clear();
	};
}