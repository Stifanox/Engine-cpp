#pragma once

#include "Binder.h"
#include "GL/glew.h"
#include <vector>

class VertexBuffer : public Binder
{
public:
	VertexBuffer();
	VertexBuffer(std::vector<float>& vertexData);
	~VertexBuffer();


	void bind() override;
	void unbind() override;
private:
	std::vector<float> vertexData;
};

