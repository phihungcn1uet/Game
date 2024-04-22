#pragma once
#include "LibFile.h"
class Menu : public BaseObject {
public:
	Menu();
	~Menu();
	void startmenu(SDL_Event& e, bool& playgame, bool& quit, bool& secondplay, TTF_Font* font, SDL_Renderer* screen, void Resetgame());
	void pausemenu(SDL_Event &e, bool& playgame, bool &pausegame, bool& quit, TTF_Font* font, SDL_Renderer* screen);
	bool checkFocus(const int& x, const int& y, SDL_Rect& rect);
private:
};