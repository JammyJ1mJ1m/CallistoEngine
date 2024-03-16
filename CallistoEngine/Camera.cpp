#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3 pPos, const float pWidth, const float pHeight)
{
	cameraPos = pPos;
	cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraDir = glm::normalize(cameraPos - cameraTarget);

	cameraRight = glm::normalize(glm::cross(up, cameraDir));
	cameraUp = glm::cross(cameraDir, cameraRight);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	projection = glm::perspective(glm::radians(45.0f), (float)pWidth / (float)pHeight, 0.1f, 100.0f);
	UpdateView();


	// mInstance = this;
}

void Camera::MoveForward(const float pMoveAmount)
{
	cameraPos += cameraFront * pMoveAmount;
	UpdateView();
}

void Camera::Strafe(const float pMoveAmount)
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * pMoveAmount;
	UpdateView();

}

void Camera::UpdateView()
{
	std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
	cameraTarget = cameraPos + cameraDir;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}