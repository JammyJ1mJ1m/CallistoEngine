#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vector.h"

class Camera
{
private:
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

	Camera() {}	// Constructor? (the {} brackets) are needed here.

	// static Camera mInstance;

public:


	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static Camera& getInstance()
	{
		static Camera    instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	Camera(const glm::vec3 pPos, const float pWidth, const float pHeight);
	void MoveForward(const float pMoveAmount);
	void MoveUp(const float pMoveAmount);
	void Strafe(const float pMoveAmount);
	void UpdateView();
	void Rotate(const float pYaw);

	glm::mat4 GetView() const { return view; }
	glm::mat4 GetProjection() const { return projection; }
	Vector3f GetPosition() const;
	Vector3f GetDirection() const;
	Vector3f GetRight() const;
	Vector3f GetUp() const;

};
