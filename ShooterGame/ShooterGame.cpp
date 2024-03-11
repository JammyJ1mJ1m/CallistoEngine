#include "ShooterGame.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Vector.h"

void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	// other game setup logic


	Vector2f v2 = { 1.0f, 2.0f, 3.0f, 4.0f };

	_gameState = Playing;

	Mesh* mesh = new Mesh();
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


	Mesh* mesh2 = new Mesh();
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

	mEntities.push_back(ent1);
	mEntities.push_back(ent2);

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
