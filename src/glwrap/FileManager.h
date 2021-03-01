#include <string>

/**
* \brief Manages the path when opening files 
*/
class FileManager
{
public:
	/**
	* \brief Retrieve path to the folder holding the application
	*/
	static std::string returnPath(std::string _path);
	/**
	* \brief Return contents of file in string
	*/
	static std::string loadWin(std::string _path);

private:
	static bool m_isInit; //!< Checks if variables have been set for use
	static std::string m_fullPath; //!< Full path to application
	static std::string m_dirName; //!< Name of Application
	static std::string m_folderPath; //!< Path to the folder holding the application

	/**
	* \brief If base application hasn't been found, retrieve it
	*/
	static void init();

};