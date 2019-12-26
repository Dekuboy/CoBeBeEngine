#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include <cobebe/NonCopyable.h>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Renderer;

	/**
	* Parent class for loaded assets
	*/
	class Asset
	{
	public:
		/**
		* \brief Activates once when loading a file
		*/
		virtual void onLoad(const std::string& _path);

	protected:
		friend class Resources;
		std::string m_path; /// Folder path as identification
		std::weak_ptr<glwrap::Context> m_context; /// Pointer to context for OpenGL asset creation

	};


	/**
	* Holds and manages loaded file assets
	*/
	class Resources
	{
	public:
		/**
		* \brief Loads Asset of type (loads file if new Asset)
		*/
		template <class T>
		std::shared_ptr<T> load(std::string _path)
		{
			std::shared_ptr<T> asset;

			for (std::list<std::shared_ptr<Asset>>::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
			{
				asset = std::dynamic_pointer_cast<T>(*it);
				if (asset)
				{
					if (asset->m_path == _path)
					{
						return asset;
					}
				}
			}
			asset = std::make_shared<T>();
			asset->m_context = m_context;
			asset->onLoad(_path);
			m_resources.push_back(asset);
			return asset;
		}

	private:
		friend class Core;
		std::list<std::shared_ptr<Asset>> m_resources; /// List of currently loaded assets
		std::weak_ptr<glwrap::Context> m_context; /// Pointer to context for OpenGL assets

	};


	/**
	* Stores a VertexArray to set in Renderer
	*/
	class Mesh : private NonCopyable, public Asset
	{
	public:
		void onLoad(const std::string& _path);

	private:
		friend class Renderer;
		std::shared_ptr<glwrap::VertexArray> m_internal; /// Pointer to OpenGL VertexArray

	};


	/**
	* Stores a Texture to set in Renderer
	*/
	class Texture : private NonCopyable, public Asset
	{
	public:
		void onLoad(const std::string& _path);

	private:
		friend class Renderer;
		std::shared_ptr<glwrap::Texture> m_internal; /// Pointer to OpenGL Texture

	};


	/**
	* Stores a Shader to set in Renderer
	*/
	class Shader : private NonCopyable, public Asset
	{
	public:
		void onLoad(const std::string& _path);

	private:
		friend class Renderer;
		std::shared_ptr<glwrap::ShaderProgram> m_internal; /// Pointer to OpenGL ShaderProgram

	};
}