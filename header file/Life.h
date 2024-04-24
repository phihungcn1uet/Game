#pragma once
#include "LibFile.h"
struct animationlife {
	int x_pos;
	int y_pos;
	animationlife(int x, int y) : x_pos(x), y_pos(y) {}
};
class Life : public BaseObject{
public:
	Life();
	~Life();
	// load mau nhan vat
	bool loadFromFileLife(std::string path, SDL_Renderer* screen);
	// load hoat anh mau nhan vat
	void loadlifeani(SDL_Renderer* screen, bool& death,bool& secondplay, character& character,int &specialnum, int& time,bool & collision, bool &playgame, Figure& figure);
	// free
	void free();
	// vector mau han vat
	std::vector <animationlife> animationlife1;
private:
	// texture mau nhan vat
	SDL_Texture* mTextureLife;
	// Box mau nhan vat
	SDL_Rect lBox;
	// Thoi gian chet
	int timepoint;
};