#pragma once
#include <GLAD/glad.h>		
#include <string>
#include <glm/mat4x4.hpp>



// Created by  on 2024-06-17.
namespace Renderer {



	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		ShaderProgram(const std::string& vertexShader, std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);



	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID );
		bool m_isCompiled = false;
		GLuint m_ID =0;

				



	};

}// namespace Renderer

