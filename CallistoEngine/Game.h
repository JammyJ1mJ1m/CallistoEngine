#pragma once
#include "Graphical/Window.h"
#include "Graphical/Renderer.h"
#include <vector>
#include "Components/Entity.h"
#include "Graphical/Mesh.h"
#include <map>

#include "Misc/Camera.h"
#include "Managers/SceneManager.h"

#include "Systems/SystemRender.h"
#include "Managers/AudioManager.h"

#include "Managers/DiscordManager.h"

#include "Managers/ResourceManager.h"
#include "chrono"


#include "Managers/SteamManager.h"
#include "Managers/LightManager.h"
#include "Managers/PhysicsManager.h"
//#include "Misc/BulletDebugDraw.h"


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
	GameState mGameState;
	LightManager* mLightManager;

	DiscordManager* mDiscordManager;
	SteamManager* mSteamManager;

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
	Game();
	virtual ~Game();

	// Gets and sets
	const GameState GetGameState() const { return mGameState; }
	void SetGameState(const GameState& pState) { mGameState = pState; }

	static Camera* GetGameCamera();
	static Game* GetGame() { return theGame; }
	AudioManager* GetAudioManager() { return mAudioManager; }
	static const float GetDeltaTime() { return theGame->mDeltaTime; }
	InputManager* GetInputManager() { return mInputManager; }

	Mesh* GetMesh(std::string name);
	void AddMesh(std::string name, Mesh* mesh) { mMeshes[name] = mesh; }


	// methods
	// pure virtuals
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual bool IsRunning() = 0;
	virtual bool HandleInput() = 0;
	virtual bool LoadMesh(const char* pFilePath, const char* pModelName, ResourceManager& pResourceManager) = 0;

	virtual void SetTitle(const char* pName) { mWindow->SetTitle(pName); }
	const double CalculateDeltaTime();
	const float GetFPS() { return fps; }

	// Use this for proper game initialisation
	void Initialise(Window* w)
	{
		BaseInitialise(w);
		InitialiseGame();
	}


	// Use this method to run the game loop
	void Update() {
		BaseRun();
		Run();
	}

	// Call this for proper drawing
	void Render() {
		BaseRender();
		RenderFrame();
	}

	//virtual void derivedUpdate() = 0;

private:
	virtual void Run() = 0; // same as derivedUpdate
	virtual void RenderFrame() = 0;
	virtual void InitialiseGame() = 0;


	void BaseInitialise(Window* w);
	void BaseRun();
	void BaseRender();
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