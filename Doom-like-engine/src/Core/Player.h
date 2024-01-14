#pragma once

#include <glm.hpp>
#include <GLFW/glfw3.h>
class Player {
public:
	Player();
	Player(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

	glm::mat4 getViewMatrix();

	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);

	void updateViewMatrix();

	void updateCameraFront(float yaw,float pitch);

private:
	float cameraSpeed;
	glm::mat4 cameraView;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

};