#pragma once
#ifndef FIGURE_H_
#define FIGURE_H_
#define MAX_MAP_Y 10
#define MAX_MAP_X 20
#include "LibFile.h"

struct character {
	int velocityX;
	int velocityY;
	int x_pos;
	int y_pos;
	SDL_Rect mBox;
};

struct Bullet {
	int x, y;
	int speed;

	Bullet(int startX, int startY, int bulletSpeed) : x(startX), y(startY), speed(bulletSpeed) {}
};

class Figure{
public:
	const int FIGURE_VEL = 16;
	Figure();
	~Figure();
	// Nhan vat
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void handleEvent(SDL_Event& e,SDL_Renderer * screen);
	// Dan ban
	bool loadFromFileBullet(std::string path, SDL_Renderer* screen);
	void move(SDL_Renderer* screen,bool &quit);
	void movebullet(SDL_Renderer* screen);
	std::vector<Bullet> bullets;
	character character;
	//free
	void free();
private:
	//Nhan vat
	SDL_Texture* mTexture;
	//Dan ban
	SDL_Texture* mTextureBullet;
	SDL_Rect rectbullet;
};



#endif // !FIGURE_H_
