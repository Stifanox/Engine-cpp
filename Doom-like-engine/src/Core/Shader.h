#pragma once

#include "Binder.h"
#include <string>
#include <glm.hpp>


class Shader : public Binder
{
public:
	Shader();
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void bind() override;
	void unbind() override;
	void setUniform(std::string uniformName, glm::mat4 matrix);
	void setUniform(std::string uniformName, glm::vec4 vector);

private:
	unsigned int createShader(const std::string& shader, int shaderType);
};

