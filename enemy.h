#pragma once
#include "LibFile.h"
const int bossHP = 20;
struct numEnemy  {
	int x, y;
	int speed;
	numEnemy(int startX, int startY, int Speed) : x(startX), y(startY), speed(Speed) {}
};
class Enemy : public BaseObject {
public:
	Enemy();
	~Enemy();
	bool loadFromFileEnemy(std::string path, SDL_Renderer* screen);
	bool loadFromFileBoss(std::string path, SDL_Renderer* screen);
	void enemymove(SDL_Renderer* screen,std::vector <Bullet>& bullets,bool & death,character &character,const bool& collision);
	void bossmove(SDL_Renderer* screen, std::vector <Bullet>& bullets, bool& death, character& character, const bool& collision, const int& a, TTF_Font* font_hp);
	void random();
	void timerandomboss(const int &a);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	void free();
	void SetScore(TTF_Font* font, SDL_Renderer* screen);
	std::vector <numEnemy> enemys;
	std::vector <numEnemy> boss1;
	std::vector <numEnemy> skill1;
	long long score;
private:
	SDL_Texture* mTextureEnemy;
	SDL_Texture* mTextureBoss;
	SDL_Rect eBox;
	SDL_Rect BossBox;
	int HP = bossHP;
	int skill;
	SDL_Rect bossskillBox;
};