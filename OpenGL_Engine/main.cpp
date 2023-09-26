#include "main.h"
#include "Components/PointLight.h"
#include "Components/SpotLight.h"
#include "Components/DirectionalLight.h"
#include "model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// ===================================
// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

float color[] = { 1.0f, 1.0f,1.0f,0.0f };
glm::vec4 vecColor = glm::vec4(0.5f, 0.3f, 0.3f, 0.0f);
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), SCR_WIDTH, SCR_HEIGHT);

// timing
float dt = 0.0f;
float lastFrame = 0.0f;

// camera rotation
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
float fov = 45.0f;

bool lastState = false;

void DisplayFPS(GLFWwindow* window)
{
	std::stringstream ss;
	ss << "OpenGL" << " " << " [" << 1.0 / dt << " FPS]";
	glfwSetWindowTitle(window, ss.str().c_str());
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// imgui initialisation 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	//Shader shader("Shaders/default.vert", "Shaders/default.frag");
	Shader shader("Shaders/Lighting/basicLight.vert", "Shaders/Lighting/basicLight.frag");

	PointLight point1 = PointLight(
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		shader,
		glm::vec3(5.0f,6.0f,0.0f)
		);


#pragma region Light stuff

	//Shader lightShader("Shaders/Lighting/basicLight.vert", "Shaders/Lighting/basicLight.frag");

	//float dir[] = { 0.0f,-1.0f,0.0f };
	//glm::vec3 lightDir = glm::vec3(dir[0], dir[1], dir[2]);
	//float shininess = 0.078125f * 128;
	//float emissionBrightness = 1.0f;

	//float lightColour[] = { 0.5f, 0.5f, 0.5f };
	//glm::vec3 lightCol = glm::vec3(lightColour[0], lightColour[1], lightColour[2]);

	//// first pointlight

	//float innerOuter[] = { 17.5f,12.5f };
	//glm::vec2 innerOuterV = glm::vec2(innerOuter[0], innerOuter[1]);


	//glm::vec3 pointLightPositions[] = {
	//   glm::vec3(0.0f,  1.0f,  0.0f),
	//   glm::vec3(2.3f, -3.3f, -4.0f),
	//   glm::vec3(-4.0f,  2.0f, -12.0f),
	//   glm::vec3(0.0f,  0.0f, -3.0f)
	//};

	//PointLight lights[] = {
	//	PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[0]),
	//	PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[1]),
	//	PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[2]),
	//	PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[3])
	//};

	//SpotLight spotLights[] = {
	//	SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),lightShader,pointLightPositions[0],12.5f,17.5f,lightDir),
	//	SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[1],12.5f,17.5f,lightDir),
	//	SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[2],12.5f,17.5f,lightDir),
	//	SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[3],12.5f,17.5f,lightDir)
	//};

	//DirectionalLight sun = DirectionalLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightDir);
#pragma endregion

	Model model1 = Model("resources/geometry/backpack/backpack.obj");
	//Model model1 = Model("resources/geometry/TCube/TCube.obj");
	int frame = 0;
	
	glEnable(GL_DEPTH_TEST);

	float pos[] = { point1.position.x,point1.position.y, point1.position.z };

	bool enable = false;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		shader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = cam.view;
		shader.setMat("projection", projection);
		shader.setMat("view", view);


		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // translate it down so it's at the center of the scene
		
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		shader.setMat("model", model);
		model1.Draw(shader);
		point1.Run(glm::vec3(0.5f, 0.5f, 0.5f), 0, &shader);

		// ImGui stuff
		// -----------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Window");
		ImGui::Text("Hello there!");
		ImGui::Checkbox("Wireframe mode", &enable);
		

		ImGui::SliderFloat3("Light Pos", pos, -10.0f, 10.0f);
		//ImGui::SliderFloat2("falloff", innerOuter, 0.1f, 45.0f);
		//ImGui::SliderFloat("Specular shininess", &shininess, 1.0f, 512.0f);
		////ImGui::SliderFloat("Emission shininess", &emissionBrightness, 0.0f, 5.0f);
		//ImGui::ColorEdit4("Color", lightColour);
		ImGui::End();

		point1.position.x = pos[0];
		point1.position.y = pos[1];
		point1.position.z = pos[2];

		if (enable)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// input
		// -----
		processInput(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// de allocate resources


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	float camSpeed = 5.0f * dt;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.MoveForward(camSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.MoveForward(-camSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.Strafe(-camSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.Strafe(camSpeed);
	}
}

bool enableMouse = false;

// called every time a key is pressed/released/repeated
// 0 = key released; 1 = key pressed; 2 = key repeated.
// -------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == 1)
	{
		enableMouse = !enableMouse;

		if (enableMouse)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
		}
		else if (!enableMouse)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (enableMouse)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;
		//glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);


		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cam.cameraFront = glm::normalize(front);
		cam.UpdateView();
	}

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//cam.ProcessMouseScroll(static_cast<float>(yoffset));
}