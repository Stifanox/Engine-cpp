#pragma once

#include "Binder.h"
#include "VertexBuffer.h"

enum VectorSize
{
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4
};

class VertexArray : public Binder {
public:
	VertexArray();
	~VertexArray();

	void bind() override;
	void unbind() override;
	void linkVBO(VertexBuffer* vbo,VectorSize vectorSize ,unsigned int layoutPosition, int stride, int offset);
};