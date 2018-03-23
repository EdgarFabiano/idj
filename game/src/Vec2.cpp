//
// Created by edgar on 22/03/18.
//

#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::Sum(Vec2 v) {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::Sub(Vec2 v) {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::Mul(float escalar) {
    return Vec2(x * escalar, y * escalar);
}

float Vec2::Mag() {
    return sqrtf(((x * x) + (y * y)));
}

Vec2 Vec2::Norm() {
    float mag = this->Mag();
    return Vec2(x / mag, y / mag);
}

float Vec2::Dist(Vec2 v) {
    Vec2 ret = this->Sub(v);
    return ret.Mag();
}

float Vec2::InclX() {
    return atan2(x, y);
}

float Vec2::Incl(Vec2 v) {
    Vec2 ret = this->Sub(v);
    return ret.InclX();
}

Vec2 Vec2::Rotate(float ang) {
    return Vec2((x * cos(ang)) - (y * sin(ang)), (y * cos(ang)) + (x * sin(ang)));
}

Vec2& Vec2::operator+(const Vec2& v) {
    x += v.x;
    y += v.y;

    return *this;
}

Vec2& Vec2::operator-(const Vec2 &v) {
    x -= v.x;
    y -= v.y;

    return *this;
}

Vec2 &Vec2::operator=(const Vec2 &v) {
    x = v.x;
    y = v.y;

    return *this;
}
