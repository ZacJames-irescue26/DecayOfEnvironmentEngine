#include "pch.h"
#include "Engine/Renderer/Shader.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"
namespace DOE_Engine
{


	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(VertexShader, 1, &source, 0);

		glCompileShader(VertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(VertexShader);

			DOE_CORE_ERROR("{0}", infoLog.data());
			DOE_CORE_ASSERT(false, "Vertex shader compilaiton error");
			return;
		}

		GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragmentSrc.c_str();
		glShaderSource(FragmentShader, 1, &source, 0);

		glCompileShader(FragmentShader);


		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(FragmentShader);
			glDeleteShader(VertexShader);


			DOE_CORE_ERROR("{0}", infoLog.data());
			DOE_CORE_ASSERT(false, "Fragment shader compilaiton error");
			return;
		}

		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, VertexShader);
		glAttachShader(m_RendererID, FragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			DOE_CORE_ERROR("{0}", infoLog.data());
			DOE_CORE_ASSERT(false, "linking error");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, VertexShader);
		glDetachShader(m_RendererID, FragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(Location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}