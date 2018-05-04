//
// Created by edgar on 26/04/18.
//

#include <SDL_rect.h>
#include <Game.h>
#include <Camera.h>
#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    Rect aux = Rect();

    aux.w = associated.box.w * scale.x;
    aux.h = associated.box.h * scale.y;

    const Vec2 &center = associated.box.GetCenter();
    aux.x = center.x - aux.w/2;
    aux.y = center.y - aux.h/2;

    box = aux + offset.RotateDeg((float)(associated.angleDeg));
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).RotateDeg((float)(associated.angleDeg))
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y) - center).RotateDeg((float)(associated.angleDeg))
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).RotateDeg((float)(associated.angleDeg))
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x, box.y + box.h) - center).RotateDeg((float)(associated.angleDeg))
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type) {
    return type == COLLIDER_TYPE;
}

void Collider::setScale(const Vec2 &scale) {
    this->scale = scale;
}

void Collider::setOffset(const Vec2 &offset) {
    this->offset = offset;
}
