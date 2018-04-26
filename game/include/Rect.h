//
// Created by edgar on 22/03/18.
//

#ifndef RECT_CLASS
#define RECT_CLASS


#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Rect SumVec2(Vec2 v);
    Rect SubVec2(Vec2 v);
    Rect MulVec2(Vec2 v);

    Vec2 GetCenter();

    float DistRecs(Rect r);
    float DistVec2(Vec2 v);
    bool Contains(Vec2 v);

    Rect operator+(Vec2 offset);
    Rect operator+=(Vec2 v);

    Rect operator*(Vec2 scale);
    Rect operator*=(Vec2 scale);
};


#endif //SRC_RECT_H
