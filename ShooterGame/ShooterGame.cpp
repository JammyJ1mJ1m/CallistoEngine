#include "ShooterGame.h"


void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	// other game setup logic
	_gameState = Playing;

	Mesh* mesh = new Mesh("Resources/textures/TestCube.mtl");
	mesh->LoadTexture("Resources/textures/container.jpg");
	mesh->AddVertex({ 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, });
	mesh->AddVertex({ 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, });
	mesh->AddVertex({ -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, });
	mesh->AddVertex({ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f });
	
	int indices[] = {  
		0, 1, 3,  
		1, 2, 3   
	};

	int size = sizeof(indices) / sizeof(indices[0]);

	mesh->AddIndex(indices, size);

	Entity* ent1 = new Entity();
	ent1->AddComponent(new ComponentModel(mesh));
	ent1->AddComponent(new ComponentShader());
	ent1->AddComponent(new ComponentTransform( glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) ) );


	Mesh* mesh2 = new Mesh("Resources/textures/Default.mtl");
	mesh2->LoadTexture("Resources/textures/Default.png");

	mesh2->AddVertex({ 0.8f,  0.8f, 0.0f,	1.0f,  0.0f, 0.0f,	1.0f, 1.0f, });
	mesh2->AddVertex({ 0.8f, -0.2f, 0.0f,	1.0f,  0.0f, 0.0f, 1.0f, 0.0f, });
	mesh2->AddVertex({ -0.8f, -0.2f, 0.0f,	0.0f,  0.0f, 1.0f, 0.0f, 0.0f, });


	int indices2[] = {
		0, 1, 2,
	};

	size = sizeof(indices2) / sizeof(indices2[0]);
	mesh2->AddIndex(indices2, size);


	Entity* ent2 = new Entity();
	ent2->AddComponent(new ComponentModel(mesh2));
	ent2->AddComponent(new ComponentShader());
	ent2->AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));


	mEntities.push_back(ent1);
	mEntities.push_back(ent2);


	mRenderSystem = new SystemRender();

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
	for (Entity* ent : mEntities)
	{
		mRenderSystem->Run(ent);
	}


	_renderer->ClearScreen();
	// _renderer->Render();

// other draw related logic
	for (size_t i = 0; i < mEntities.size(); i++)
	{

		_renderer->Render(mEntities[i]);
	}

	// Swap buffers
	_renderer->SwapBuffers();
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
