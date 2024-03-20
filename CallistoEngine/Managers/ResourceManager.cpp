#include "ResourceManager.h"
#include <../stb_image.h>

#include "../Mesh.h"

std::string ResourceManager::LoadShader(const char* pFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;

	std::ifstream shaderFileStream;

	// ensure ifstream objects can throw exceptions:
	shaderFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		shaderFileStream.open(pFile);

		std::stringstream shaderStringStream;
		// read file's buffer contents into streams
		shaderStringStream << shaderFileStream.rdbuf();

		// close file handlers
		shaderFileStream.close();

		// convert stream into string
		shaderCode = shaderStringStream.str();
		return shaderCode;

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::string emp = "empty";
		return emp;
	}
}

#if OPENGL	
#include <glad/glad.h>
#include "GLFW/glfw3.h"

int ResourceManager::LoadTexture(const std::string pFile)
{
	bool fileExists = false;
	// Search for a specific value
	for (const auto& pair : mTextures) {
		if (pair.second == pFile) {
			std::cout << "Texture ::  " << pFile << " :: already loaded :: unit = " << pair.first << std::endl;
			return pair.first;  // Assuming each value is unique, exit loop if found
		}
	}

	if (!fileExists)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		stbi_set_flip_vertically_on_load(true);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(pFile.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			if (nrChannels == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);

			mTextures.insert({ texture, pFile });
			return texture;
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return -1;
		}
		stbi_image_free(data);
	}
}


Mesh* ResourceManager::LoadMesh(const std::string pFile)
{

	bool fileExists = false;
	// Search for a specific value
	for (const auto& pair : mMeshs) {
		if (pair.second == pFile) {
			std::cout << "Model  ::  " << pFile << " :: already loaded :: model = " << pair.first << std::endl;
			return pair.first;  // Assuming each value is unique, exit loop if found
		}
	}

	if (!fileExists)
	{

		Assimp::Importer importer;

		const aiScene* const scene = importer.ReadFile( pFile,
			aiProcess_Triangulate | aiProcess_CalcTangentSpace);
		try
		{
			if (scene == nullptr)
				throw std::runtime_error("Error reading file, perhaps the path is incorrect");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}

		Mesh* MeshModel = new Mesh();

		for (size_t i = 0; i < scene->mNumMeshes; i++)
		{
			const aiMesh* const mesh = scene->mMeshes[i];

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.x = mesh->mVertices[i].x;
				vertex.y = mesh->mVertices[i].y;
				vertex.z = mesh->mVertices[i].z;


				vertex.u = mesh->mTextureCoords[0][i].x;
				vertex.v = mesh->mTextureCoords[0][i].y;

				/*vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.z = mesh->mNormals[i].z;

				vertex.Binormal.x = mesh->mBitangents[i].x;
				vertex.Binormal.y = mesh->mBitangents[i].y;
				vertex.Binormal.z = mesh->mBitangents[i].z;

				vertex.Tangent.x = mesh->mTangents[i].x;
				vertex.Tangent.y = mesh->mTangents[i].y;
				vertex.Tangent.z = mesh->mTangents[i].z;*/

				MeshModel->AddVertices(vertex);
			}

			for (int i = 0; i < mesh->mNumFaces; i++)
			{
				const aiFace face = mesh->mFaces[i];
				for (int j = 0; j < face.mNumIndices; j++)
					MeshModel->AddIndex(face.mIndices[j]);
			}
		}

		// mStartIndex = mVertices.size();
		return MeshModel;
	}

}
#endif