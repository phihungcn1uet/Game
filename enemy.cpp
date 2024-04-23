#include "LibFile.h"
TextObject text1;

Enemy :: Enemy() {
	eBox.x = 1280;
	eBox.y = 64;
	mTextureEnemy = NULL;
	eBox = { 0,0,0,0 };
	text1.SetColor(TextObject::WHITE_TEXT);
	score = 0;
	skill = 0;
	mTextureBoss = NULL;
	BossBox = { 0,0,0,0 };
	bossskillBox = { 0,0,0,0 };
}
Enemy :: ~Enemy() {
	free();
}
bool Enemy::loadFromFileEnemy(std::string path, SDL_Renderer* screen) {
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			eBox.w = loadedSurface->w;
			eBox.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTextureEnemy = newTexture;
	return mTextureEnemy != NULL;
}

void Enemy::enemymove(SDL_Renderer* screen,std :: vector <Bullet>& bullets,bool & death, character &character, const bool& collision) {
	for (int i = 0; i < enemys.size(); i++) {
		if (i == 0) {
			enemys[i].x -= enemys[i].speed;
			eBox.x = enemys[i].x;
			eBox.y = enemys[i].y;
			SDL_RenderCopy(screen, mTextureEnemy, NULL, &eBox);
			if (enemys[i].x < 0) {
				enemys.erase(enemys.begin() + i);
			}
		}
		else if (i >= 1 && enemys[i - 1].x < 1000) {
			enemys[i].x -= enemys[i].speed;
			eBox.x = enemys[i].x;
			eBox.y = enemys[i].y;
			SDL_RenderCopy(screen, mTextureEnemy, NULL, &eBox);
			if (enemys[i].x < 0) {
				enemys.erase(enemys.begin() + i);
			}
			if (bullets.size() != 0) {
				for (int j = 0; j < bullets.size(); j++) {
					SDL_Rect a = { bullets[j].x,bullets[j].y,32,32 };
					SDL_Rect b = { enemys[i].x,enemys[i].y,FIGURE_WIDTH,FIGURE_HEIGHT };
					SDL_Rect c = { enemys[i - 1].x,enemys[i - 1].y,FIGURE_WIDTH,FIGURE_HEIGHT };
						if (checkCollision(a, b)) {
							enemys.erase(enemys.begin() + i);
							bullets.erase(bullets.begin() + j);
							score++;
						}
						else if (checkCollision(a, c)) {
							enemys.erase(enemys.begin() + i - 1);
							bullets.erase(bullets.begin() + j);
							score++;
						}
				}
			}
		}	
	}
	for (int i = 0; i < enemys.size(); i++) {
		SDL_Rect a = { enemys[i].x,enemys[i].y,FIGURE_WIDTH,FIGURE_HEIGHT };
		if (collision) {
			if (checkCollision(character.mBox, a)) {
				death = true;
			}
		}
	}
}



void Enemy::random() {
	int x_pos_enemy = 1280;
	int y_pos_enemy = rand() % (576+1-64)+64;
	int speed = rand() % (8-4+1) + 4;
	enemys.push_back(numEnemy(x_pos_enemy, y_pos_enemy, speed));
	if (enemys.size() > 10) enemys.erase(enemys.begin() + 10);
	
}

bool Enemy::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}
void Enemy::free() {
	if (mTextureEnemy != NULL)
	{
		SDL_DestroyTexture(mTextureEnemy);
		mTextureEnemy = NULL;
		eBox.x = 0;
		eBox.y = 0;
	}
}

void Enemy::SetScore(TTF_Font *font,SDL_Renderer *screen) {
	std::string str_score = "Score:";
	std::string str_val = std::to_string(score);
	str_score += str_val;
	text1.SetText(str_score);
	text1.loadFromRenderText(font, screen);
	text1.RenderText(screen, SCREEN_WIDTH - 400, 15);
}

