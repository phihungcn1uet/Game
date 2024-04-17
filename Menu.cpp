#include "LibFile.h"

Menu::Menu() {

}

Menu::~Menu() {

}

void Menu::startmenu(SDL_Event& e, bool& playgame) {
	const int items = 3;
	SDL_Rect menu_pos[items];
	menu_pos[0].x = 200;
	menu_pos[0].y = 400;

	menu_pos[1].x = 200;
	menu_pos[2].y = 200;
	TextObject textmenu[items];
	textmenu[0].SetText("Play Game");
	textmenu[0].SetColor(TextObject::BLACK_TEXT);
	textmenu[0].SetRect(menu_pos[0].x = 200, menu_pos[0].y = 400);
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < 860 && x> 320 && y > 400 && y < 560) {
			
			playgame = true;
		}
	}
}