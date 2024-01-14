#include "Pyramid.h"
#include <iostream>
#include "gtc/matrix_transform.hpp"
#include "../Exceptions/DefaultFiguresCall.h"

//TODO: move all the buisness logic to figure class
Pyramid::Pyramid()
{
	throw DefaultFigureCall("Pyramid was called with default constructor");
}

Pyramid::Pyramid(float x, float y, float z, float baseSide, float height)
{
	std::vector <float> vertexInfo = {
		0.0f,0.0f,0.0f, 0.55f, 0.18f, 0.14f,
		baseSide,0.0f,0.0f, 0.69f, 0.44f, 0.06f,
		baseSide,0.0f,baseSide, 0.86f, 0.14f, 0.87f,
		0.0f,0.0f,baseSide, 0.15f, 0.59f, 0.66f,
		baseSide / 2.0f,height,baseSide / 2.0f, 0.87f, 0.25f, 0.7f,

	};

	std::vector <unsigned int> indices = {
		0,1,2,
		1,2,3,
		1,2,4,
		3,2,4,
		3,0,4,
		0,1,4
	};

	this->shader = new Shader("res/shader/default.vert", "res/shader/default.frag");
	this->vao = new VertexArray();
	this->ebo = new ElementBuffer(indices);
	this->vbo = new VertexBuffer(vertexInfo);


	this->vao->bind();
	this->ebo->bind();

	this->vao->linkVBO(this->vbo, VectorSize::THREE, 0, sizeof(float) * 6, 0);
	this->vao->linkVBO(this->vbo, VectorSize::THREE, 1, sizeof(float) * 6, sizeof(float) * 3);
	this->vao->unbind();
	this->ebo->unbind();

	this->shader->bind();

	glm::mat4 modelPosition = glm::mat4(1.0f);
	modelPosition = glm::translate(modelPosition, glm::vec3(x, y, z));
	// TODO: change aspect ratio 
	glm::mat4 perspective = glm::perspective(glm::radians(60.0f), 800.f / 800, 0.1f, 100.0f);

	this->shader->setUniform("model", modelPosition);
	this->shader->setUniform("projection", perspective);

	this->shader->unbind();
}
