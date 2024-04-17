#pragma once
#include "LibFile.h"
class TextObject : public BaseObject {
public:
	enum TextColor {
	RED_TEXT = 0,
	WHITE_TEXT = 1,
	BLACK_TEXT =2,
	};
	TextObject();
	~TextObject();
	void SetText(const std::string& text) { str_val = text; };
	void SetColor(const int&type);
	void CreateGameText(TTF_Font * font, SDL_Renderer* screen);
private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* mText;



};