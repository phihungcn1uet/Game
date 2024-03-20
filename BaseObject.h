#pragma once
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "LibFile.h"
class BaseObject {
public:
	BaseObject();
	~BaseObject();
	bool loadFromFile(std::string path,SDL_Renderer *screen);
	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	void render(SDL_Renderer* des, const SDL_Rect* clip,int x,int y);


private:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
};



#endif // !BASE_OBJECT_H_
