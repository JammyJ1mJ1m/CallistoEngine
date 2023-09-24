#include "main.h"
#include "Components/PointLight.h"
#include "Components/SpotLight.h"
#include "Components/DirectionalLight.h"

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


	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


#pragma endregion

	// build and compile our shader program
	// ------------------------------------
	int tex1, tex2, tex3;

	tex1 = lightShader.LoadTexture("Textures\\box.png", true);
	tex2 = lightShader.LoadTexture("Textures\\box_specular.png", true);
	tex3 = lightShader.LoadTexture("Textures\\box_emission.png", true);

	//shader.use();

	lightShader.use();
	//GLuint colourLoc = glGetUniformLocation(shader.ID, "colour");
	lightShader.setInt("material.diffuse", 0);
	lightShader.setInt("material.specular", 1);
	lightShader.setInt("material.emission", 2);

	//shader.setInt("texture2", 1);

	bool enable = false;

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	/*float pos[] = { 0.0f, 1.0f, 0.0f };
	glm::vec3 lightPos = glm::vec3(pos[0], pos[1], pos[2]);*/
	float dir[] = { 0.0f,-1.0f,0.0f };
	glm::vec3 lightDir = glm::vec3(dir[0], dir[1], dir[2]);
	float shininess = 0.078125f * 128;
	float emissionBrightness = 1.0f;

	float lightColour[] = { 0.5f, 0.5f, 0.5f };
	glm::vec3 lightCol = glm::vec3(lightColour[0], lightColour[1], lightColour[2]);

	// first pointlight

	float innerOuter[] = { 0.0f,-1.0f };
	glm::vec2 innerOuterV = glm::vec2(innerOuter[0], innerOuter[1]);


	glm::vec3 pointLightPositions[] = {
	   glm::vec3(0.0f,  1.0f,  0.0f),
	   glm::vec3(2.3f, -3.3f, -4.0f),
	   glm::vec3(-4.0f,  2.0f, -12.0f),
	   glm::vec3(0.0f,  0.0f, -3.0f)
	};

	PointLight lights[] = {
		PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[0]),
		PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[1]),
		PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[2]),
		PointLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightShader, pointLightPositions[3])
	};

	SpotLight spotLights[] = {
		SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),lightShader,pointLightPositions[0],12.5f,17.5f,lightDir),
		SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[1],12.5f,17.5f,lightDir),
		SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[2],12.5f,17.5f,lightDir),
		SpotLight(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.5f, 1.0f, 1.0f),lightShader,pointLightPositions[3],12.5f,17.5f,lightDir)
	};

	DirectionalLight sun = DirectionalLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightDir);


	int frame = 0;
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		frame++;
		// calcualte deltatime
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		DisplayFPS(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightShader.use();

		// material properties
		lightShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		lightShader.setFloat("material.shininess", shininess);
		lightShader.setFloat("material.emissionBrightness", emissionBrightness);

		// 4 point lights
		for (int i = 0; i < 4; i++)
		{
			//lights[i].position = pointLightPositions[i];
			lights[i].Run(pointLightPositions[i], i, &lightShader);
			spotLights[i].Run(pointLightPositions[i], i, &lightShader);
			spotLights[i].innerCutoff = glm::cos(glm::radians( innerOuter[0]));
			spotLights[i].outerCutoff = glm::cos(glm::radians(innerOuter[1]));
		}

		sun.Run(pointLightPositions[0], 0, &lightShader);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = cam.view;
		lightShader.setMat("projection", projection);
		lightShader.setMat("view", view);


		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.setMat("model", model);
		lightShader.setVec3("viewPos", cam.cameraPos);

		// texture 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, tex3);

		// render the cube
		//glBindVertexArray(cubeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 20; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			lightShader.setMat("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));


		model = glm::scale(model, glm::vec3(50.0f, 0.1f, 50.0f));
		lightShader.setMat("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// also draw the lamp object
		lightCubeShader.use();
		for (int i = 0; i < 4; i++)
		{
			lightCubeShader.setMat("projection", projection);
			lightCubeShader.setMat("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.05f)); // a smaller cube
			lightCubeShader.setMat("model", model);

			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		emissionBrightness = sin(glfwGetTime() * 1.0f) + 1.1f;
		//std::cout << emissionBrightness << std::endl;
		// ImGui stuff
		// -----------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Window");
		ImGui::Text("Hello there!");
		ImGui::Checkbox("Wireframe mode", &enable);

		for (int i = 0; i < sizeof(lights) / sizeof(lights[0]); i++)
		{
			float pos[] = { lights[i].position.x, lights[i].position.y, lights[i].position.z };
			std::stringstream ss;
			ss << "Light Pos: " << i;
			std::string s = ss.str();

			const char* output = s.c_str();

			ImGui::SliderFloat3(output, pos, -5.0f, 5.0f);
			lights[i].SetPosition(pos[0], pos[1], pos[2]);
			spotLights[i].SetPosition(pos[0], pos[1], pos[2]);

			pointLightPositions[i].x = pos[0];
			pointLightPositions[i].y = pos[1];
			pointLightPositions[i].z = pos[2];

			spotLights[i].direction.x = dir[0];
			spotLights[i].direction.y = dir[1];
			spotLights[i].direction.z = dir[2];
		}

		ImGui::SliderFloat3("Light Dir", dir, -1.0f, 1.0f);
		ImGui::SliderFloat2("falloff", innerOuter, 0.1f, 45.0f);
		ImGui::SliderFloat("Specular shininess", &shininess, 1.0f, 512.0f);
		//ImGui::SliderFloat("Emission shininess", &emissionBrightness, 0.0f, 5.0f);
		ImGui::ColorEdit4("Color", lightColour);
		ImGui::End();

		lightDir.x = dir[0];
		lightDir.y = dir[1];
		lightDir.z = dir[2];


		innerOuterV.x = innerOuter[1];
		innerOuterV.y = innerOuter[0];
		if (innerOuter[1] >= innerOuter[0])
		{
			innerOuter[0] = innerOuter[1];
		}

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