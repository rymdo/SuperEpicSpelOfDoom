#include "../include/Vec.h"

using namespace std;

void Vec::Normalize()
{
    if(x == 0 && y == 0) return;

    float k = 1/(sqrt(pow(x, 2) + pow(y, 2)));

    x *= k;
    y *= k;
}

Vec operator* (int i, Vec v) { return v*i; }
Vec operator* (Vec v, int i)
{
    v.x *= i;
    v.y *= i;
    return (v);
}

Vec operator* (float f, Vec v) { return v*f; }
Vec operator* (Vec v, float f)
{
    v.x *= f;
    v.y *= f;
    return (v);
}

Vec Vec::operator*=(float f)
{
    x *= f;
    y *= f;
}
