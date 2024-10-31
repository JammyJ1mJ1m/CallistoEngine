#pragma once
#include <stack>
#include <vector>

class SystemRender;
class Scene;
class Game;

/// Handles the Scenes for a game
class SceneManager
{
	// Constants
public:

	// Data
protected:
	Game* mGame;
	std::stack<Scene*>	mScenes;

	// Structors
public:
	SceneManager(Game* pGame);
	~SceneManager();


	// Gets/Sets
public:
	Scene* GetCurrentScene()	const { if (mScenes.size() > 0) return mScenes.top(); else return NULL; }
	Game* GetGame()				const { return mGame; }

	// Functions
public:

	/// Respond to input
	void OnKeyboard(int pKey, bool pIsDown);

	/// Update current scene
	void Update(double pDeltaTime);

	/// Render current scene
	void Render(SystemRender* pRenderer);

	/// Pop the top scene. If no scenes remain, we should quit.
	void PopScene() { mScenes.pop(); }

	/// Push a new scene
	void PushScene(Scene* pScene);
};

