#pragma once
#include"Pch.h"

class RandomGenerator
{
public:

	static RandomGenerator* GetInstance();

	static float GetFloat(const float& min, const float& max);

	static int GetInt(const int& min, const int& max);

private:

	std::random_device device_ ;

};
