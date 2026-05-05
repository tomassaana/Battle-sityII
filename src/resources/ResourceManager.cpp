#include	"../renderer/ShaderProgram.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(const std::string& exePath)
{
	size_t found = exePath.find_last_of("/\\");
	m_path = exePath.substr(0, found);
}