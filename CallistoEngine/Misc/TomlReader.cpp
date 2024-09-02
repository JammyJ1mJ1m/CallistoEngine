#include "TomlReader.h"
#include <iostream>

toml::table TomlReader::ReadFile(const char* pFilename)
{
	toml::table config;
	try {

		config = toml::parse_file(pFilename);

	}
	catch (const toml::parse_error& err)
	{
		std::cerr
			<< "Error parsing file '" << err.source().path
			<< "':\n" << err.description()
			<< "\n (" << err.source().begin << ")\n";
		return config;
	}
}
