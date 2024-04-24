#pragma once
#include "LibFile.h"
class Menu : public BaseObject {
public:
	Menu();
	~Menu();
	// menu ban dau
	void startmenu(SDL_Event& e, bool& playgame, bool& quit, bool& secondplay,long long &timewhenplay, TTF_Font* font, SDL_Renderer* screen, void Resetgame());
	// menu tam dung
	void pausemenu(SDL_Event& e, bool& playgame, bool &pausegame, bool& quit, TTF_Font* font, SDL_Renderer* screen, Figure& figure);
	// check forcus cua chuot
	bool checkFocus(const int& x, const int& y, SDL_Rect& rect);
private:
};