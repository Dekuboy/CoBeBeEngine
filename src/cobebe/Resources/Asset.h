#ifndef _COBEBE_ASSET
#define _COBEBE_ASSET

#include <cobebe/NonCopyable.h>
#include <string>
#include <memory>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Resources;

	/**
	* \brief Parent class for loaded assets
	*/
	class Asset : private NonCopyable
	{
	public:

	protected:
		friend class Resources;

		std::string m_path; //!< Folder path as identification
		std::weak_ptr<glwrap::Context> m_context; //!< Pointer to context for OpenGL asset creation
		std::weak_ptr<Resources> m_resources; //!< Pointer to Resources for Assets with multiple dependencies

		/**
		* \brief Activates once when loading a file
		*/
		virtual void onLoad(const std::string& _path);
	};
}

#endif