#include "Utils.h"

std::string Utils::toString(float f, int precision){
std::ostringstream out;
out.precision(precision);
out<<std::fixed<<f;
return out.str();
}

std::string Utils::toString(int i){
std::ostringstream out;
out<<i;
return out.str();
}
int Utils::clamp(int n, int min, int max){
if(n<min) return min;
else if(n>max) return max;
else return n;
}

float Utils::mirrorXf(float x, float borderL, float borderR){
float distance=x-borderL;
x=borderR-distance;
return x;
}
