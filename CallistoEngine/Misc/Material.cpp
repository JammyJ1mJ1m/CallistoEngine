#include "Material.h"

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
	// removes spaces from the string 
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return std::isspace(c); }), str.end());

}

void checkDir(std::string& line, const std::string& pFileLoc)
{
	std::size_t pos = pFileLoc.find_last_of("/\\");

	// Extract the substring from the start to the position before the last separator
	std::string directoryPath = (pos != std::string::npos) ? pFileLoc.substr(0, pos + 1) : "";

	replaceAll(directoryPath, "/", "\\");

	if (line.find(directoryPath) == std::string::npos)
		line = directoryPath + line;
}

void Material::LoadMaterial(std::string pFile)
{
	std::ifstream fileStram;

	fileStram.open(pFile);

	if (!fileStram)
	{
		std::cout << "Error opening file: " << pFile << std::endl;
		fileStram.clear();
		fileStram.open("Resources/Textures/Default.mtl");
	};
	std::string line;
	ResourceManager& manager = ResourceManager::getInstance();

	while (getline(fileStram, line)) {

		if (CheckLine(line, "map_Kd"))
		{
			checkDir(line, pFile);
			mDiffuseMap = manager.LoadTexture(line.c_str());
		}
		if (CheckLine(line, "map_Bump"))
		{
			checkDir(line, pFile);
			mNormalMap = manager.LoadTexture(line.c_str());
		}
		if (CheckLine(line, "map_Ke"))
		{
			checkDir(line, pFile);
			mEmissionMap = manager.LoadTexture(line.c_str());
		}


		if (CheckLine(line, "map_Ks"))
		{
			checkDir(line, pFile);
			mSpecularMap = manager.LoadTexture(line.c_str());
		}
	}

	// if none of the textures are found, load the default texture
	if (mDiffuseMap == -1)
	{
		std::cout << "Texture :: Diffuse not loaded :: mtl = " << pFile << std::endl;
		fileStram.clear();
		fileStram.open("Resources/Textures/Default.mtl");
		mDiffuseMap = manager.LoadTexture("Resources/Textures/Default.png");
	}

	if (mEmissionMap < 0)
	{
		mEmissionMap = manager.LoadTexture("Resources/Textures/DefaultEmission.png");
	}

	if (mSpecularMap < 0)

	{
		mSpecularMap = manager.LoadTexture("Resources/Textures/DefaultEmission.png");
	}
	fileStram.close();

}


void Material::LoadCubemap(std::string pFile)
{
	std::ifstream fileStram;
	fileStram.open(pFile);
	if (!fileStram)
	{
		std::cout << "Error opening file: " << pFile << std::endl;
		fileStram.clear();
		fileStram.open("Resources/Textures/Default.mtl");
	};
	std::string line;
	ResourceManager& manager = ResourceManager::getInstance();

	std::vector<std::string> faces;
	while (getline(fileStram, line)) {

		AddFace(line, faces, "ktop", pFile);
		AddFace(line, faces, "kleft", pFile);
		AddFace(line, faces, "kfront", pFile);
		AddFace(line, faces, "kright", pFile);
		AddFace(line, faces, "kback", pFile);
		AddFace(line, faces, "kbottom", pFile);
	}


	mCubemap = manager.LoadCubemap(faces);
}

bool Material::CheckLine(std::string& pLine, std::string pSearch)
{
	if (!pLine.find(pSearch))
	{
		replaceAll(pLine, pSearch, "");
		replaceAll(pLine, "\\\\", "\\");
		//pLine = pLine.substr("map_Bump");
		return true;
	}
	return false;
}

void Material::AddFace(std::string& pFace, std::vector<std::string>& pFaces, std::string pLineToCheck, const std::string& pFile)
{
	if (CheckLine(pFace, pLineToCheck))
	{
		checkDir(pFace, pFile);
		pFaces.push_back(pFace);
	}
}

Material::Material(std::string pFile, const bool pIsCubemap)
{
	mIsCubemap = pIsCubemap;

	if (mIsCubemap)
	{
		LoadCubemap(pFile);
	}
	else
		LoadMaterial(pFile);

}

void Material::UnbindTextures()
{
	glBindTexture(GL_TEXTURE0, 0);
	glBindTexture(GL_TEXTURE1, 0);
	glBindTexture(GL_TEXTURE2, 0);
}

void Material::Draw()
{
#if OPENGL

	if (mIsCubemap)
	{
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, GetCubemap());

	}
	else
	{
		if (GetDiffuseMap() != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GetDiffuseMap());

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GetEmissionMap());

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, GetSpecularMap());
		}
	}
#endif
}
