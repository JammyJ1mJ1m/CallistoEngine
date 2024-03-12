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

Material::Material(std::string pFile)
{
	LoadMaterial(pFile);
}

void Material::Draw() const
{
#if OPENGL

#endif
}
