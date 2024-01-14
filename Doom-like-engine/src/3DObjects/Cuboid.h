#pragma once


#include "Figure.h"

class Cubiod : public Figure {
public:
	Cubiod();
	Cubiod(float x, float y, float z, float width, float height, float depth);
	~Cubiod();

	void draw() override;
	void update(glm::mat4& cameraMatrix) override;
};