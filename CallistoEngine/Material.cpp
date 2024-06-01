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
			mDiffuseMap = manager.LoadTexture(line.c_str());
		}
		if (CheckLine(line, "map_Bump"))
		{
			mNormalMap = manager.LoadTexture(line.c_str());
		}
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

		AddFace(line, faces, "ktop");
		AddFace(line, faces, "kleft");
		AddFace(line, faces, "kfront");
		AddFace(line, faces, "kright");
		AddFace(line, faces, "kback");
		AddFace(line, faces, "kbottom");
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

void Material::AddFace(std::string& pFace, std::vector<std::string>& pFaces, std::string pLineToCheck)
{
	if (CheckLine(pFace, pLineToCheck))
		pFaces.push_back(pFace);
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

void Material::Draw()
{
#if OPENGL

	if (mIsCubemap)
	{
		glDepthMask(GL_FALSE);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, GetCubemap());
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, GetCubemap());*/
		//glDepthMask(GL_TRUE);
	}
	else
	{
		if (GetDiffuseMap() != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GetDiffuseMap());
		}
	}
#endif
}
