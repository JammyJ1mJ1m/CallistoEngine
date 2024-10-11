#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "../Managers/ResourceManager.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"
class Material
{
	bool mIsCubemap;

	int mDiffuseMap;
	int mEmissionMap;
	int mSpecularMap;
	int mNormalMap;
	int mCubemap;

	void LoadMaterial(std::string pFile);
	void LoadCubemap(std::string pFile);
	bool CheckLine(std::string& pLine, std::string pSearch);
	void AddFace(std::string& pLine, std::vector<std::string>& pFaces, std::string pLineToCheck, const std::string& pFile);

public:
	Material(std::string pFile, const bool pIsCubemap = false);
	~Material() = default;

	const int& GetDiffuseMap() { return mDiffuseMap; }
	const int& GetEmissionMap()  { return mEmissionMap; }
	const int& GetNormalMap() { return mNormalMap; }
	const int& GetSpecularMap()  { return mSpecularMap; }
	const int& GetCubemap() { return mCubemap; }

	void UnbindTextures();

	void Draw();

};

