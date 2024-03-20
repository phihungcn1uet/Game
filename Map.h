#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "LibFile.h"
#define MAX_TILE 20
#define MAX_MAP_X 20
#define MAX_MAP_Y 10
#define MAP_SIZE 64
class GameMap {

public:
	GameMap();
	~GameMap();

	void loadFileMap(std::string name);
	void DrawMap(SDL_Renderer* screen);
	bool loadFromFile(std::string path, SDL_Renderer* screen);
private:
	SDL_Texture *mTexture;
	int MapHeight;
	int MapWidth;
	int numcheck[MAX_MAP_Y][MAX_MAP_X];
};
#endif