#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glwrap/RenderTexture.h>

namespace glwrap
{
	class DepthBuffer : public RenderTexture
	{
	public:
		DepthBuffer(int _width, int _height);

		void clear();

	private:
		friend class Context;

	};
}