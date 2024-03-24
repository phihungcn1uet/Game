#include "LibFile.h"
Figure :: Figure() {
	character.velocityX = 0;
	character.velocityY = 0;
	x_pos = 0;
	y_pos = 0;
	mTexture = NULL;
	mTextureBullet = NULL;
	rect_ = { 0,0,0,0 };
	character.mBox = { 0,0,FIGURE_WIDTH,FIGURE_HEIGHT };
}

Figure :: ~Figure() {

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

void Figure::move(SDL_Renderer *screen) {
	x_pos += character.velocityX;
	y_pos += character.velocityY;
	
	character.mBox.x = x_pos;
	character.mBox.y = y_pos;
	toadoX = x_pos;
	toadoY = y_pos;
	//std::cout << toadoX << "-" << toadoY << "-" << character.mBox.w << "-" << character.mBox.h << std::endl;
	if (x_pos < 0) {
		x_pos = 0;
	}
	else if (x_pos + FIGURE_WIDTH > SCREEN_WIDTH) {
		x_pos = SCREEN_WIDTH - FIGURE_WIDTH;
	}
	if (y_pos < 0) {
		y_pos = 0;
	}
	else if (y_pos + FIGURE_HEIGHT > SCREEN_HEIGHT) {
		y_pos = SCREEN_HEIGHT - FIGURE_HEIGHT;
	}
	SDL_RenderCopy(screen, mTexture, NULL, &character.mBox);
}

void Figure::handleEvent(SDL_Event& e,SDL_Renderer *screen) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: character.velocityY -= FIGURE_VEL; break;
		case SDLK_s: character.velocityY += FIGURE_VEL; break;
		case SDLK_a: character.velocityX -= FIGURE_VEL; break;
		case SDLK_d: character.velocityX += FIGURE_VEL; break;
		case SDLK_e:
		bullets.push_back(Bullet(character.mBox.x + character.mBox.w, character.mBox.y + FIGURE_HEIGHT/2, 1));
		break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
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
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTextureBullet = newTexture;
	return mTextureBullet != NULL;
}
void Figure::movebullet(SDL_Renderer* screen) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].x += 6;
		SDL_Rect rectbullet = { bullets[i].x, bullets[i].y-FIGURE_HEIGHT/2, FIGURE_WIDTH, FIGURE_HEIGHT };
		SDL_RenderCopy(screen, mTextureBullet, NULL, &rectbullet);
		if (bullets[i].x > SCREEN_WIDTH - 30) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

