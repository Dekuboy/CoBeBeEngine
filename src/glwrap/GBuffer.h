#include <glwrap/RenderTexture.h>

namespace glwrap
{
	/**
	* \brief Fbo and Textures for deferred rendering
	* -Textures hold: Position values
	*                 Normal values
	*                 Albedo and Specular values
	*/
	class GBuffer : public RenderTexture
	{
	public:
		GBuffer(int _width, int _height);
		~GBuffer();

		/**
		* Get Normal Buffer Texture Id
		*/
		GLuint getNId();
		/**
		* Get AlbedoSpec Buffer Texture Id
		*/
		GLuint getAsId();

	private:
		GLuint m_nId; //!< GL Id of Normal buffer Texture
		GLuint m_asId; //!< GL Id of AlbedoSpec buffer Texture

	};
}