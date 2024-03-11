#include "ResourceManager.h"
#include <../stb_image.h>

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
#endif