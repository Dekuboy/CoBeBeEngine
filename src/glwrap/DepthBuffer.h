#include <GL/glew.h>
#include <glm/glm.hpp>
#include "RenderTexture.h"

namespace glwrap
{
	class DepthBuffer : public RenderTexture
	{
		friend class Context;
	public:
		DepthBuffer(int width, int height);

		void clear();
	};
}