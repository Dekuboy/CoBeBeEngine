#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Resources/Asset.h>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Renderer;

	/**
	* Stores a VertexArray to set in Renderer
	*/
	class Mesh : private NonCopyable, public Asset
	{
	public:

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::VertexArray> m_internal; /// Pointer to OpenGL VertexArray

		void onLoad(const std::string& _path);

	};


	/**
	* Stores a Texture to set in Renderer
	*/
	class Texture : private NonCopyable, public Asset
	{
	public:

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::Texture> m_internal; /// Pointer to OpenGL Texture

		void onLoad(const std::string& _path);

	};


	/**
	* Stores a Shader to set in Renderer
	*/
	class Shader : private NonCopyable, public Asset
	{
	public:

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::ShaderProgram> m_internal; /// Pointer to OpenGL ShaderProgram

		void onLoad(const std::string& _path);

	};
}