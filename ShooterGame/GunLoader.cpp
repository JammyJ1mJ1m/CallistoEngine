#include "GunLoader.h"
#include "Game.h"
#include <fstream>
#include <string>

GunLoader* GunLoader::mInstance = nullptr;

GunLoader::~GunLoader()
{
	for (auto& item : mGuns)
	{
		delete item.first;
	}
}

void GunLoader::ReadManifest(const char* pPath)
{
	// open the manifest
	std::string line;
	std::ifstream myfile(pPath);
	if (myfile.is_open())
	{
		// loop through and construct each gun
		while (getline(myfile, line)) {
			if (line.find('#') == std::string::npos)
				ConstructFromDisk(line.c_str());
		}
		myfile.close();
	}
	else std::cerr << "GunLoader :: Unable to open file :: " << pPath << "\n";

}

void GunLoader::ConstructFromDisk(const char* pPath)
{
	GunInformation* loadedGunInfo = new GunInformation();;

	TomlReader reader;
	toml::table config = reader.ReadFile(pPath);

	if (config.empty())
	{
		std::cerr << "GunLoader :: Error parsing file\n";
		return;
	}

	auto transform = config["gun"]["transform"];
	loadedGunInfo->setPosition(Vector3f(*transform["positionX"].value<float>(),
		*transform["positionY"].value<float>(),
		*transform["positionZ"].value<float>()));

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

	mMeshesToLoad[loadedGunInfo->getModelPath()] = loadedGunInfo->getGunName();
	mGuns[loadedGunInfo] = loadedGunInfo->getGunName();
}