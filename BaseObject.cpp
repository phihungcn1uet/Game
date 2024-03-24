
#include "LibFile.h"


BaseObject::BaseObject() {
	mTexture = NULL;
	rect_ = { 0,0,0,0 };
}
 
BaseObject :: ~BaseObject() {
	free();
}

bool BaseObject :: loadFromFile(std::string path,SDL_Renderer *screen) {
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
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}


void BaseObject :: free() {
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		rect_.x = 0;
		rect_.y = 0;
	}
}

void BaseObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void BaseObject::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void BaseObject::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip,int x, int y) {

	SDL_Rect howrender = { x,y,rect_.w,rect_.h };
	SDL_RenderCopy(des, mTexture, clip, &howrender);
}