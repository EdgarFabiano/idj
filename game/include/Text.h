//
// Created by edgar on 12/05/18.
//

#ifndef SRC_TEXT_H
#define SRC_TEXT_H


#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Component.h"

#define TEXT_TYPE "Text"

class Text : public Component{
public:
    enum TextStyle{SOLID, SHADED, BLENDED};
    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
    virtual ~Text();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void setText(string text);
    void setColor(SDL_Color color);
    const SDL_Color &GetColor() const;
    void setStyle(TextStyle style);
    void setFontFile(string fontFile);
    void setFontSize(int fontSize);


private:
    void RemakeTexture();

    shared_ptr<TTF_Font> font;
    SDL_Texture* texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;

};


#endif //SRC_TEXT_H
