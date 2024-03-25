#pragma once
#include"Pch.h"

class FileLoader
{
public:

	static stringstream  CSVLoadFile(const string filepath);

private:


	FileLoader() = default;
	~FileLoader() = default;
	FileLoader(const FileLoader&) = delete;
	const FileLoader& operator=(const FileLoader&) = delete;
};
