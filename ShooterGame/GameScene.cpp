#include "GameScene.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentRigidBody.h"
#include "Vector.h"
#include "Material.h"
#include "Systems/SystemRender.h"
#include "Player.h"
#include "Enemy.h"
#include "SkyBox.h"
#include "ExpBarrel.h"

#include "Managers/PhysicsManager.h"
#include "Sound.h"

Player* player;
ExpBarrel* expBarrel;
Sound* sound;
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
	player = new Player();
	AddEntity(player);

	Enemy* enemy = new Enemy();
	AddEntity(enemy);

	SkyBox* skybox = new SkyBox();
	AddEntity(skybox);

	expBarrel = new ExpBarrel();
	AddEntity(expBarrel);


	sound = new Sound("Resources/Sounds/explosion.wav");
	//sound->SetLooping(true);
	//sound->Play3D(0,0,0);

	//Game::GetGame()->GetAudioManager()->PlaySound("Resources/Sounds/hyperloop-by-infraction.mp3", true);
}



void GameScene::OnKeyboard(int key, bool down)
{
	if (key == 82)
	{
		AddEntity(new Enemy());
	}
	// key y is pressed

	// g key pres

	if (key == 89 && isExploded == false)
	{
		isExploded = true;
		// applyExplosionForce(PhysicsManager::GetInstance().GetWorld(), btVector3(0, 0, 0), 1000, 100);
		btDiscreteDynamicsWorld& world = PhysicsManager::GetInstance().GetDynamicsWorld();
		auto origin = btVector3(expBarrel->GetComponent<ComponentTransform>()->GetPosition().x, expBarrel->GetComponent<ComponentTransform>()->GetPosition().y, expBarrel->GetComponent<ComponentTransform>()->GetPosition().z);
		auto strength = 175;
		auto radius = 50;
		expBarrel->applyExplosionForce(world,origin,strength,radius);
		sound->Play3D(origin.x(), origin.y(), origin.z());
		//Game::GetGame()->GetAudioManager()->Play3DSound("Resources/Sounds/explosion.wav",origin.x(),origin.y(),origin.z(), false);
		
		// remove expBarrel from mEntities
		 mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), expBarrel), mEntities.end());

	}

}

void GameScene::Update(double deltaTime)
{
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

void GameScene::Render(SystemRender* renderer)
{
	for (auto& enti : mEntities)
	{
		if (enti->GetComponent<ComponentRigidBody>())
		{
			enti->GetComponent<ComponentRigidBody>()->SyncWithTransform(enti->GetComponent<ComponentTransform>());

		}

		renderer->Run(enti);
	}
}