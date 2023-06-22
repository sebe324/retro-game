#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <iomanip>
#include <cmath>

class Utils{
    public:
static std::string toString(float f, int precision=8);
static std::string toString(int i);
static int clamp(int n, int min, int max);
static float mirrorXf(float x, float borderL, float borderR);
static float distance(float x1, float y1, float x2, float y2);
static float randomize(int min, int max);
};
#endif // UTILS_H
