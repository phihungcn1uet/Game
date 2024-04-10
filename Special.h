#pragma once
#include "LibFile.h"
struct specialpos {
	int x, y;
	specialpos(int startX, int startY) : x(startX), y(startY) {}
};
class Special: public Enemy {
public:
	Special();
	~Special();
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void free();
	void randomspecial(const int &a);
	void specialappearance(SDL_Renderer* screen, character& chacracter,bool&check, const int& a);
private:
	SDL_Texture* special;
	SDL_Rect sBox;
	std::vector <specialpos> specialpos1;
	int time1;
};