bool Enemy::loadFromFileBoss(std::string path, SDL_Renderer* screen) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			BossBox.w = loadedSurface->w;
			BossBox.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTextureBoss = newTexture;
	return mTextureBoss != NULL;
}

void Enemy :: timerandomboss(const int& a) {
	int time = a / 1000;
	int du = a % 1000;
	int currenttime = 0;
	if (du < 30) {
		if (time % 15 == 0 && time != 0) {
			int currenttime = time;
			int x_pos = 1280;
			int y_pos = rand() % (300-200+1)+200;
			boss1.push_back(numEnemy(x_pos, y_pos,2));
			if (boss1.size() > 1) boss1.erase(boss1.begin() + 1);
			HP = bossHP;
		}
	}
}

void Enemy::bossmove(SDL_Renderer* screen, std::vector <Bullet>& bullets, bool& death, character& character, const bool& collision,const int &a,TTF_Font * font_hp) {
	for (int i = 0; i < boss1.size(); i++) {
		if (boss1[i].x > 960) {
			boss1[i].x -= boss1[i].speed;
		}
		else if (boss1[i].x < 960) {
			boss1[i].x = boss1[i].x;
		}
		BossBox.x = boss1[i].x;
		BossBox.y = boss1[i].y;
		SDL_RenderCopy(screen, mTextureBoss, NULL, &BossBox);
		skill1.push_back(numEnemy(boss1[i].x, boss1[i].y, 6));
		std::cout << skill1.size() << std::endl;
		if (skill1.size() > 1) skill1.erase(skill1.begin() + 1);
		
		if (skill1.size() > 0) {
			for (int k = 0; k < skill1.size(); k++) {
				skill1[k].x -= skill1[k].speed;
				bossskillBox.x = skill1[k].x;
				bossskillBox.y = skill1[k].y + 64;
				bossskillBox.w = 64;
				bossskillBox.h = 128;
				SDL_RenderCopy(screen, mTextureBoss, NULL, &bossskillBox);
				if (collision) {
					if (checkCollision(character.mBox, bossskillBox)) {
						death = true;
					}
				}
				for (int j = 0; j < bullets.size(); j++) {
					SDL_Rect a = { bullets[j].x,bullets[j].y,32,32 };
					if (checkCollision(a, bossskillBox)) {
							bullets.erase(bullets.begin() + j);
					}
				}
				if (skill1[k].x < 0) {
					skill1.erase(skill1.begin() + k);
				}
			}
			//Neu dan ban trung may bay
			if (bullets.size() != 0) {
				for (int j = 0; j < bullets.size(); j++) {
					SDL_Rect a = { bullets[j].x,bullets[j].y,32,32 };
					SDL_Rect b = { boss1[i].x,boss1[i].y,BossBox.w,BossBox.h };
					if (checkCollision(a, b)) {
						bullets.erase(bullets.begin() + j);
						HP--;
					}
					std::cout << HP << std::endl;
					if (HP == 0) {
						boss1.erase(boss1.begin() + i);
						skill1.clear();
						break;
					}
				}
			}
		}
		int bossheartbar = 570;
		TextObject textheart;
		for (int i = 0; i < HP; i++) {
			std::string hp = std :: to_string(HP);
			std::string text = "BOSS HP: " + hp;
			textheart.SetText(text);
			textheart.loadFromRenderText(font_hp, screen);
			textheart.RenderText(screen, 450, 9);
			loadFromFile("img/heartbar.png", screen);
			render(screen, NULL, bossheartbar, 15);
			bossheartbar += 10;
		}
	}
	if (boss1.size() > 0) {
		for (int i = 0; i < boss1.size(); i++) {
			SDL_Rect a = { boss1[i].x,boss1[i].y,BossBox.w,BossBox.h };
			if (collision) {
				if (checkCollision(character.mBox, a)) {
					death = true;
				}
			}
		}
	}
	
}