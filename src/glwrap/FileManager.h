#include <string>

class FileManager
{
public:
	static std::string returnPath(std::string _path);
	static std::string loadWin(std::string _path);

private:
	static void init();
	static bool m_isInit;
	static std::string m_fullPath;
	static std::string m_dirName;
	static std::string m_folderPath;
};