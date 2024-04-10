#pragma once
#include "LibFile.h"
const int Rocketvel = 15;
struct sRocket {
	int x, y;
	sRocket(int startX, int startY) : x(startX), y(startY) {}
};
class Rocket : public Enemy {
public:
	Rocket();
	~Rocket();
	bool loadFromFileRocket(std::string path, SDL_Renderer* screen);
	void free();
	void rocketmove(int& a, SDL_Renderer* screen, character& character, bool& quit, const bool& check);
	void random(const int& a);
private:
	SDL_Texture* rTexture;
	SDL_Rect rBox;
	int x_pos;
	int y_pos;
	std :: vector <sRocket> sRocket1;
};