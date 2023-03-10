#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <iomanip>

class Utils{
    public:
static std::string toString(float f, int precision=8);
static std::string toString(int i);
static int clamp(int n, int min, int max);
static float mirrorXf(float x, float borderL, float borderR);
};
#endif // UTILS_H
