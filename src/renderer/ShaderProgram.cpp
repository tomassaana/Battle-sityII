#include "ShaderProgram.h"
#include <iostream>


namespace Renderer{
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID); // Delete the existing shader program to free up resources before moving the new one
		m_ID = shaderProgram.m_ID; // Move the shader program ID from the source object to the current object
		m_isCompiled = shaderProgram.m_isCompiled; // Move the compilation status from the source object to the current object
		
		shaderProgram.m_ID = 0; // Reset the source object's shader program ID to 0 to prevent accidental use after moving
		shaderProgram.m_isCompiled = false; // Reset the source object's compilation status to false
		return *this; // Return a reference to the current object after the move assignment is complete

	}
	ShaderProgram::ShaderProgram(ShaderProgram&& ShaderProgram) noexcept
	{

		m_ID = ShaderProgram.m_ID; // Move the shader program ID from the source object to the current object
		m_isCompiled = ShaderProgram.m_isCompiled; // Move the compilation status from the source object to the current object
		
		ShaderProgram.m_ID = 0; // Reset the source object's shader program ID to 0 to prevent accidental use after moving
		ShaderProgram.m_isCompiled = false; // Reset the source object's compilation status to false	

	}
	ShaderProgram::ShaderProgram(const std::string& vertexShader, std::string& fragmentShader)
	{

		GLuint vertexShaderID, fragmentShaderID;

		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) 
		{
			std::cerr << "ERROR::SHADER: Vertex shader compilation failed" << std::endl;
			return;
		}	

		

		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "ERROR::SHADER: Fragment shader compilation failed" << std::endl;
			glDeleteShader(vertexShaderID); // Clean up the vertex shader if fragment shader compilation fails
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID); // Attach the compiled vertex shader to the shader program
		glAttachShader(m_ID, fragmentShaderID); // Attach the compiled fragment shader to the shader program
		glLinkProgram(m_ID); // Link the shader program, which combines the vertex and fragment shaders into a single executable program that can be used for rendering

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			// Handle the error (e.g., log it)
			std::cerr << "ERROR::SHADER: Link program time error: \t" << infoLog << std::endl;
		
		}
		else
		{

			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID); // Clean up the vertex shader, as it is no longer needed after linking
		glDeleteShader(fragmentShaderID); // Clean up the fragment shader, as it is no longer needed after linking


	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID); // Delete the shader program when the ShaderProgram object is destroyed to free up resources

	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID); // Set the current active shader program to the one represented by this ShaderProgram object
	}

	

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{

		shaderID = glCreateShader(shaderType); // Create a shader object of the specified type (vertex or fragment) and store its ID in shaderID 
		const char* code =	source.c_str(); // Convert the shader source code from a std::string to a C-style string (const char*)
		glShaderSource(shaderID, 1, &code, nullptr); // Attach the shader source code to the shader object
		glCompileShader(shaderID); // Compile the shader

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar infoLog[1024];
				glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
				// Handle the error (e.g., log it)
				std::cerr << "ERROR::SHADER: Compile time error: \t" << infoLog << std::endl;
				return false;
			}

		return true;
	}

	void ShaderProgram::setInt(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value); 
	}



}