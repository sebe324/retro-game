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
