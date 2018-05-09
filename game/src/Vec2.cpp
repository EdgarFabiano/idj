//
// Created by edgar on 22/03/18.
//

#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::Sum(Vec2 v) {
    return {x + v.x, y + v.y};
}

Vec2 Vec2::Sub(Vec2 v) {
    return {x - v.x, y - v.y};
}

Vec2 Vec2::Mul(const float escalar) {
    return {x * escalar, y * escalar};
}

float Vec2::Mag() {
    return sqrtf((x * x) + (y * y));
}

Vec2 Vec2::Norm() {
    float mag = Mag();
    return {x / mag, y / mag};
}

float Vec2::Dist(Vec2 v) {
    return (*this - v).Mag();
}

float Vec2::InclX() {
    return atan2(y, x);
}

float Vec2::Incl(Vec2 v) {
    Vec2 ret = Sub(v);
    return ret.InclX();
}

Vec2 Vec2::Rotate(const float ang) {
    return {(x * cos(ang)) - (y * sin(ang)), (y * cos(ang)) + (x * sin(ang))};
}

Vec2 Vec2::RotateDeg(const float angDeg) {
    auto ang = (float)angDeg * (M_PI/180.0f);
    return {(x * cos(ang)) - (y * sin(ang)), (y * cos(ang)) + (x * sin(ang))};
}

Vec2 Vec2::operator+(const Vec2& v) {
    return Sum(v);
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &v) {
    return Sub(v);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float escalar) {
    return Mul(escalar);
}

Vec2 Vec2::operator*(const float rhs) const {
    return {x * rhs, y * rhs};
}

bool Vec2::operator==(const Vec2 &v) {
    return x == v.x && y == v.y;
}

Vec2 Vec2::operator+=(const Vec2 &v) {
    return *this = *this + v;
}

Vec2 Vec2::operator-=(const Vec2 &v) {
    return *this = *this - v;
}
