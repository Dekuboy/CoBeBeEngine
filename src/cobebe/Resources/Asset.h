#ifndef _COBEBE_ASSET
#define _COBEBE_ASSET

#include <string>
#include <memory>
#include <glwrap/glwrap.h>

namespace cobebe
{
	/**
	* Parent class for loaded assets
	*/
	class Asset
	{
	public:

	protected:
		friend class Resources;

		std::string m_path; /// Folder path as identification
		std::weak_ptr<glwrap::Context> m_context; /// Pointer to context for OpenGL asset creation

		/**
		* \brief Activates once when loading a file
		*/
		virtual void onLoad(const std::string& _path);
	};
}

#endif