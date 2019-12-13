#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Renderer;

	class Asset
	{
	public:
		virtual void onLoad(const std::string& path);

	private:
		friend class Resources;
		std::string m_path;
	};



	class Resources
	{
	public:
		template <class T>
		std::shared_ptr<T> load(std::string _path);

	private:
		std::list<std::shared_ptr<Asset>> m_resources;

	};



	class Mesh : private NonCopyable, public Asset
	{
	public:
		~Mesh();
		void onLoad(const std::string& path);

	private:
		friend class Renderer;
		//std::shared_ptr<rend::Mesh> m_internal;

	};



	class Texture : private NonCopyable, public Asset
	{
	public:
		~Texture();
		void onLoad(const std::string& path);

	private:
		friend class Material;
		//std::shared_ptr<rend::Texture> m_internal;

	};



	class Shader : private NonCopyable, public Asset
	{
	public:
		~Shader();
		void onLoad(const std::string& path);

	private:
		friend class Material;
		//std::shared_ptr<rend::Shader> m_internal;

	};
}