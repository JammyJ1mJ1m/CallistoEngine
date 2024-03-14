#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraDir;
	glm::vec3 up;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraRot;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 position; // proj * view
	Camera(glm::vec3 pPos, float pWidth, float pHeight);
	void MoveForward(float pMoveAmount);
	void Strafe(float pMoveAmount);
	void UpdateView();
	void Rotate(float yaw);

};
