#pragma once
#include "LibFile.h"
struct numEnemy {
	int x, y;
	int speed;
	numEnemy(int startX, int startY, int Speed) : x(startX), y(startY), speed(Speed) {}
};
class Enemy {
public:
	Enemy();
	~Enemy();
	bool loadFromFileEnemy(std::string path, SDL_Renderer* screen);
	void enemymove(SDL_Renderer* screen,std::vector <Bullet>& bullets,bool & death,character &character,const bool& collision);
	void random();
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	void free();

private:
	SDL_Texture* mTextureEnemy;
	std::vector <numEnemy> enemys;
	SDL_Rect eBox;
};