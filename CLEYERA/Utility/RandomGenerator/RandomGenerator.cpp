#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::GetInstance()
{
	static RandomGenerator instance;
	return &instance;
}

float RandomGenerator::GetFloat(const float& min, const float& max)
{
	std::mt19937 generetor(RandomGenerator::GetInstance()->device_());
	std::uniform_real_distribution<float>result(min, max);
	return result(generetor);
}

int RandomGenerator::GetInt(const int& min, const int& max)
{
	std::mt19937 generetor(RandomGenerator::GetInstance()->device_());
	std::uniform_int_distribution<int>result(min, max);
	return result(generetor);
}
