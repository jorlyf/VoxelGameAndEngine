#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"

vx::Shader::Shader(const uint32_t id)
{
	_id = id;
}

vx::Shader::~Shader()
{
	glDeleteProgram(_id);
}

vx::Shader* vx::Shader::loadFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	// Reading Files
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexFilePath);
		fShaderFile.open(fragmentFilePath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		throw std::runtime_error("ERROR::vx::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "vx::SHADER::VERTEX: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
		throw std::runtime_error("vx::SHADER::FRAGMENT: compilation failed");
	}

	// Shader Program
	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		std::cerr << infoLog << std::endl;
		throw std::runtime_error("vx::SHADER::PROGRAM: linking failed");
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(id);
}

void vx::Shader::use()
{
	glUseProgram(_id);
}

void vx::Shader::setUniformMatrix(const std::string& name, const glm::mat4& matrix)
{
	GLuint uniformLocation = glGetUniformLocation(_id, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}
