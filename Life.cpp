#include "LibFile.h"

Life::Life() {
	mTextureLife = NULL;
	lBox = { 0,0,0,0 };
	animationlife1.push_back(animationlife(0, 0));
	animationlife1.push_back(animationlife(32, 0));
	animationlife1.push_back(animationlife(64, 0));
	timepoint = 0;
}

Life::~Life(){
	free();
}

bool Life::loadFromFileLife(std::string path, SDL_Renderer* screen) {
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
			lBox.w = loadedSurface->w;
			lBox.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTextureLife = newTexture;
	return mTextureLife != NULL;
}


void Life::free() {
	if (mTextureLife != NULL)
	{
		SDL_DestroyTexture(mTextureLife);
		mTextureLife = NULL;
		lBox.x = 0;
		lBox.y = 0;
	}
}
void Life::loadlifeani(SDL_Renderer *screen,bool &death,bool& secondplay, character &character, int &specialnum, int &time, bool& collision,bool &playgame, Figure &figure) {
	int currenttime = time / 1000;
	int l = animationlife1.size();
	if (specialnum == 1) {	
		if (l == 1) {
			animationlife1.push_back(animationlife(32,0));
			//animationlife1.pop_back();
			
		}
		else if (l > 1) {
			animationlife1.push_back(animationlife(animationlife1[l - 1].x_pos + 32, 0));
			specialnum = 0;
		}
	}
	if (death ==true && l>=2) {
		animationlife1.pop_back();
		figure.loadFromFile("img/shieldplane.png", screen);
		character.mBox.x = 0;
		character.mBox.y = 0;
		collision = false;
		timepoint = currenttime;
		death = false;
	}
	else if (death == true && l == 1) {
		figure.loadFromFile("img/planeexplosion.png", screen);
		playgame = false;
		secondplay = true;
		animationlife1.pop_back();
	}
	for (int i = 0; i < animationlife1.size(); i++) {
		lBox.x = animationlife1[i].x_pos;
		lBox.y = animationlife1[i].y_pos;
		SDL_RenderCopy(screen, mTextureLife, NULL, &lBox);
	}
	if (currenttime - timepoint ==2) {
		collision = true;
		figure.loadFromFile("img/plane.png", screen);
	}
}