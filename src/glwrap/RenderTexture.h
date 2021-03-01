#ifndef _GLWRAP_RENDTEXTURE
#define _GLWRAP_RENDTEXTURE
#include <glwrap/Texture.h>

namespace glwrap
{
	/**
	* \brief Texture that a ShaderProgram can draw to
	*/
	class RenderTexture : public Texture
	{
	public:
		RenderTexture(int _width, int _height);
		RenderTexture(int _width, int _height, int _multisamples);
		RenderTexture(int _width, int _height, bool _base);

		/**
		* \brief Retrieve the frame buffer Id
		*/
		GLuint getFbId();
		/**
		* \brief When multisampling, retrieve the sample total
		*/
		int getSamples();
		/**
		* \brief Clear the Texture of colour
		*/
		virtual void clear();

	protected:
		GLuint m_fbo; //!< Id of frame buffer in GL
		int m_multisamples; //!< Number of samples when multisampling

	};
}

#endif