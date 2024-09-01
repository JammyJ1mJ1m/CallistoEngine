#include "Camera.h"
#include <iostream>
#include "Game.h"

Camera::Camera(const glm::vec3 pPos, const float pWidth, const float pHeight)
{
	yaw = -90.0f;
	pitch = 0.0f;

	cameraPos = pPos;
	cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraDir = glm::normalize(cameraPos - cameraTarget);

	cameraRight = glm::normalize(glm::cross(up, cameraDir));
	cameraUp = glm::cross(cameraDir, cameraRight);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	mMoveSpeedModifier = 1.0f;


	/*float aspect = pWidth / pHeight;
	float fov = glm::radians(45.0f);
	float near = 0.1f;
	float far = 1000.0f;

	projection = glm::mat4(1.0f);
		projection = glm::perspective(fov, aspect, near, far);*/

	UpdateProjection(pWidth, pHeight);
	mFov = 45.0f;
	mWidth = pWidth;
	mHeight = pHeight;

	//glm::mat4 projection2 = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 500.0f);
	//projection = projection2;

	UpdateView();


	// mInstance = this;
}

void Camera::MoveForward(const float pMoveAmount)
{
	cameraPos += cameraFront * mMoveSpeedModifier * pMoveAmount * Game::GetGame()->GetDeltaTime();
	mMoveSpeedModifier = 1.0f;

	UpdateView();
}

void Camera::Strafe(const float pMoveAmount)
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * mMoveSpeedModifier * pMoveAmount * Game::GetGame()->GetDeltaTime();;
	mMoveSpeedModifier = 1.0f;

	UpdateView();

}

void Camera::MoveUp(const float pMoveAmount)
{
	cameraPos += cameraUp * mMoveSpeedModifier * pMoveAmount * Game::GetGame()->GetDeltaTime();;
	mMoveSpeedModifier = 1.0f;

	UpdateView();
}

void Camera::UpdateView()
{
	// std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
	cameraTarget = cameraPos + cameraDir;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}


void Camera::Rotate(const float pYaw)
{
	float yawRadians = glm::radians(pYaw);
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yawRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	cameraDir = glm::normalize(glm::vec3(rotation * glm::vec4(cameraDir, 0.0f)));

	cameraFront = cameraDir;
	cameraFront *= -1.0f;

	cameraRight = glm::normalize(glm::cross(up, cameraDir));
	cameraUp = glm::cross(cameraDir, cameraRight);

	UpdateView();
}

const void Camera::IncreaseSpeedMod(const float pModifer)
{
	mMoveSpeedModifier = pModifer;
}

Vector3f Camera::GetPosition() const
{
	Vector3f vec;
	vec.SetX(cameraPos.x);
	vec.SetY(cameraPos.y);
	vec.SetZ(cameraPos.z);
	return vec;
}

Vector3f Camera::GetDirection() const
{
	Vector3f vec;
	vec.SetX(cameraDir.x);
	vec.SetY(cameraDir.y);
	vec.SetZ(cameraDir.z);
	return vec;
}

Vector3f Camera::GetRight() const
{
	Vector3f vec;
	vec.SetX(cameraRight.x);
	vec.SetY(cameraRight.y);
	vec.SetZ(cameraRight.z);
	return vec;
}

Vector3f Camera::GetUp() const
{
	Vector3f vec;
	vec.SetX(cameraUp.x);
	vec.SetY(cameraUp.y);
	vec.SetZ(cameraUp.z);
	return vec;
}

void Camera::UpdateProjection(const float pWidth, const float pHeight, const float fov, const float near, const float far)
{
	float aspect = pWidth / pHeight;
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::HandleMouse(const float xpos, const float ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction = cameraFront;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	UpdateView();
}