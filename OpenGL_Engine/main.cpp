#include "main.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void Draw(Shader pShader, int pTex1, int pTex2, float pTestFloat, unsigned int VAO, glm::vec3 pPositions[]);



// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

float color[] = { 1.0f, 1.0f,1.0f,0.0f };
glm::vec4 vecColor = glm::vec4(0.5f, 0.3f, 0.3f, 0.0f);
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), SCR_WIDTH, SCR_HEIGHT);

float dt = 0.0f;
float lastFrame = 0.0f;

// camera rotation
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
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

	glfwSetKeyCallback(window, key_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	bool testBool = false;
	float testFloat = 0.2f;


#pragma region Shader stuff

	Shader shader("Shaders/default.vert", "Shaders/default.frag");
	Shader lightShader("Shaders/Lighting/basicLight.vert", "Shaders/Lighting/basicLight.frag");
	Shader lightCubeShader("Shaders/light_cube.vert", "Shaders/light_cube.frag");
	
	
	// standard cube verts
	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#pragma region TexturedCube
	//float vertices[] = {
	//	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // A 0
	//	0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // B 1
	//	0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // C 2
	//	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // D 3
	//	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // E 4
	//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,   // F 5
	//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // G 6
	//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,   // H 7

	//	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // D 8
	//	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // A 9
	//	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // E 10
	//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // H 11
	//	0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // B 12
	//	0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,   // C 13
	//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // G 14
	//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,   // F 15

	//	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // A 16
	//	0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,   // B 17
	//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // F 18
	//	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // E 19
	//	0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // C 20
	//	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // D 21
	//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // H 22
	//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // G 23
	//};
	//// index data
	//unsigned int indices[] = {
	//	// front and back
	//	0, 3, 2,
	//	2, 1, 0,
	//	4, 5, 6,
	//	6, 7 ,4,
	//	// left and right
	//	11, 8, 9,
	//	9, 10, 11,
	//	12, 13, 14,
	//	14, 15, 12,
	//	// bottom and top
	//	16, 17, 18,
	//	18, 19, 16,
	//	20, 21, 22,
	//	22, 23, 20
	//};

	//unsigned int VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//// texture coord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);


	//// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);
#pragma endregion

#pragma endregion

	// build and compile our shader program
	// ------------------------------------
	int tex1, tex2;

	tex1 = shader.LoadTexture("Textures\\container.jpg");
	tex2 = shader.LoadTexture("Textures\\awesomeface.png", true);

	shader.use();

	//GLuint colourLoc = glGetUniformLocation(shader.ID, "colour");
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	bool enable = false;



	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(3.0f,  1.0f,  -5.0f),
	
	};

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float pos[] = { 3.0f, 1.0f, 2.0f };
	glm::vec3 lightPos = glm::vec3(pos[0], pos[1], pos[2]);
	float shininess = 0.078125f * 128;

	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// calcualte deltatime
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		DisplayFPS(window);

 		// Draw(lightShader, tex1,tex2,testFloat,VAO,cubePositions);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightShader.use();
		//lightShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		//lightShader.setVec3("lightColor", glm::vec3( 1.0f, 1.0f, 1.0f));
		//lightShader.setVec3("lightPos", lightPos);

		lightShader.setVec3("material.ambient", 0.0f,	0.05f,	0.05f);
		lightShader.setVec3("material.diffuse", 0.4f,	0.5f,	0.5f);
		lightShader.setVec3("material.specular", 0.04f,	0.7f,	0.7f);
		lightShader.setFloat("material.shininess", shininess);

		lightShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
		lightShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		lightShader.setVec3("light.position", lightPos);


		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = cam.view;
		lightShader.setMat("projection", projection);
		lightShader.setMat("view", view);
		

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.setMat("model", model);
		lightShader.setVec3("viewPos", cam.cameraPos);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// also draw the lamp object
		lightCubeShader.use();
		lightCubeShader.setMat("projection", projection);
		lightCubeShader.setMat("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.setMat("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// ImGui stuff
		// -----------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Window");
		ImGui::Text("Hello there!");
		ImGui::Checkbox("Wireframe mode", &enable);
		ImGui::SliderFloat("SliderX", &pos[0], -5.0f, 5.0f);
		ImGui::SliderFloat("SliderY", &pos[1], -5.0f, 5.0f);
		ImGui::SliderFloat("SliderZ", &pos[2], -5.0f, 5.0f);
		ImGui::SliderFloat("Specular shininess", &shininess, 1.0f, 512.0f);
		ImGui::ColorEdit4("Color", color);
		ImGui::End();

		lightPos.x = pos[0];
		lightPos.y = pos[1];
		lightPos.z = pos[2];
		

		if (enable)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		// converting imgui color into the vec4 color
		vecColor.x = color[0];
		vecColor.y = color[1];
		vecColor.z = color[2];
		vecColor.w = color[3];

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
	//glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader.ID);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	// 

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


void Draw(Shader pShader, int pTex1, int pTex2, float pTestFloat, unsigned int VAO, glm::vec3 pPositions[])
{
	// render
		// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTex1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pTex2);

	// render container
	pShader.use();
	pShader.setFloat("mixAmount", pTestFloat);
	glm::mat4 trans = glm::mat4(1.0f);

	//shader.setMat("model", model);
	pShader.setMat("view", cam.view);
	pShader.setMat("projection", cam.projection);

	pShader.setVec3("newCol", vecColor);

	//glBindVertexArray(VAO);


	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pPositions[i]);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		float angle = 0.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		pShader.setMat("model", model);

		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
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
		std::cout << "W pressed" << std::endl;
		cam.MoveForward(camSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		std::cout << "S pressed" << std::endl;
		cam.MoveForward(-camSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		std::cout << "A pressed" << std::endl;
		cam.Strafe(-camSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		std::cout << "D pressed" << std::endl;
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
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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