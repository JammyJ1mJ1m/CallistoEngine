#include "GunLoader.h"
#include "Game.h"

GunLoader* GunLoader::mInstance = nullptr;

GunLoader::~GunLoader()
{
	for (auto& item : mGuns)
	{
		delete item.first;
	}
}

void GunLoader::ConstructFromDisk(const char* pPath)
{
	GunInformation* loadedGunInfo = new GunInformation();;

	// Gun* gun = new Gun();
	TomlReader reader;
	toml::table config = reader.ReadFile(pPath);

	if (config.empty())
	{
		std::cerr << "GunLoader :: Error parsing file\n";
		return;
	}

	// Accessing display settings
	auto transform = config["gun"]["transform"];
	loadedGunInfo->setPosition(Vector3f(*transform["positionX"].value<float>(),
		*transform["positionY"].value<float>(),
		*transform["positionZ"].value<float>()));

	//float posX = *transform["positionX"].value<float>();
	//float posY = *transform["positionY"].value<float>();
	//float posZ = *transform["positionZ"].value<float>();
	//gun->SetPosition(Vector3f(posX, posY, posZ));



	auto model = config["gun"]["model"];
	loadedGunInfo->setModelPath(*model["modelPath"].value<std::string>());
	loadedGunInfo->setModelMat(*model["moldeMaterial"].value<std::string>());


	auto specifics = config["gun"]["specifics"];
	loadedGunInfo->setGunName(*specifics["gunName"].value<std::string>());
	loadedGunInfo->setMagCount(*specifics["magCount"].value<int>());
	loadedGunInfo->setMagSize(*specifics["magSize"].value<int>());
	loadedGunInfo->setFireRate(*specifics["fireRate"].value<float>());

	auto magazine = config["gun"]["mag"];
	loadedGunInfo->SetHasChild(*magazine["hasChild"].value<bool>());

	if (loadedGunInfo->GetHasChild())
	{
		loadedGunInfo->setChildName(*magazine["childName"].value<std::string>());
		loadedGunInfo->setChildPath(*magazine["childPath"].value<std::string>());
	}

	if (loadedGunInfo->getChildName() != "" && loadedGunInfo->getChildPath() != "")
	{
		mMeshesToLoad[loadedGunInfo->getChildPath()] = loadedGunInfo->getChildName();
	}
	// gun->AddComponent(new ComponentModel(Game::GetGame()->GetMesh(gunName), modelMat));

	mMeshesToLoad[loadedGunInfo->getModelPath()] = loadedGunInfo->getGunName();
	mGuns[loadedGunInfo] = loadedGunInfo->getGunName();

}