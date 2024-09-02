#pragma once
#include "toml.hpp"
class TomlReader final
{
	public:
	TomlReader() = default;
	~TomlReader() = default;

	toml::table ReadFile(const char* pFilename);
};

