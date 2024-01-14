#include "Cuboid.h"
#include <iostream>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "../Exceptions/DefaultConstructorCall.h"

Cubiod::Cubiod()
{
	throw DefaultConstructorCall();
}

Cubiod::Cubiod(float x, float y, float z, float width, float height, float depth)
{
	std::vector <float> vertexInfo = {
		0.0f,0.0f,0.0f, 0.55f, 0.18f, 0.14f,
		width,0.0f,0.0f, 0.69f, 0.44f, 0.06f,
		width,height,0.0f, 0.87f, 0.25f, 0.7f,
		0.0f,height,0.0f, 0.86f, 0.14f, 0.87f,
		0.0f,height,depth, 0.15f, 0.59f, 0.66f,
		width,height,depth, 0.3f, 0.74f, 0.33f,
		width,0.0f,depth, 0.2f, 0.89f, 0.61f,
		0.0f,0.0f,depth, 0.75f, 0.03f, 0.64f
	};


	std::vector <unsigned int> indices = {
		0,1,2,//front
		0,3,2,
		2,3,4, //up
		4,5,6,
		4,7,6, //back
		6,5,4,
		0,1,7, //down
		7,6,1,
		0,3,4, //left
		0,7,4,
		1,2,5, //right
		1,6,5
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

Cubiod::~Cubiod()
{
	delete this->shader;
	delete this->ebo;
	delete this->vao;
	delete this->vbo;
}

void Cubiod::draw()
{
	this->vao->bind();
	this->ebo->bind();
	this->shader->bind();
	glDrawElements(GL_TRIANGLES, this->ebo->getIndicesSize(), GL_UNSIGNED_INT, nullptr);
	this->vao->unbind();
	this->ebo->unbind();
	this->shader->unbind();
}

void Cubiod::update(glm::mat4& cameraMatrix)
{
	this->shader->bind();
	this->shader->setUniform("view", cameraMatrix);
	this->shader->unbind();
}
