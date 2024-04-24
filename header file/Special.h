#pragma once
#include "LibFile.h"
struct specialpos {
	int x, y;
	specialpos(int startX, int startY) : x(startX), y(startY) {}
};
class Special : public Enemy {
public:
	Special();
	~Special();
	//load hieu ung dac biet
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	//random hieu ung dac biet sau 1 khoang thoi gian
	void randomspecial(const int &a);
	// xuat hien hieu ung dac biet
	void specialappearance(SDL_Renderer* screen, character& chacracter,bool& collision, bool& bullettype, const int& a, Figure &sfigure);
	//free
	void free();
	// vector hieu ung dac biet
	std::vector <specialpos> specialpos1;
	int specialnumlife;
private:
	//texture hieu ung dac biet
	SDL_Texture* special;
	// box hieu ung dac biet
	SDL_Rect sBox;
	// thoi gian
	int time1;
	int TimeRanSpecial = 15;
};