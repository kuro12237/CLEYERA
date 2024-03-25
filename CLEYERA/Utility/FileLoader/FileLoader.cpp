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
