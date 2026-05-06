#include "Texture2D.h"

namespace Renderer {

		Texture2D::Texture2D(const GLuint width, 
							const GLuint height, 
							const unsigned char* data, 
							const unsigned int channels, 
							const GLenum filter, 
							const GLenum wrapMode)
			: m_width(width), 
				m_height(height)
	{

			m_mode = channels == 4 ? GL_RGBA : GL_RGB;// Determine the appropriate format based on the number of channels

			glGenTextures(1, &m_ID);
			glActiveTexture(GL_TEXTURE0); // Activate the texture unit before binding the texture
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode); // Set texture parameters for wrapping and filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);// Set texture parameters for wrapping and filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);// Set texture parameters for wrapping and filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);// Set texture parameters for wrapping and filtering
			glGenerateMipmap(GL_TEXTURE_2D);// Generate mipmaps for the texture

			glBindTexture(GL_TEXTURE_2D, 0);// Unbind the texture after setting it up
	}

		Texture2D& Texture2D::operator=(Texture2D&& texture2d) noexcept
		{
			glDeleteTextures(1, &m_ID);
			m_ID = texture2d.m_ID; 
			texture2d.m_ID = 0;
			m_mode = texture2d.m_mode;
			m_width = texture2d.m_width;
			m_height = texture2d.m_height;
			return *this;
		}

		Texture2D::Texture2D(Texture2D&& texture2d) noexcept
		{
			m_ID = texture2d.m_ID;
			texture2d.m_ID = 0;
			 m_mode = texture2d.m_mode;
			 m_width = texture2d.m_width;
			 m_height = texture2d.m_height;	
		}


		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_ID);
		}

		void Texture2D::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}



}