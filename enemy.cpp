#include "LibFile.h"
Enemy :: Enemy() {
	eBox.x = 1280;
	eBox.y = 64;
	mTextureEnemy = NULL;
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

void Enemy::enemymove(SDL_Renderer* screen,std :: vector <Bullet>& bullets,bool &quit, character &character) {
	//std::cout << enemys.size() << std::endl;
	for (int i = 0; i < enemys.size(); i++) {
		if (i == 0) {
			enemys[i].x -= 6;
			eBox = { enemys[i].x, enemys[i].y , FIGURE_WIDTH, FIGURE_HEIGHT };
			SDL_RenderCopy(screen, mTextureEnemy, NULL, &eBox);
			if (enemys[i].x < 0) {
				enemys.erase(enemys.begin() + i);
				i--;
			}
		}
		else if (i >= 1 && enemys[i - 1].x < 1000) {
			enemys[i].x -= 6;
			eBox = { enemys[i].x, enemys[i].y , FIGURE_WIDTH, FIGURE_HEIGHT };
			SDL_RenderCopy(screen, mTextureEnemy, NULL, &eBox);
			if (enemys[i].x < 0) {
				enemys.erase(enemys.begin() + i);
				i--;
			}
			if (bullets.size() != 0) {
				for (int j = 0; j < bullets.size(); j++) {
					SDL_Rect a = { bullets[j].x,bullets[j].y,16,16 };
					SDL_Rect b = { enemys[i].x,enemys[i].y,FIGURE_WIDTH,FIGURE_HEIGHT };
					SDL_Rect c = { enemys[i - 1].x,enemys[i - 1].y,FIGURE_WIDTH,FIGURE_HEIGHT };
					if (checkCollision(a,b)) {
						enemys.erase(enemys.begin() + i);
						bullets.erase(bullets.begin() + j);
					}
					else if (checkCollision(a,c)) {
						enemys.erase(enemys.begin() + i - 1);
						bullets.erase(bullets.begin() + j);
					}
				}
			}
		}
	}
	for (int i = 0; i < enemys.size(); i++) {
		SDL_Rect a = { enemys[i].x,enemys[i].y,FIGURE_WIDTH,FIGURE_HEIGHT };
		if (checkCollision(character.mBox, a)) {
			quit = true;
		}
	}
}



void Enemy::random() {
	int x_pos_enemy = 1280;
	int y_pos_enemy = (rand() % 640);
	enemys.push_back(numEnemy(x_pos_enemy, y_pos_enemy, 2));
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