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
	//load normal enenmy va boss
	bool loadFromFileEnemy(std::string path, SDL_Renderer* screen);
	bool loadFromFileBoss(std::string path, SDL_Renderer* screen);
	bool loadFromFileBossSkill(std::string path, SDL_Renderer* screen);
	//ham di chuyen cho enemy va boss
	void enemymove(SDL_Renderer* screen,std::vector <Bullet>& bullets,bool & death,character &character,const bool& collision);
	void bossmove(SDL_Renderer* screen, std::vector <Bullet>& bullets, bool& death, const bool& bullettype, character& character, const bool& collision, const int& a, TTF_Font* font_hp);
	//ham random
	void random();
	void timerandomboss(const int &a);
	//ham va cham
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	//ham tinh diem
	void SetScore(TTF_Font* font, SDL_Renderer* screen);
	//free lan luot cho cac texture
	void free();
	void free1();
	void free2();
	//vector normal enemy
	std::vector <numEnemy> enemys;
	//vector boss
	std::vector <numEnemy> boss1;
	//vector skill boss
	std::vector <numEnemy> skill1;
	long long score;
private:
	//texture normal enemy
	SDL_Texture* mTextureEnemy;
	//texture boss
	SDL_Texture* mTextureBoss;
	//texture boss skill
	SDL_Texture* mTextureBossSkill;
	// box va cham
	SDL_Rect eBox;
	SDL_Rect BossBox;
	SDL_Rect BossBoxSkill;
	//cac du lieu kieu so nguyen khac
	int HP = bossHP;
	int skill;
	bool bossdeath;
	int TimeranBoss = 50;
};