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
	//load file rocket
	bool loadFromFileRocket(std::string path, SDL_Renderer* screen);
	//random ten lua sau 1 khoan thoi gian
	void random(const int& a);
	// di chuyen ten lua
	void rocketmove(SDL_Renderer* screen, character& character, bool& death, const bool& collision,const bool& bullettype, std::vector <Bullet>& bullets);
	//free
	void free();
	//vector ten lua
	std::vector <sRocket> sRocket1;
private:
	// texture ten lua
	SDL_Texture* rTexture;
	//box ten lua
	SDL_Rect rBox;
	// vi tri ten lua
	int x_pos;
	int y_pos;
	//thoi gian random ten lua
	const int TimeRanRocket = 7;
};