#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <vector>
#include <stdint.h>
#include <random>
class Rnd{
public:
uint32_t seed=12345;
std::vector<float> perlin1d(std::vector<float> values, int nOctaves, float bias=2.f);

std::vector<float> perlin2d(std::vector<float> values, int width, int height, int nOctaves, float bias=2.f);
uint32_t Lehmer32();

int rndInt(int min, int max);

double rndDouble(double min, double max);

int rndIntNormal(int min, int max);

double rndDoubleNormal(double min, double max);
};
#endif // PERLINNOISE_H
