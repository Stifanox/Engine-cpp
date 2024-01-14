#pragma once

#include "Binder.h"
#include <vector>

class ElementBuffer : public Binder {
public:
	ElementBuffer();
	ElementBuffer(std::vector<unsigned int> indices);
	~ElementBuffer();


	void bind() override;
	void unbind() override;
	int getIndicesSize();
private:
	std::vector<unsigned int> indices;
};
