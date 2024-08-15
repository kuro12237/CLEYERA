#pragma once
#include"Pch.h"

class LogManager
{
public:
	LogManager();
	~LogManager();

	static std::wstring ConvertString(const std::string& str);
	static std::string ConvertString(const std::wstring& str);

	static void Log(const std::string& message);

	static void CompliteLog(const string message=nullptr);

private:

};

