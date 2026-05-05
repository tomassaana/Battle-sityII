#include	"../renderer/ShaderProgram.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>


ResourceManager::ResourceManager(const std::string& exePath)
{
	size_t found = exePath.find_last_of("/\\");
	m_path = exePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string shaderName, 
																	const std::string& vertexShaderPath,
																	const std::string& fragmentShaderPath)
{
	
	std::string vertexString = getFileString(vertexShaderPath);
	if(vertexString.empty())
	{
		std::cerr << "Failed to load vertex shaderString is EMPTY: " << vertexShaderPath << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentShaderPath);
	if (fragmentString.empty())
	{
		std::cerr << "Failed to load fragment shaderString is EMPTY: " << fragmentShaderPath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Failed to compile shader: " << shaderName << std::endl;
	return nullptr;

}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{

	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
		if (it != m_shaderPrograms.end())
		{
		return it->second;
		}
		std::cerr << "Failed to find shader! :\t " << shaderName << std::endl;
		return nullptr;

}

std::string ResourceManager::getFileString(const std::string& relativePath) const
{
	std::ifstream f;
	f.open(m_path + "/" + relativePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cerr << "Failed to open file: " << relativePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();

}




