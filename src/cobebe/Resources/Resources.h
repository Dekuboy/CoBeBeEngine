#ifndef _COBEBE_RESOURCES
#define _COBEBE_RESOURCES

#include <string>
#include <memory>
#include <list>

namespace cobebe
{
	class Asset;

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
			std::shared_ptr<Asset> assetCast = asset;
			assetCast->onLoad(_path);
			m_resources.push_back(asset);
			return asset;
		}

	private:
		friend class Core;

		std::list<std::shared_ptr<Asset>> m_resources; /// List of currently loaded assets
		std::weak_ptr<glwrap::Context> m_context; /// Pointer to context for OpenGL assets

	};
}
#endif