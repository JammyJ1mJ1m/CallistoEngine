#include "GameScene.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentRigidBody.h"
#include "Math/Vector.h"
#include "Misc/Material.h"
#include "Systems/SystemRender.h"
#include "Systems/SystemRenderDeferred.h"
#include "Player.h"
#include "Enemy.h"
#include "SkyBox.h"
#include "ExpBarrel.h"
#include "TestCube.h"
#include "GunAK.h"
#include "TestLight.h"

#include "Managers/PhysicsManager.h"
#include "Managers/InputManager.h"

#include "Misc/Sound.h"

#include "GunLoader.h"

#include <sstream>

#include "GUI/GUIManager.h"
#include "Graphical/Renderer_GL.h"

//#include <chrono>

Player* player;
ExpBarrel* expBarrel;
Sound* sound;
TestCube* testCube;
GunAK* gun;
TestLight* light;

GameScene::GameScene()
{
	isExploded = false;
}

GameScene::~GameScene()
{
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void GameScene::Initialise()
{
	mTimeToSpawn = 0.1;
#pragma region Initial entity stuff
	mLightSystem = new SystemLight();


	SkyBox* skybox = new SkyBox();
	AddEntity(skybox);


	player = new Player();
	AddEntity(player);

	//gun = new GunAK();
	//AddEntity(gun);

	Enemy* enemy = new Enemy();
	AddEntity(enemy);

	GunLoader& gLoader = GunLoader::GetInstance();

	const GunMap meshes = gLoader.GetGunsToLoad();

	for (auto& mesh : meshes)
	{
		Gun* newGun = new Gun();
		newGun->Initialise(mesh.first);
		AddEntity(newGun);
	}


	expBarrel = new ExpBarrel();
	AddEntity(expBarrel);

	//testCube = new TestCube();
	//AddEntity(testCube);
#pragma endregion

#pragma region Sounds stuff
	//sound = new Sound("Resources/Sounds/explosion.wav");
	//sound->SetLooping(true);
	//sound->Play3D(0,0,0);

	//Game::GetGame()->GetAudioManager()->PlaySound("Resources/Sounds/hyperloop-by-infraction.mp3", true);
#pragma endregion

#pragma region Lights

	// using this gives me 25 
	int lightCount = 9;
	// distance to use for width, dpeth of grid
	int distance = 200;
	float spacing = 50;
	Vector3f lightpositions = Vector3f(-distance, 5, -distance);

	for (size_t i = 0; i < lightCount; i++)
	{
		for (size_t j = 0; j < lightCount; j++)
		{
			TestLight* testLight = new TestLight();
			LightComponent* lc = testLight->GetComponent<LightComponent>();
			testLight->SetPosition(lightpositions);
			Light* l = lc->GetLight();/// ;

			float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.0
			float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.0
			float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.0

			l->SetDiffuse(Vector3f(rColor, gColor, bColor));
			AddEntity(testLight);

			lightpositions.SetX(lightpositions.GetX() + spacing);
		}
		lightpositions.SetX(-distance);

		lightpositions.SetZ(lightpositions.GetZ() + spacing);


	}

	// add the lights here
	light = new TestLight();
	LightComponent* lc1 = light->GetComponent<LightComponent>();
	Light* l1 = lc1->GetLight();/// ;
	l1->SetDiffuse(Vector3f(1, 0, 1));
	AddEntity(light);

	//TestLight* light3 = new TestLight();
	//light3->SetPosition(Vector3f(-10, 20, -50));
	//LightComponent* lc3 = light3->GetComponent<LightComponent>();
	//lc3->GetLight()->SetDiffuse(Vector3f(0, 1, 0));
	//AddEntity(light3);

	//TestLight* light2 = new TestLight();
	//light2->SetPosition(Vector3f(-10, 20, 50));
	//LightComponent* lc2 = light2->GetComponent<LightComponent>();
	//lc2->GetLight()->SetDiffuse(Vector3f(1, 0, 0));
	//AddEntity(light2);
#pragma endregion

#pragma region UI Stuff
	const char* tt = SteamManager::GetInstance().GetSteamUserID();

	std::stringstream ss;
	ss << "Logged in as: " << tt;
	std::string name = ss.str();

	text1 = new GUIText(name.c_str(), Vector3f(1, 1, 1), Vector3f(5, 5, 1), GUIOrigin::BOTTOM_LEFT, 20);
	//text2 = new GUIText("Hallo welt!", Vector3f(1, 1, 1), Vector3f(0, 0, 1), 32);

	container1 = new GUIContainer(Vector3f(0, 0));
	//container1->AddElement(text1);
	//container1->AddElement(text2);

	image1 = new GUIImage(1131, 178, 1, 10, 10);
	image1->SetColor(Vector4f(1, 0, 1, 1));
	image1->SetPosition(Vector3f(10, 40, 0));
	image1->SetRelativePosition(Vector3f(10, 40, 0));
	container1->AddElement(image1);

	GUIManager::GetInstance().AddElement(image1);
	GUIManager::GetInstance().AddElement(text1);
#pragma endregion
	testCheck = false;
}


void GameScene::OnKeyboard(int key, bool down)
{
	// get a reference to the input manager
	GameInputManager* inputManager = static_cast<GameInputManager*>(Game::GetGame()->GetInputManager());

	// Get the delta time
	double mDeltaTime = Game::GetGame()->GetDeltaTime();

	// Get the camera
	Camera* mCamera = Game::GetGame()->GetGameCamera();
	float moveSensitivity = 32.0f;

	for (int i = 0; i < inputManager->GetKeysSize(); i++)
	{
		Command* command = nullptr;
		if (inputManager->GetKey(i))
			command = inputManager->HandleInput(i);

		// realistically we would only ever pass the player here as the user input affects the player
		// TODO maybe implemnent a type/tag to filter commands for specific entities
		if (command != nullptr)
			command->execute(light);

	}

	// TODO replace these with commands
	if (inputManager->GetKey(GLFW_KEY_R) && mElapsed >= mTimeToSpawn)
	{
		mElapsed = 0;
		AddEntity(new Enemy());
		int entityCount = GetEntityCount();
		std::cout << "Entity count: " << entityCount << std::endl;
		// get the game class
		Game* game = Game::GetGame();

		// update window title
		std::stringstream ss;
		ss << "Gamey game :: " << entityCount << " entities";

		game->SetTitle(ss.str().c_str());
	}
	// key y is pressed

	// g key pres

	if (inputManager->GetKey(GLFW_KEY_Y) && isExploded == false)
	{
		isExploded = true;
		// applyExplosionForce(PhysicsManager::GetInstance().GetWorld(), btVector3(0, 0, 0), 1000, 100);
		btDiscreteDynamicsWorld& world = PhysicsManager::GetInstance().GetDynamicsWorld();
		auto origin = btVector3(expBarrel->GetComponent<ComponentTransform>()->GetPosition().x, expBarrel->GetComponent<ComponentTransform>()->GetPosition().y, expBarrel->GetComponent<ComponentTransform>()->GetPosition().z);
		auto strength = 100;
		auto radius = 50;
		expBarrel->applyExplosionForce(world, origin, strength, radius);
		//sound->Play3D(origin.x(), origin.y(), origin.z());
		//Game::GetGame()->GetAudioManager()->Play3DSound("Resources/Sounds/explosion.wav",origin.x(),origin.y(),origin.z(), false);

		// remove expBarrel from mEntities
		mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), expBarrel), mEntities.end());
	}



	if (inputManager->GetKeyDown(GLFW_KEY_X))
	{
		Renderer_GL* instance = static_cast<Renderer_GL*>(&Renderer_GL::GetInstance());
		instance->SetEffectStatus("Blur", testCheck);
		instance->SetEffectStatus("Bloom", testCheck);
		testCheck = !testCheck;
		// Renderer_GL* gl = Renderer_GL::GetInstance();
	}
}

