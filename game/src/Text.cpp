//
// Created by edgar on 12/05/18.
//

#include <Game.h>
#include <Camera.h>

#include <Resources.h>
#include "Text.h"

Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated),
                                                                                                                   fontFile(move(fontFile)),
                                                                                                                   fontSize(fontSize),
                                                                                                                   style(style),
                                                                                                                   text(move(text)),
                                                                                                                   color(color),
                                                                                                                   texture(nullptr) {
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {}

void Text::Render() {
    auto box = associated.box;
    SDL_Rect srcRect = {0, 0, (int)box.w, (int)box.h};
    SDL_Rect dstRect = {(int)(box.GetCenter() - Vec2(GAME_WIDTH/2, GAME_HEIGHT/2) - Camera::pos).x, (int)(box.GetCenter() - Vec2(GAME_WIDTH/2, GAME_HEIGHT/2) - Camera::pos).y, srcRect.w, srcRect.h};
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(string type) {
    return type == TEXT_TYPE;
}

void Text::setText(string text) {
    Text::text = move(text);
    RemakeTexture();
}

void Text::setColor(SDL_Color color) {
    Text::color = color;
    RemakeTexture();
}

void Text::setStyle(TextStyle style) {
    Text::style = style;
    RemakeTexture();
}

void Text::setFontFile(string fontFile) {
    Text::fontFile = move(fontFile);
}

void Text::setFontSize(int fontSize) {
    Text::fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    font = Resources::GetFont(fontFile, fontSize);

    SDL_Surface *surface = nullptr;
    if(style == TextStyle::SOLID) surface = TTF_RenderText_Solid(font, text.c_str(), color);
    else if(style == TextStyle::SHADED) surface = TTF_RenderText_Shaded(font, text.c_str(), color, { 0, 0, 0, 255 });
    else if(style == TextStyle::BLENDED) surface = TTF_RenderText_Blended(font, text.c_str(), color);

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_SetTextureAlphaMod(texture, color.a);

    if(surface) {
        associated.box.w = surface->w;
        associated.box.h = surface->h;
    }

    SDL_FreeSurface(surface);

}
