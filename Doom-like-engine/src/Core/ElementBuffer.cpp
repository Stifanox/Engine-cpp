#include "ElementBuffer.h"
#include "GL/glew.h"
#include <iostream>
#include "../Exceptions/DefaultConstructorCall.h"

ElementBuffer::ElementBuffer()
{
	
	//throw DefaultConstructorCall();
}

ElementBuffer::ElementBuffer(std::vector<unsigned int> indices): indices(indices)
{
	glGenBuffers(1, &this->bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferId);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), static_cast<void*>(this->indices.data()), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &this->bufferId);
}

void ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferId);
}

void ElementBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int ElementBuffer::getIndicesSize()
{
	return this->indices.size();
}