void GameScene::Update(double deltaTime)
{
	// testCube->Rotate(1, deltaTime);
	mElapsed += deltaTime;

	// move all this to a audio system
	ALfloat listenerPos[] = {
	Game::GetGame()->GetGameCamera()->GetPosition().GetX(),
	Game::GetGame()->GetGameCamera()->GetPosition().GetY(),
	Game::GetGame()->GetGameCamera()->GetPosition().GetZ()
	};

	ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };

	ALfloat listenerOri[] = {
	Game::GetGame()->GetGameCamera()->GetDirection().GetX() ,
	Game::GetGame()->GetGameCamera()->GetDirection().GetY() ,
	Game::GetGame()->GetGameCamera()->GetDirection().GetZ() ,

	Game::GetGame()->GetGameCamera()->GetUp().GetX() * -1,
	Game::GetGame()->GetGameCamera()->GetUp().GetY() * -1,
	Game::GetGame()->GetGameCamera()->GetUp().GetZ() * -1
	};



	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	Game::GetGame()->GetAudioManager()->SetListenerPosition(Game::GetGame()->GetGameCamera()->GetPosition().GetX(),
		Game::GetGame()->GetGameCamera()->GetPosition().GetY(),
		Game::GetGame()->GetGameCamera()->GetPosition().GetZ());

	//Game::GetGame()->GetAudioManager()->SetListenerPosition(0,0,0);
	PhysicsManager::GetInstance().Update(deltaTime);

	//btTransform pos;
	//player->GetComponent<ComponentRigidBody>()->GetMotionState()->getWorldTransform(pos);
	//std::cout << pos.getOrigin().x() << " " << pos.getOrigin().y() << " " << pos.getOrigin().z() << std::endl;
	//player->GetComponent<ComponentRigidBody>()->SyncWithTransform(player->GetComponent<ComponentTransform>());

	if (Game::GetGame()->GetHasWindowChanged())
	{
		image1->Resize(Game::GetGame()->GetGameCamera()->mWidth, Game::GetGame()->GetGameCamera()->mHeight);

	}

}

void GameScene::Render(SystemRenderDeferred* renderer)
{
	//renderer->StartPP();

	renderer->Begin();

	//################################################################
	//	  fill out the g buffer with position, normal and colour
	//################################################################

	// TODO: refactor this into systems, syncing RB doesnt need to be here
	for (auto& enti : mEntities)
	{
		mLightSystem->Run(enti);

		if (enti->GetComponent<ComponentRigidBody>())
		{
			enti->GetComponent<ComponentRigidBody>()->SyncWithTransform(enti->GetComponent<ComponentTransform>());
			//enti->GetComponent<ComponentRigidBody>()->SyncWithTransform(enti);
		}
		//enti->UpdateChildPositions();
		renderer->Run(enti);
		for (auto& child : enti->GetChildren())
		{
			renderer->Run(child);
		}
	}
	//################################################################
	//					 render the lights
	//################################################################

	renderer->RunLighting();

	renderer->End();
	renderer->PostProcess();


	//text1->Render();
	////container1->Render();
	//image1->Render();
}