#pragma once
#include "LibFile.h"
class Menu : public BaseObject {
public:
	Menu();
	~Menu();
	void startmenu(SDL_Event &e,bool& playgame);
};