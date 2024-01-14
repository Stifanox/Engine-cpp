#pragma once
#include "../Core/VertexBuffer.h"
#include "../Core/VertexArray.h"
#include "../Core/ElementBuffer.h"
#include "../Core/Shader.h"
#include <glm.hpp>
class Figure
{
public:
	Shader* shader;
	VertexArray* vao;
	VertexBuffer* vbo;
	ElementBuffer* ebo;
	virtual ~Figure() {};

	virtual void draw() = 0;
	virtual void update(glm::mat4& cameraMatrix) = 0;
};
