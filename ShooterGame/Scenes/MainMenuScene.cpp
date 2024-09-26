#include "MainMenuScene.h"
#include "Math/Vector.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentRigidBody.h"
#include "Misc/Material.h"
#include "Systems/SystemRender.h"
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

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void MainMenuScene::Initialise()
{
	text1 = new GUIText("First", Vector3f(1, 1, 1), Vector3f(50, 500, 1), 64);
	text2 = new GUIText("Second", Vector3f(1, 1, 1), Vector3f(50, 300, 1), 64);
	text3 = new GUIText("third",Vector3f(1,1,1), Vector3f(50, 100, 1), 64);

	container1 = new GUIContainer(Vector3f(50, 50));
	container1->AddElement(text1);
	container1->AddElement(text2);
	container1->AddElement(text3);

	image1 = new GUIImage(Vector3f(1, 1, 1));
	image1->Initialise(1131, 478, 0.5);
	image1->SetPosition(Vector3f(1131 /2 , 178 /2 , 0));
	image1->SetRelativePosition(Vector3f(1131/2, 178 /2, 0));
	container1->AddElement(image1);

	//sound->SetLooping(true);
	//sound->Play3D(0,0,0);
	//Game::GetGame()->GetAudioManager()->Play2DSound("Resources/Sounds/hyperloop-by-infraction.mp3", true);
}


void MainMenuScene::OnKeyboard(int key, bool down)
{
	//// get a reference to the input manager
	//GameInputManager* inputManager = static_cast<GameInputManager*>(Game::GetGame()->GetInputManager());

	//for (int i = 0; i < inputManager->GetKeysSize(); i++)
	//{
	//	Command* command = nullptr;
	//	if (inputManager->GetKey(i))
	//		command = inputManager->HandleInput(i);
	//	// realistically we would only ever pass the player here as the user input affects the player
	//	// TODO maybe implemnent a type/tag to filter commands for specific entities
	//	if (command != nullptr)
	//		command->execute(light);
	//}
	GameInputManager* inputManager = static_cast<GameInputManager*>(Game::GetGame()->GetInputManager());
	float amount = 50.0;
	float dt = Game::GetDeltaTime();

	if (inputManager->GetKey(GLFW_KEY_LEFT))
	{
		container1->SetPosition(container1->GetPosition() + Vector3f(-amount * dt, 0, 0));
	}
	if (inputManager->GetKey(GLFW_KEY_RIGHT))
		container1->SetPosition(container1->GetPosition() + Vector3f(amount * dt, 0, 0));

	if (inputManager->GetKey(GLFW_KEY_UP))
	{
		container1->SetPosition(container1->GetPosition() + Vector3f( 0, amount * dt, 0));
	}
	if (inputManager->GetKey(GLFW_KEY_DOWN))
		container1->SetPosition(container1->GetPosition() + Vector3f( 0, -amount * dt, 0));

}

void MainMenuScene::Update(double deltaTime)
{
	// testCube->Rotate(1, deltaTime);


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

}

void MainMenuScene::Render(SystemRender* renderer)
{
	renderer->Begin();

	//renderer->StartPP();

	// TODO: refactor this into systems, syncing RB doesnt need to be here
	//for (auto& enti : mEntities)
	//{
	//	//mLightSystem->Run(enti);

	//	//if (enti->GetComponent<ComponentRigidBody>())
	//	//{
	//	//	enti->GetComponent<ComponentRigidBody>()->SyncWithTransform(enti->GetComponent<ComponentTransform>());
	//	//	//enti->GetComponent<ComponentRigidBody>()->SyncWithTransform(enti);

	//	//}
	//	////enti->UpdateChildPositions();
	//	//renderer->Run(enti);
	//	//for(auto& child : enti->GetChildren())
	//	//{
	//	//	renderer->Run(child);
	//	//}
	//}
	// draw PP here
	//renderer->DrawPP();

	renderer->End();
	renderer->PostProcess();

	// container1->Render();
	//image1->Render();
	//text1->Render();
	//text2->Render();
}