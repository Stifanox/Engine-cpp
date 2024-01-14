#include "Player.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include "../Exceptions/DefaultConstructorCall.h"

Player::Player()
{
	throw DefaultConstructorCall();
}

Player::Player(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) : cameraSpeed(10.0f)
{
	this->cameraFront = cameraFront;
	this->cameraPos = cameraPos;
	this->cameraUp = cameraUp;

	this->cameraView = glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

glm::mat4 Player::getViewMatrix()
{
	return this->cameraView;
}

void Player::moveLeft(float deltaTime)
{
	this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->cameraSpeed * deltaTime;
}

void Player::moveRight(float deltaTime)
{
	this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp))* this->cameraSpeed * deltaTime;
}

void Player::moveForward(float deltaTime)
{
	this->cameraPos += this->cameraSpeed * deltaTime * cameraFront;
}

void Player::moveBackward(float deltaTime)
{
	this->cameraPos -= this->cameraSpeed * deltaTime * cameraFront;
}

void Player::updateViewMatrix()
{
	this->cameraView = glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

void Player::updateCameraFront(float yaw, float pitch)
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->cameraFront = glm::normalize(direction);
}

