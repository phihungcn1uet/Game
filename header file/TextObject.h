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
	//load text
	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	// set mau cho text
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	// render text
	void RenderText(SDL_Renderer* screen,
		int x_pos, int y_pos,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	//cai dat text
	void SetText(const std::string& text) { str_val = text; }
	//lay text
	std::string GetText() const { return str_val; ; }
	//free
	void free();
private:
	// chuoi ki tu lay lam text
	std::string str_val;
	// mau cua text
	SDL_Color text_color;
	//texture text
	SDL_Texture* mText;
	// chieu  dai va chieu rong text
	int width;
	int height;


};