#pragma once
#ifndef FIGURE_H_
#define FIGURE_H_
#define MAX_MAP_Y 10
#define MAX_MAP_X 20
#include "LibFile.h"
//Ham nhan vat
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
	Figure();
	~Figure();
	// Nhan vat
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void handleEvent(SDL_Event &e,SDL_Renderer * screen);
	// load 2 loai dan ban
	bool loadFromFileBullet(std::string path, SDL_Renderer* screen);
	bool loadFromFileFireBall(std::string path, SDL_Renderer* screen);
	//di chuyen nhan vat
	void move(SDL_Renderer* screen);
	//di chuyen dan
	void movebullet(SDL_Renderer* screen);
	//di chuyen vien dan dac biet
	void moveball(SDL_Renderer* screen);
	//vector dan
	std::vector<Bullet> bullets;
	character character;
	//free
	void free();
	void free1();
private:
	//Nhan vat
	SDL_Texture* mTexture;
	//Dan ban
	SDL_Texture* mTextureBullet;
	SDL_Rect rectbullet;
	SDL_Texture *mTextureFireBall;
	SDL_Rect rectfireball;
};



#endif // !FIGURE_H_
