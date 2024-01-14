#pragma once

#include "Figure.h"
class Pyramid: public Figure {
public:
	Pyramid();
	Pyramid(float x, float y, float z, float baseSide, float height);
	~Pyramid();

	void draw() override;
	void update(glm::mat4& cameraMatrix) override;
};
