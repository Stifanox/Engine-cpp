#pragma once
#include "../Core/VertexBuffer.h"
#include "../Core/VertexArray.h"
#include "../Core/ElementBuffer.h"
#include "../Core/Shader.h"
#include <glm.hpp>
#include <iostream>

class Figure
{
public:
	Shader* shader;
	VertexArray* vao;
	VertexBuffer* vbo;
	ElementBuffer* ebo;
	virtual ~Figure() {
		delete this->shader;
		delete this->ebo;
		delete this->vao;
		delete this->vbo;
	};

	virtual void draw() {
		this->vao->bind();
		this->ebo->bind();
		this->shader->bind();
		glDrawElements(GL_TRIANGLES, this->ebo->getIndicesSize(), GL_UNSIGNED_INT, nullptr);
		this->vao->unbind();
		this->ebo->unbind();
		this->shader->unbind();
	};
	virtual void update(glm::mat4& cameraMatrix) {
		this->shader->bind();
		this->shader->setUniform("view", cameraMatrix);
		this->shader->unbind();
	};
};
