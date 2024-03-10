#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ResourceManager
{

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


	std::string LoadShader(const char* pFile)
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


};

