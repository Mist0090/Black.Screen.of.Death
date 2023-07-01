#pragma once
#include "system.h"

#define PI 3.141592f

#define SineWave(t, freq, sampleCount) sinf(2.f * 3.1415f * ((float)(freq) * (float)(t) / (float)(sampleCount)))
#define SquareWave(t, freq, sampleCount) (((uint8_t)(2.f * (float)(freq) * ((t) / (float)(sampleCount))) % 2) == 0 ? 1.f : -1.f)
#define TriangleWave(t, freq, sampleCount) (4.f * ( float )fabsf(((float)(t) / ((float)(sampleCount) / (float)(freq))) - floorf(((float)(t) / ((float)(sampleCount) / (float)(freq)))) - .5f) - 1.f)
#define SawtoothWave(t, freq, sampleCount) (fmodf(((float)(t) / (float)(sampleCount)), (1.f / (float)(freq))) * (float)(freq) * 2.f - 1.f)

void Reflect2D ( int *x, int *y, int w, int h );