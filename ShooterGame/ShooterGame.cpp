#include "ShooterGame.h"

void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();
	mRenderSystem = new SystemRender(_renderer);

	// other game setup logic
	_gameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), _window->GetWindowWidth(), _window->GetWindowHeight());
	// ####################################################################### triangle

	Entity* tri = new Entity();
	tri->AddComponent(new ComponentModel("Resources/Geometry/test/Intergalactic_Spaceship.obj", "Resources/textures/TestCube.mtl"));
	tri->AddComponent(new ComponentShader(mCamera));
	tri->AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	 mEntities.push_back(tri);
}

void ShooterGame::OnKeyboard(int key, bool down)
{
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
	}

	_keyStates[key] = down;
}

void ShooterGame::Render()
{
	_renderer->ClearScreen();
	for (Entity* ent : mEntities)
	{
		mRenderSystem->Run(ent);
		//_renderer->Render(ent);
	}

}

void ShooterGame::Run(double dt)
{
	_deltaTime = dt;

	if (_gameState != Paused)
	{
		// game logic here
	}
	if (_gameState == Playing)
	{
		Render();
		HandleInput();

		// game logic here
	}
	if (_gameState == Quit)
	{
		ShooterGame* game = this;
		_window->Close();
	}

}

bool ShooterGame::HandleInput()
{
	float moveSensitivity = 16.0f * _deltaTime;
	
	if (_keyStates[256])  // Esc
		_gameState = Quit;
	if (_keyStates[80])  // P
		if (_gameState == Playing)
		{
			_gameState = Paused;
		}
		else if (_gameState = Paused)
		{
			_gameState = Playing;
		}

	if (_keyStates[65])  // A
		if (_gameState == Playing)
		{
			mCamera->Strafe(-(moveSensitivity));
		}
	if (_keyStates[68])  // D
		if (_gameState == Playing)
		{
			// Move right
			mCamera->Strafe((moveSensitivity));
		}

	if (_keyStates[83])  // S
		if (_gameState == Playing)
		{
			// Move back
			mCamera->MoveForward(-(moveSensitivity));
		}
	if (_keyStates[87]) // W
		if (_gameState == Playing)
		{
			// Move forward
			mCamera->MoveForward(moveSensitivity);
		}
	return false;
}
