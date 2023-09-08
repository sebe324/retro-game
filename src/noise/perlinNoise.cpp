#include "perlinNoise.h"

std::vector<float> Rnd::perlin1d(std::vector<float> values, int nOctaves, float bias) {
    int n=values.size();
    std::vector<float> output;
    for (int x=0; x<n; x++) {

        float fNoise = 0.f; //accumulated noise
        float fScale = 1.f;
        float fScaleAcc = 0.f;
        for (int i=0; i<nOctaves; i++) {
            int nPitch=n >> i; //bitshifting
            int nSample1 = (x/nPitch) * nPitch; // 20/8*8 = 2*8=16 Some data gets lost, because those are ints.

            int nSample2 = (nSample1+nPitch) % n;

            float fBlend = (float)(x-nSample1) / float(nPitch); //how far are we in the pitch

            float fSample = (1.f-fBlend) * values[nSample1] + fBlend * values[nSample2];

            fNoise +=fSample*fScale;
            fScaleAcc +=fScale;
            fScale=fScale/bias;
        }
        output.push_back(fNoise/fScaleAcc);
    }
    return output;
}


std::vector<float> Rnd::perlin2d(std::vector<float> values, int width, int height, int nOctaves, float bias) {
    std::vector<float> output(width*height,0);
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {

            float fNoise = 0.f; //accumulated noise
            float fScale = 1.f;
            float fScaleAcc = 0.f;
            for (int i=0; i<nOctaves; i++) {
                int nPitch= height >> i; //bitshifting
                int nSampleX1 = (x/nPitch) * nPitch;
                int nSampleY1 = (y/nPitch) * nPitch;

                int nSampleX2 = (nSampleX1+nPitch) % width;
                int nSampleY2 = (nSampleY1+nPitch) % width;

                float fBlendX = (float)(x-nSampleX1) / (float)nPitch;
                float fBlendY = (float)(x-nSampleY1) / (float)nPitch;

                float fSample1 = (1.f-fBlendX) * values[nSampleY1*width+nSampleX1] + fBlendX * values[nSampleY1*width+nSampleX2];
                float fSample2 = (1.f-fBlendX) * values[nSampleY2*width+nSampleX1] + fBlendX * values[nSampleY2*width+nSampleX2];
                fNoise += (fBlendY*(fSample2-fSample1)+fSample1)*fScale;
                fScaleAcc +=fScale;
                fScale=fScale/bias;
            }
            output[y*width+x]=fNoise/fScaleAcc;
        }
    }
    return output;
}




uint32_t Rnd::Lehmer32() {
    seed+=0xe120fc15;
    uint64_t tmp;
    tmp=(uint64_t)seed * 0x4a39b70d;
    uint32_t m1=(tmp>>32) ^ tmp;
    tmp=(uint64_t)m1*0x12fad5c9;
    uint32_t m2=(tmp>>32) ^ tmp;
    return m2;
}
int Rnd::rndInt(int min, int max) {
    return (Lehmer32() % (max-min))+min;
}
double Rnd::rndDouble(double min, double max) {
    return ((double)Lehmer32() / (double)(0x7FFFFFFF))*(max-min)+min;
}


int Rnd::rndIntNormal(int min, int max) {
    return (std::rand()%(max-min))+min;
}


