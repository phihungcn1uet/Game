#pragma once
#include "LibFile.h"
struct sBoom {
	int x, y;
	sBoom(int startX, int startY) : x(startX), y(startY) {}
};
class Boom : public Enemy {
public:
	Boom();
	~Boom();
	bool loadFromFileBoom(std::string path, SDL_Renderer* screen);
	void free();
	void boommove(int& a, SDL_Renderer* screen, character& character, bool& quit,  const bool& check);
	void random(const int& a);
private:
	SDL_Texture* bTexture;
	SDL_Rect bBox;
	int x_pos;
	int y_pos;
	std::vector <sBoom> sBoom1;
};