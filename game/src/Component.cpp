//
// Created by edgar on 23/03/18.
//

#include "Component.h"

Component::Component(GameObject &associated) : associated(associated) {}

Component::~Component() {}

void Component::Start() {}

