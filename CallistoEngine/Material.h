#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "Managers/ResourceManager.h"

class Material
{
	int mDiffuseMap;
	int mNormalMap;

	void LoadMaterial(std::string pFile);
	bool CheckLine(std::string& pLine, std::string pSearch);
public:
	Material(std::string pFile);
	~Material() = default;

	const int& GetDiffuseMap()  { return mDiffuseMap; }
	const int& GetNormalMap()  { return mNormalMap; }

	void Draw() const;

};

