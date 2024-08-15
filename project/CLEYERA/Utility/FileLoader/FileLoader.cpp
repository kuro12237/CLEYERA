#include "FileLoader.h"


stringstream  FileLoader::CSVLoadFile(const string filepath)
{
	filepath;
	ifstream file{};
	stringstream resultData{};
	file.open(filepath);
	assert(file.is_open());
	resultData << file.rdbuf();
	file.close();
	return resultData;
}

ifstream FileLoader::JsonLoadFile(const string filePath)
{
	ifstream file;
	file.open(filePath);

	if (file.fail())
	{
		LogManager::Log("not file open\n");
		assert(0);
	}

	return file;
}
