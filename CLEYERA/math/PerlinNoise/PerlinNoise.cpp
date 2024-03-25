#include "PerlinNoise.h"



PerlinNoise::PerlinNoise() {

    for (int i = 0; i < 256; ++i) {
        gradientTable_[i] = i;
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(gradientTable_.begin(), gradientTable_.begin() + 256, generator);

    gradientTable_.insert(gradientTable_.end(), gradientTable_.begin(), gradientTable_.begin() + 256);
}


float PerlinNoise::noise(float x, float y, float z) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    x -= floor(x);
    y -= floor(y);
    z -= floor(z);


    float u = fade(x);
    float v = fade(y);
    float w = fade(z);


    int p000 = gradientTable_[X] + Y;
    int p001 = gradientTable_[p000] + Z;
    int p010 = gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p000) + 1] + Z;
    int p011 = gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(X) + 1] + Y;
    int p100 = gradientTable_[p011] + Z;
    int p101 = gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p011) + 1] + Z;


    float g000 = grad(gradientTable_[p001], x, y, z);
    float g001 = grad(gradientTable_[p100], x - 1, y, z);
    float g010 = grad(gradientTable_[p010], x, y - 1, z);
    float g011 = grad(gradientTable_[p101], x - 1, y - 1, z);
    float g100 = grad(gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p001) + 1], x, y, z - 1);
    float g101 = grad(gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p100) + 1], x - 1, y, z - 1);
    float g110 = grad(gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p010) + 1], x, y - 1, z - 1);
    float g111 = grad(gradientTable_[static_cast<std::vector<int, std::allocator<int>>::size_type>(p101) + 1], x - 1, y - 1, z - 1);


    float n000 = lerp(u, g000, g001);
    float n001 = lerp(u, g010, g011);
    float n010 = lerp(u, g100, g101);
    float n011 = lerp(u, g110, g111);
    float n100 = lerp(v, n000, n001);
    float n101 = lerp(v, n010, n011);

    float result = lerp(w, n100, n101);


    return (result + 1) / 2;
}


float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}


float PerlinNoise::lerp(float t, float a, float b) {
    return a + t * (b - a);
}


float PerlinNoise::grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}