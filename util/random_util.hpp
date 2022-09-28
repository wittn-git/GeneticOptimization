#pragma once
#include <random>

inline float getRandom(float min, float max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(min, max); 
    return dist(rng);
}