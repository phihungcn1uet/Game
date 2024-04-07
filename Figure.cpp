#include "LibFile.h"
Figure :: Figure() {
	character.velocityX = 0;
	character.velocityY = 0;
	mTexture = NULL;
	mTextureBullet = NULL;
	character.mBox = { 0,0,0,0 };
	rectbullet = { 0,0,0,0 };
}

Figure :: ~Figure() {
	free();
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

void Figure::move(SDL_Renderer* screen,bool &quit) {
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

void Figure::handleEvent(SDL_Event& e,SDL_Renderer *screen) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: character.velocityY -= FIGURE_VEL; break;
		case SDLK_s: character.velocityY += FIGURE_VEL; break;
		case SDLK_a: character.velocityX -= FIGURE_VEL; break;
		case SDLK_d: character.velocityX += FIGURE_VEL; break;
		case SDLK_e:
		if(bullets.size()<6)
		bullets.push_back(Bullet(character.mBox.x + character.mBox.w, character.mBox.y +FIGURE_WIDTH/2, 1));
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
void Figure::movebullet(SDL_Renderer* screen) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].x += 6;
		rectbullet.x = bullets[i].x;
		rectbullet.y = bullets[i].y;
		SDL_RenderCopy(screen, mTextureBullet, NULL, &rectbullet);
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
	}
}

