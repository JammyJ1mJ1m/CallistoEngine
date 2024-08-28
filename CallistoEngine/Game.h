#pragma once
#include "Window.h"
#include "Renderer.h"
#include <vector>
#include "Components/Entity.h"
#include "Mesh.h"
#include <map>

#include "Camera.h"
#include "SceneManager.h"

#include "Systems/SystemRender.h"
#include "Managers/AudioManager.h"

#include "DiscordManager.h"

#include "Managers/ResourceManager.h"
#include "chrono"



using MeshMap = std::map<std::string, Mesh*>;
using MeshMapIterator = MeshMap::iterator;

class InputManager;

class Game
{
	float fps = 0.0f;
	int frameCount = 0;
	int lastFrameCount = 0;

	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();


protected:
	DiscordManager* mDiscordManager;

	Camera* mCamera;
	// DT stuff
	double mDeltaTime;
	double mLastFrameTime;

	InputManager* mInputManager;

	bool mHasWindowSizeChanged;

	bool _keyStates[512];
	Renderer* mRenderer;
	Window* mWindow;
	MeshMap mMeshes;
	//	RenderSystem mRenderSystem;

	SystemRender* mRenderSystem;

	SceneManager mSceneManager;

	std::vector<Entity*> mEntities;

	static Game* theGame;  // Static instance pointer
	AudioManager* mAudioManager;

public:
	static Camera* GetGameCamera();
	static Game* GetGame() { return theGame; }
	AudioManager* GetAudioManager() { return mAudioManager; }
	static const float GetDeltaTime() { return theGame->mDeltaTime; }

	// get the input manager
	InputManager* GetInputManager() { return mInputManager; }


	Game();
	virtual ~Game() {};

	Mesh* GetMesh(std::string name);
	void AddMesh(std::string name, Mesh* mesh) { mMeshes[name] = mesh; }

	// methods
	virtual void Initialise(Window* w) = 0;
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual void Render() = 0;
	virtual void Run() = 0;
	virtual bool IsRunning() = 0;
	virtual bool HandleInput() = 0;
	virtual bool LoadMesh(const char* pFilePath, const char* pModelName, ResourceManager& pResourceManager) = 0;
	virtual void SetTitle(const char* pName){ mWindow->SetTitle(pName); }
	const double CalculateDeltaTime();
	const float GetFPS() { return fps; }
};

inline Mesh* Game::GetMesh(std::string name)
{
	// Found
	MeshMapIterator i = mMeshes.find(name);
	if (i != mMeshes.end())
	{
		return i->second;
	}
	// Not found
	return NULL;
}