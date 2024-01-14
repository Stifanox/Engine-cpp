#include "Shader.h"
#include <iostream>
#include "GL/glew.h"
#include <sstream>
#include <fstream>
#include <string>
#include "../Exceptions/DefaultOpenGLCall.h"

unsigned int Shader::createShader(const std::string& shader, int shaderType) {
	unsigned int shaderId = glCreateShader(shaderType);

	std::ifstream shaderFile(shader);
	std::string lineOfCode;
	std::stringstream shaderCode;

	while (getline(shaderFile, lineOfCode))
	{
		shaderCode << lineOfCode << "\n";
	}

	const std::string& tmp = shaderCode.str();
	const char* converted = tmp.c_str();

	glShaderSource(shaderId, 1, &converted, nullptr);

	glCompileShader(shaderId);

	return shaderId;
}


Shader::Shader()
{
	throw DefaultOpenGLCall("Shader was called with default constructor");
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	this->bufferId = glCreateProgram();
	unsigned int vertexShaderId = this->createShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fragmentShaderId = this->createShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(this->bufferId, vertexShaderId);
	glAttachShader(this->bufferId, fragmentShaderId);

	glLinkProgram(this->bufferId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

Shader::~Shader()
{
	glDeleteProgram(this->bufferId);
}

void Shader::bind()
{
	glUseProgram(this->bufferId);
}

void Shader::unbind()
{
	glUseProgram(0);
}



void Shader::setUniform(std::string uniformName, glm::mat4 matrix)
{
	this->bind();
	unsigned int locationOfShader = glGetUniformLocation(this->bufferId, uniformName.c_str());
	glUniformMatrix4fv(locationOfShader, 1, GL_FALSE, &matrix[0][0]);
	this->unbind();
}

void Shader::setUniform(std::string uniformName, glm::vec4 vector)
{
	this->bind();
	unsigned int locationOfShader = glGetUniformLocation(this->bufferId, uniformName.c_str());
	glUniform4fv(locationOfShader, 1, &vector[0]);
	this->unbind();
}
