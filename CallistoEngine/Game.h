#pragma once
#include "Window.h"
#include "Renderer.h"
#include <vector>
#include "Components/Entity.h"
#include "Mesh.h"
#include <map>

#include "Camera.h"

// #include "RenderSystem.h"
#include "SceneManager.h"

#include "Systems/SystemRender.h"
class Game
{

protected:
	Camera* mCamera;
	// DT stuff
	double mDeltaTime;
	double mLastFrameTime;
	

	bool _keyStates[512];
	Renderer* mRenderer;
	Window* mWindow;
	std::map<std::string, Mesh*> mMeshes;
//	RenderSystem mRenderSystem;

	SystemRender* mRenderSystem;

	SceneManager mSceneManager;

	std::vector<Entity*> mEntities;

	static Game* theGame;  // Static instance pointer

public:
	static Camera* GetGameCamera();


	Game();
	virtual ~Game() {};

	void AddMesh(std::string name, Mesh* mesh) { mMeshes[name] = mesh; }

	// methods
	virtual void Initialise(Window* w) = 0;
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual void Render() = 0;
	virtual void Run(double dt) = 0;
	virtual bool IsRunning() = 0;
	virtual bool HandleInput() = 0;
};

