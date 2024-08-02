#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Mesh;

class ResourceManager
{

	std::unordered_map <int, std::string> mTextures;
	std::unordered_map <Mesh*, std::string> mMeshs;

	// credits https://stackoverflow.com/a/1008289/12954717
	// singleton class that is thread safe and lazy initialized

public:
	static ResourceManager& getInstance()
	{
		static ResourceManager    instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
private:
	ResourceManager() {}                    // Constructor? (the {} brackets) are needed here.

	//// C++ 03
	//// ========
	//// Don't forget to declare these two. You want to make sure they
	//// are inaccessible(especially from outside), otherwise, you may accidentally get copies of
	//// your singleton appearing.
	//ResourceManager(ResourceManager const&); // Don't Implement
	//void operator=(ResourceManager const&); // Don't implement

	// C++ 11
	// =======
	// We can use the better technique of deleting the methods
	// we don't want.
public:
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status


	std::string LoadShader(const char* pFile);

	int LoadTexture(const std::string pFile);
	int LoadCubemap(const std::vector<std::string> pFaces);
	Mesh* LoadMesh(const std::string pFile);

};

