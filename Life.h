#pragma once
#include "LibFile.h"
struct animationlife {
	int x_pos;
	int y_pos;
	animationlife(int x, int y) : x_pos(x), y_pos(y) {}
};
class Life {
public:
	Life();
	~Life();
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void free();
	void loadlifeani(SDL_Renderer* screen, bool& death, character& character,int &specialnum, int& time,bool & collision, bool &playgame, Figure& figure);
	std::vector <animationlife> animationlife1;
private:
	SDL_Texture* mTextureLife;
	SDL_Rect lBox;
	int timepoint;
};