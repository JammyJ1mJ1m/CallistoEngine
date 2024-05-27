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

	float aspect = 800 / 800;
	float fov = glm::radians(45.0f);
	float near = 0.1f;
	float far = 100.0f;

	projection = glm::mat4(1.0f);
		projection = glm::perspective(fov, aspect, near, far);


	//glm::mat4 projection2 = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 500.0f);
	//projection = projection2;
	
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
	// std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
	cameraTarget = cameraPos + cameraDir;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}