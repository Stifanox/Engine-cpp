#include "VertexBuffer.h"
#include <iostream>
#include "../Exceptions/DefaultOpenGLCall.h"

VertexBuffer::VertexBuffer(): vertexData({})
{
	throw DefaultOpenGLCall("Vertex buffer was called with default constructor");
}

VertexBuffer::VertexBuffer(std::vector<float>& vertexData): vertexData(vertexData)
{
	glGenBuffers(1, &this->bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), static_cast<void*>(vertexData.data()), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->bufferId);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
