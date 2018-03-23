//
// Created by edgar on 22/03/18.
//

#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0)  {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect Rect::SumVec2(Vec2 v) {
    return Rect(x + v.x, y + v.y, w, h);
}

Rect Rect::SubVec2(Vec2 v) {
    return Rect(x - v.x, y - v.y, w, h);
}

Vec2 Rect::CenterCoord() {
    return Vec2(x + (w/2), y + (h/2));
}

float Rect::DistRecs(Rect r) {
    Vec2 v = this->CenterCoord();
    return v.Dist(r.CenterCoord());
}

bool Rect::Contains(Vec2 v) {
    return (v.x < (x + w) && v.x >= x) && (v.y < (y + h) && v.y >= y);
}