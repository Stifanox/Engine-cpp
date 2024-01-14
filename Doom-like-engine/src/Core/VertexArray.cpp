#include "VertexArray.h"
#include "GL/glew.h"
#include <iostream>

VertexArray::VertexArray() : Binder()
{
	glGenVertexArrays(1, &this->bufferId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->bufferId);
}

void VertexArray::bind()
{
	glBindVertexArray(this->bufferId);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::linkVBO(VertexBuffer* vbo, VectorSize vectorSize, unsigned int layoutPosition, int stride, int offset)
{
	vbo->bind();
	glVertexAttribPointer(layoutPosition, vectorSize, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(layoutPosition);
	vbo->unbind();
}


