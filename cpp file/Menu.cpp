#include "LibFile.h"
TextObject textstartmenu[2];
TextObject textpausemenu[2];
Menu::Menu() {
	
}

Menu::~Menu() {

}

void Menu::startmenu(SDL_Event &e, bool& playgame, bool& quit, bool& secondplay, long long& timewhenplay, TTF_Font* font, SDL_Renderer* screen, void Resetgame()) {
	
	SDL_Rect GetTextPos[2];
	textstartmenu[0].SetText("Play Game");
	textstartmenu[0].loadFromRenderText(font, screen);
	textstartmenu[0].RenderText(screen, 250, 480);
	GetTextPos[0] = { 250,480,320,70 };

	textstartmenu[1].SetText("Exit");
	textstartmenu[1].loadFromRenderText(font, screen);
	textstartmenu[1].RenderText(screen, 250, 550);
	GetTextPos[1] = { 250,550,120,70 };
	
		switch (e.type) {
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			for (int i = 0; i < 2; i++) {
				if (checkFocus(x, y, GetTextPos[i])) {
					textstartmenu[i].SetColor(TextObject::RED_TEXT);
				}
				else if (!checkFocus(x, y, GetTextPos[i])) {
					textstartmenu[i].SetColor(TextObject::BLACK_TEXT);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int a, b;
			SDL_GetMouseState(&a, &b);
			if (a > 250 && a < 570 && b>480 && b < 550) {
				playgame = true;
				if (secondplay == true) {
					Resetgame();
				}
				if (secondplay == false) {
					timewhenplay = int(SDL_GetTicks64());
				}
			}
			else if (a > 250 && a < 370 && b>550 && b < 620) {
				quit = true;
			}
		default:
			break;
		}
}


void Menu::pausemenu(SDL_Event& e, bool &playgame, bool& pausegame, bool& quit, TTF_Font* font, SDL_Renderer* screen,Figure &figure) {
	figure.character.velocityX = 0;
	figure.character.velocityY = 0;
	SDL_Rect GetTextPos[2];
	textpausemenu[0].SetText("Play Again");
	textpausemenu[0].loadFromRenderText(font, screen);
	textpausemenu[0].RenderText(screen, 250, 480);
	GetTextPos[0] = { 250,480,320,70 };

	textpausemenu[1].SetText("Exit");
	textpausemenu[1].loadFromRenderText(font, screen);
	textpausemenu[1].RenderText(screen, 250, 550);
	GetTextPos[1] = { 250,550,120,70 };
	
		switch (e.type) {
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			for (int i = 0; i < 2; i++) {
				if (checkFocus(x, y, GetTextPos[i])) {
					textpausemenu[i].SetColor(TextObject::RED_TEXT);
				}
				else if (!checkFocus(x, y, GetTextPos[i])) {
					textpausemenu[i].SetColor(TextObject::BLACK_TEXT);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int a, b;
			SDL_GetMouseState(&a, &b);
			if (a > 250 && a < 570 && b>480 && b < 550) {
				playgame = true;
				pausegame = false;
			}
			else if (a > 250 && a < 370 && b>550 && b < 620) {
				quit = true;
			}

		default:
			break;
		}

}


bool Menu::checkFocus(const int& x, const int& y, SDL_Rect& rect) {
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h) {
		return true;
	}
	return false;
}

