#include "LibFile.h"

GameMap::GameMap() {
	mTexture = NULL;
	 MapHeight=0;
	 MapWidth=0;
}
GameMap :: ~GameMap() {

}


void GameMap::loadFileMap(std::string name) 
{
	std::ifstream in;
	in.open(name);
	if (!in.is_open()) {
		std::cout << "Can't load file" << std::endl;
	}
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			in >> numcheck[i][j];
		}

	}
	in.close();
}


bool GameMap::loadFromFile(std::string path, SDL_Renderer* screen) {
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
			MapWidth = loadedSurface->w;
			MapHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void GameMap::DrawMap(SDL_Renderer* screen) {
	std::string dot = ".png";
	std::string head = "img/";
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			if (numcheck[i][j] != 0) {
				int val = numcheck[i][j];
				std::string file_img;
				file_img = head+std::to_string(val) + dot;
				loadFromFile(file_img, screen);
				SDL_Rect a = { 64 * j,64 * i,64,64 };
				SDL_RenderCopy(screen, mTexture, NULL, &a);
			}
		}
	}
}

