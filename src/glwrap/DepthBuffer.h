#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glwrap/RenderTexture.h>

namespace glwrap
{
	/**
	* \brief Fbo and Texture which stores depth values for shading
	*/
	class DepthBuffer : public RenderTexture
	{
	public:
		DepthBuffer(int _width, int _height);

		/**
		* \brief Clear the DepthBuffer of previously generated values
		*/
		void clear();

	private:
		friend class Context;

	};
}