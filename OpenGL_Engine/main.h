#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include<sstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Shader.h"
#include "stb_image.h"

#include "Camera.h"

#include "model.h"


//#include "imgui_impl_opengl3.h"

class main
{
public:
	void renderScene(Shader& shader, Model& boxModel);

};