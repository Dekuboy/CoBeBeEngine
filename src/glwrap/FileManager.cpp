#include <glwrap/FileManager.h>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#endif

bool FileManager::m_isInit = false;
std::string FileManager::m_fullPath = "";
std::string FileManager::m_dirName = "";
std::string FileManager::m_folderPath = "";

void FileManager::init()
{
	if (!m_isInit)
	{
		m_folderPath = "Resources/";
#if defined(WIN32)
		char strExePath[MAX_PATH];
		GetModuleFileName(NULL, strExePath, MAX_PATH);
		m_fullPath = strExePath;
		m_dirName = m_fullPath.substr(m_fullPath.find_last_of("\\"));
		m_folderPath = m_fullPath.substr(0, m_fullPath.length() - (m_dirName.length() - 1));
#endif
		m_isInit = true;
	}
}

std::string FileManager::returnPath(std::string _path)
{
	init();
	std::string path = _path;
#if defined(WIN32)
	int id = path.find_first_of('/');
	while (id > -1)
	{
		path.at(id) = '\\';
		id = path.find_first_of('/');
	}
#elif defined(__EMSCRIPTEN__)
	path = "";
	int itr = 0;
	while (itr < _path.length())
	{
		if ((_path.at(itr) == '\\') && (path.length() > 1))
		{
			if (path.at(path.length() - 1) != '/')
			{
				path.push_back('/');
			}
		}
		else
		{
			path.push_back(_path.at(itr));
		}
		itr++;
	}
	
#endif
	//printf("%s\n", _path.c_str());
	return m_folderPath + path;
}

std::string FileManager::loadWin(std::string _path)
{
	init();

	std::string contents;
	std::string path = _path;
#if defined(__EMSCRIPTEN__)
	path = "";
	int itr = 0;
	while (itr < _path.length())
	{
		if ((_path.at(itr) == '\\') && (path.length() > 1))
		{
			if (path.at(path.length() - 1) != '/')
			{
				path.push_back('/');
			}
		}
		else
		{
			path.push_back(_path.at(itr));
		}
		itr++;
	}
#endif
	//printf("%s\n", _path.c_str());
	std::ifstream file(m_folderPath + path);
	if (!file.is_open())
	{
		throw std::exception();
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			contents += line + "\n";
		}
	}
	file.close();

	return contents;
}