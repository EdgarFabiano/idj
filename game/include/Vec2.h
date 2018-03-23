//
// Created by edgar on 22/03/18.
//

#ifndef VEC2_CLASS
#define VEC2_CLASS

#include <math.h>


class Vec2 {
public:
    float x, y;

    Vec2();

    Vec2(float x, float y);

    Vec2 Sum(Vec2 v);

    Vec2 Sub(Vec2 v);

    Vec2 Mul(float escalar);

    float Mag();

    Vec2 Norm();

    float Dist(Vec2 v);

    float InclX();

    float Incl(Vec2 v);

    Vec2 Rotate(float ang);

    Vec2& operator+(const Vec2& v);

    Vec2& operator-(const Vec2& v);

    Vec2& operator=(const Vec2& v);

};


#endif //SRC_VEC2_H
