#include <GL/glew.h>
#include <glm/glm.hpp>
#include "RenderTexture.h"

namespace glwrap
{
	/**
	* \brief Fbo and TextureCube which stores depth values for shading
	*/
	class DepthCube : public RenderTexture
	{
	public:
		DepthCube(int width, int height);

#if defined(__EMSCRIPTEN__)
		/**
		* \brief Bind face to Frame Buffer to draw
		*/
		void bindFrameBuffer(int _face);
#endif

		/**
		* \brief Clear the DepthCube of previously generated values
		*/
		void clear();
	};
}