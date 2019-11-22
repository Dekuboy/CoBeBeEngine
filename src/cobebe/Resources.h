#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include <string>
#include <memory>
#include <list>
#include "NonCopyable.h"

namespace cobebe
{
	class Resource
	{
	private:
		std::string m_path;
	};



	class Resources
	{
	public:
		template <class T>
		std::shared_ptr<T> load(std::string _path);
		template <class T>
		std::shared_ptr<T> create();

	private:
		std::list<std::shared_ptr<Resource>> m_resources;

	};



	class Mesh : private NonCopyable, public Resource
	{
	public:
		~Mesh();
		rend::Mesh getRMesh();

	private:
		rend::Mesh m_mesh;

	};



	class Texture : private NonCopyable, public Resource
	{
	public:
		~Texture();
		rend::Texture getRTexture();

	private:
		rend::Texture m_texture;

	};



	class Shader : private NonCopyable, public Resource
	{
	public:
		~Shader();
		rend::Shader getRShader();

	private:
		rend::Shader m_shader;

	};
}