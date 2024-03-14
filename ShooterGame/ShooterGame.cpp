#include "ShooterGame.h"

void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();
	mRenderSystem = new SystemRender(_renderer);

	// other game setup logic
	_gameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), _window->GetWindowWidth(), _window->GetWindowHeight());

	std::vector<Vertex> vertices = {
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{ 0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{ 0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{ 0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{-0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
							 
	{-0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{ 0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{-0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{-0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
							 
	{-0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{-0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{-0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{-0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
							 	
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{ 0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{ 0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
							 	
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{ 0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{ 0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{-0.5f, -0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
						 
	{-0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f},
	{ 0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 1.0f},
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{ 0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  1.0f, 0.0f},
	{-0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 0.0f},
	{-0.5f,  0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,	  0.0f, 1.0f}
	};


	// ####################################################################### square
	Mesh* mesh = new Mesh("Resources/textures/TestCube.mtl");
	mesh->LoadTexture("Resources/textures/container.jpg");
	mesh->AddVertices(vertices);
	/*mesh->AddVertex({ 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, });
	mesh->AddVertex({ 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, });
	mesh->AddVertex({ -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, });
	mesh->AddVertex({ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f });*/
	// std::vector<int> indices = { 0, 1, 3, 1, 2, 3 };
	//mesh->AddIndex(indices);

	Entity* squar = new Entity();
	squar->AddComponent(new ComponentModel(mesh));
	squar->AddComponent(new ComponentShader());
	squar->AddComponent(new ComponentTransform( glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 1.0f) ) );
	mEntities.push_back(squar);


	// ####################################################################### triangle

	Mesh* mesh2 = new Mesh("Resources/textures/Default.mtl");
	mesh2->LoadTexture("Resources/textures/Default.png");
	mesh2->AddVertex({ 0.8f,  0.8f, 0.0f,	1.0f,  0.0f, 0.0f,	1.0f, 1.0f, });
	mesh2->AddVertex({ 0.8f, -0.2f, 0.0f,	1.0f,  0.0f, 0.0f, 1.0f, 0.0f, });
	mesh2->AddVertex({ -0.8f, -0.2f, 0.0f,	0.0f,  0.0f, 1.0f, 0.0f, 0.0f, });
	std::vector<int> indices2 = { 0, 1, 2};
	mesh2->AddIndex(indices2);


	Entity* tri = new Entity();
	tri->AddComponent(new ComponentModel(mesh2));
	tri->AddComponent(new ComponentShader());
	tri->AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 2.0f, 1.0f)));
	// mEntities.push_back(tri);

	// ####################################################################### 



}

void ShooterGame::OnKeyboard(int key, bool down)
{
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
	}


	_keyStates[key] = down;

	if (down) return; // Ignore key down events

	// Switch key presses
	switch (key)
	{
	case 256: // Esc
		_gameState = Quit;
		break;
	case 80: // P
		if (_gameState == Playing)
		{
			_gameState = Paused;
		}
		else if (_gameState = Paused)
		{
			_gameState = Playing;
		}
		break;

	}
}

void ShooterGame::Render()
{
	_renderer->ClearScreen();
	for (Entity* ent : mEntities)
	{
		mRenderSystem->Run(ent);
		//_renderer->Render(ent);
	}


	 // _renderer->Render();

// other draw related logic
	//for (size_t i = 0; i < mEntities.size(); i++)
	//{

	//}

	// Swap buffers
	// _renderer->SwapBuffers();
}

void ShooterGame::Run(double dt)
{
	// prints the window pointer
	// std::cout << _window << std::endl;

	if (_gameState != Paused)
	{
		// game logic here
	}
	if (_gameState == Playing)
	{
		Render();
		// game logic here
	}
	if (_gameState == Quit)
	{
		ShooterGame* game = this;
		_window->Close();
	}

}
