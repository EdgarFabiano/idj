//
// Created by edgar on 22/03/18.
//

#include "Rect.h"

Rect::Rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
