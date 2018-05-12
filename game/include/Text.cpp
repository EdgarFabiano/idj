//
// Created by edgar on 12/05/18.
//

#include "Text.h"

Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated) {

}

Text::~Text() = default;

void Text::Update(float dt) {

}

void Text::Render() {

}

bool Text::Is(string type) {
    return type == TEXT_TYPE;
}

void Text::setText(string text) {
    Text::text = text;
}

void Text::setStyle(TextStyle style) {
    Text::style = style;
}

void Text::setFontFile(string fontFile) {
    Text::fontFile = fontFile;
}

void Text::setFontSize(int fontSize) {
    Text::fontSize = fontSize;
}

void Text::setColor(SDL_Color color) {
    Text::color = color;
}

void Text::RemakeTexture() {

}
