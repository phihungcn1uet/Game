#include "LibFile.h"
Figure :: Figure() {
	character.velocityX = 0;
	character.velocityY = 0;
	mTexture = NULL;
	mTextureBullet = NULL;
	character.mBox = { 0,0,0,0 };
	rectbullet = { 0,0,0,0 };
	mTextureFireBall=NULL;
	rectfireball = { 0,0,0,0 };
}

Figure :: ~Figure() {
	free();
	free1();
}

bool Figure::loadFromFile(std::string path, SDL_Renderer* screen) {
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
			character.mBox.w = loadedSurface->w;
			character.mBox.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void Figure::move(SDL_Renderer* screen) {
	character.mBox.x += character.velocityX;
	character.mBox.y += character.velocityY;
	if (character.mBox.x < 0) {
		character.mBox.x = 0;
	}
	else if (character.mBox.x + FIGURE_WIDTH > SCREEN_WIDTH) {
		character.mBox.x = SCREEN_WIDTH - FIGURE_WIDTH;
	}
	if (character.mBox.y < 0) {
		character.mBox.y = 0;
	}
	else if (character.mBox.y + FIGURE_HEIGHT > SCREEN_HEIGHT) {
		character.mBox.y = SCREEN_HEIGHT - FIGURE_HEIGHT;
	}
	SDL_RenderCopy(screen, mTexture, NULL, &character.mBox);
}

void Figure::handleEvent(SDL_Event &e,SDL_Renderer *screen) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
			switch (e.key.keysym.sym )
			{
			case SDLK_w: character.velocityY -= FIGURE_VEL; break;
			case SDLK_s: character.velocityY += FIGURE_VEL; break;
			case SDLK_a: character.velocityX -= FIGURE_VEL; break;
			case SDLK_d: character.velocityX += FIGURE_VEL; break;
			case SDLK_p:
				if (bullets.size() < 12)
					bullets.push_back(Bullet(character.mBox.x + character.mBox.w, character.mBox.y + FIGURE_WIDTH / 2, 6));
				soundnormalbullet = Mix_LoadWAV("sound/soundnormalbullet.wav");
				Mix_PlayChannel(-1, soundnormalbullet, 0);
				break;
			}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: character.velocityY += FIGURE_VEL; break;
		case SDLK_s: character.velocityY -= FIGURE_VEL; break;
		case SDLK_a: character.velocityX += FIGURE_VEL; break;
		case SDLK_d: character.velocityX -= FIGURE_VEL; break;
		}
	}
}

bool Figure::loadFromFileBullet(std::string path, SDL_Renderer* screen) {
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
			rectbullet.w = loadedSurface->w;
			rectbullet.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTextureBullet = newTexture;
	return mTextureBullet != NULL;
}

bool Figure :: loadFromFileFireBall(std::string path, SDL_Renderer* screen) {
	free1();
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
			rectfireball.w = loadedSurface->w;
			rectfireball.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTextureFireBall = newTexture;
	return mTextureFireBall != NULL;
}
void Figure::movebullet(SDL_Renderer* screen) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].x += bullets[i].speed;
		rectbullet.x = bullets[i].x;
		rectbullet.y = bullets[i].y;
		SDL_RenderCopy(screen, mTextureBullet, NULL, &rectbullet);
		if (bullets[i].x > SCREEN_WIDTH - 30) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}
void Figure::moveball(SDL_Renderer* screen) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].x += bullets[i].speed;
		rectfireball.x = bullets[i].x;
		rectfireball.y = bullets[i].y;
		SDL_RenderCopy(screen, mTextureFireBall, NULL, &rectfireball);
		if (bullets[i].x > SCREEN_WIDTH - 30) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}
void Figure::free() {
	if (mTextureBullet != NULL) {
		SDL_DestroyTexture(mTextureBullet);
		mTextureBullet = NULL;
		rectbullet = { 0,0,0,0 };
	}
}
void Figure::free1() {
	if (mTextureFireBall != NULL) {
		SDL_DestroyTexture(mTextureFireBall);
		mTextureFireBall = NULL;
		rectfireball = { 0,0,0,0 };
	}
}
