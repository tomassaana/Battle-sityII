#pragma once
#include <string>
#include <memory>
#include <map>


namespace Renderer
{
	class ShaderProgram;

}


class ResourceManager
{
public:
	ResourceManager(const std::string& exePath);
	~ResourceManager() = default;


	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string shaderName, 
														const std::string& vertexShaderPath,
														const std::string& fragmentShaderPath);
	
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName) const;



private:

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	std::string m_path;
	  
};
