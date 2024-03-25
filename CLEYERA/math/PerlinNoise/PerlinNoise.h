#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>

class PerlinNoise {

public:

	PerlinNoise();

	float noise(float x, float y, float z);

	float fade(float t);

	float lerp(float t, float a, float b);

	float grad(int hash, float x, float y, float z);

private:
	std::vector<int> gradientTable_ = std::vector<int>(512);
};