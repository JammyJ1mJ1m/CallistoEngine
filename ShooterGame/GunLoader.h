#pragma once
#include "Misc/TomlReader.h"
#include "Entities/Gun.h"
#include <unordered_map>
#include "GunInformation.h"

using GunMap = std::unordered_map <GunInformation*, std::string>;
using GunsToLoad = std::unordered_map <std::string, std::string>;


class GunLoader
{
	static GunLoader* mInstance;
	GunsToLoad mMeshesToLoad;
	GunMap mGuns;

	GunLoader() = default;
public:

	static GunLoader& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new GunLoader();

		return *mInstance;
	}

	~GunLoader();

	void ConstructFromDisk(const char* pPath);
	const GunsToLoad GetMeshesToLoad() { return mMeshesToLoad; };
	const GunMap GetGunsToLoad() { return mGuns; };

};