#pragma once
#include"Pch.h"
#include"LogManager.h"

class FileLoader
{
public:

	static stringstream  CSVLoadFile(const string filepath);

	static ifstream JsonLoadFile(const string filePath);

private:



	FileLoader() = default;
	~FileLoader() = default;
	FileLoader(const FileLoader&) = delete;
	const FileLoader& operator=(const FileLoader&) = delete;
};
