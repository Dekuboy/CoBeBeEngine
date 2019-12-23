#include <glwrap/FileManager.h>
#include <fstream>
#include <Windows.h>

bool FileManager::m_isInit = false;
std::string FileManager::m_fullPath = "";
std::string FileManager::m_dirName = "";
std::string FileManager::m_folderPath = "";

void FileManager::init()
{
	if (!m_isInit)
	{
		char strExePath[MAX_PATH];
		GetModuleFileName(NULL, strExePath, MAX_PATH);
		m_fullPath = strExePath;
		m_dirName = m_fullPath.substr(m_fullPath.find_last_of("\\"));
		m_folderPath = m_fullPath.substr(0, m_fullPath.length() - (m_dirName.length() - 1));
		m_isInit = true;
	}
}

std::string FileManager::returnPath(std::string _path)
{
	init();

	return m_folderPath + _path;
}

std::string FileManager::loadWin(std::string _path)
{
	init();

	std::string contents;

	std::ifstream file(m_folderPath + _path);

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