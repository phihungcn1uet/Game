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
	// load file bom
	bool loadFromFileBoom(std::string path, SDL_Renderer* screen);
	//random bom sau 1 khoang thoi gian xac dinh
	void random(const int& a);
	//di chuyen bom
	void boommove(SDL_Renderer* screen, character& character, bool& death, const bool& collision, const bool& bullettype, std::vector <Bullet>& bullets);
	//free
	void free();
	//vector bom
	std::vector <sBoom> sBoom1;
private:
	//texture boom
	SDL_Texture* bTexture;
	// boom box
	SDL_Rect bBox;
	//vi tri cua bom
	int x_pos;
	int y_pos;
	// thoi gian random bom
	int TimeRanBoom = 9;
};