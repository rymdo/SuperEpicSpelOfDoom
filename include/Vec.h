#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include <cmath>
#include <iostream>

using namespace std;

struct Vec
{
    float x,y;

    float Abs();
    void Normalize();
    Vec operator*= (float f);
};

Vec operator* (Vec v, int i);
Vec operator* (int i, Vec v);
Vec operator* (Vec v, float f);
Vec operator* (float f, Vec v);

#endif // VEC_H_INCLUDED
