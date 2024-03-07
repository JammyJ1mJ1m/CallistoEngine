#include "ShooterGame.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Vector4.h"

void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	// other game setup logic


	_gameState = Playing;

	Mesh* mesh = new Mesh();
	mesh->AddVertex({ 0.5f,  0.5f, 0.0f, });
	mesh->AddVertex({ 0.5f, -0.5f, 0.0f });
	mesh->AddVertex({ -0.5f, -0.5f, 0.0f });
	mesh->AddVertex({ -0.5f,  0.5f, 0.0f });
	
	int indices[] = {  
		0, 1, 3,  
		1, 2, 3   
	};

	int size = sizeof(indices) / sizeof(indices[0]);

	mesh->AddIndex(indices, size);

	Entity* ent1 = new Entity();
	ent1->AddComponent(new ComponentModel(mesh));

	mEntities.push_back(ent1);

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
