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
class Figure{
public:
	static const int FIGURE_WIDTH = 64;
	static const int FIGURE_HEIGHT = 64;
	static const int FIGURE_VEL = 6;
	Figure();
	~Figure();
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void handleEvent(SDL_Event& e);
	bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
	void move(SDL_Renderer* screen);
	void ColliisonWall(SDL_Rect& wall);
	void Gravity();
	void setCamera(SDL_Rect& camera);
	void checkarround();
private:
	character character;
	SDL_Texture* mTexture;
	int x_pos;
    int y_pos;
	int status;
	int numcheck[MAX_MAP_Y][MAX_MAP_X];
};



#endif // !FIGURE_H_
