#include "LibFile.h"

Figure :: Figure() {
	character.velocityX = 0;
	character.velocityY = 0;
	x_pos = 0;
	y_pos = 0;
	mTexture = NULL;
	character.mBox = { 0,0,FIGURE_WIDTH,FIGURE_HEIGHT };
	status = -1;

	std::ifstream in;
	in.open("map/newmap.txt");
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
	//std::cout << x_pos << "-" << y_pos << "-" << character.mBox.w << "-" << character.mBox.h << std::endl;
	character.mBox.x = x_pos;
	character.mBox.y = y_pos;
	SDL_RenderCopy(screen, mTexture, NULL, &character.mBox);
}


bool Figure::checkCollision(SDL_Rect rectA, SDL_Rect rectB) {
	int leftA = rectA.x;
	int rightA = rectA.x + rectA.w;
	int topA = rectA.y;
	int bottomA = rectA.y + rectA.h;

	int leftB = rectB.x;
	int rightB = rectB.x + rectB.w;
	int topB = rectB.y;
	int bottomB = rectB.y + rectB.h;

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
		return false;
	}
	else {
		return true;
	}
}

void Figure::checkarround() {
	int x_font = (x_pos + 64)/64;
	int y_font = y_pos/64;
	int x_back = (x_pos - 64)/64;
	int y_back = y_pos/64;
	int x_above = x_pos/64;
	int y_above = (y_pos - 64) / 64;
	if (numcheck[y_font][x_font] != 0) {
		SDL_Rect wall;
		wall.x = x_font * 64;
		wall.y = y_font * 64;
		wall.w = MAP_SIZE;
		wall.h = MAP_SIZE;
		ColliisonWall(wall);
    }

	if (numcheck[y_back][x_back] != 0) {
		SDL_Rect wall;
		wall.x = x_back * 64;
		wall.y = y_back * 64;
		wall.w = MAP_SIZE;
		wall.h = MAP_SIZE;
		ColliisonWall(wall);
	}
	if (numcheck[y_above][x_above] != 0) {
		SDL_Rect wall;
		wall.x = x_above * 64;
		wall.y = y_above * 64;
		wall.w = MAP_SIZE;
		wall.h = MAP_SIZE;
		ColliisonWall(wall);
	}
}


void Figure::ColliisonWall(SDL_Rect& wall)
{
	//Move the dot left or right
	x_pos += character.velocityX;
	character.mBox.x = x_pos;

	/*if (checkCollision(character.mBox, wall) == true) {
		std::cout << "co va cham" << std::endl;
	}*/
	//If the dot collided or went too far to the left or right
	if ((x_pos < 0) || (x_pos + FIGURE_WIDTH > SCREEN_WIDTH) || checkCollision(character.mBox, wall))
	{
		if (status == 4) {
			//Move back
			//x_pos += character.velocityX;
			//character.velocityX = 0;
			x_pos = wall.x - FIGURE_WIDTH-6;
		}
		else if (status == 3) {
			//Move back
			//x_pos += character.velocityX;
			//character.velocityX = 0;
			x_pos = wall.x + wall.w+6;
		}
		
	}

	//Move the dot up or down
	y_pos += character.velocityY;
	character.mBox.y = y_pos;

	//If the dot collided or went too far up or down
	if ((y_pos < 0) || (y_pos + FIGURE_HEIGHT > SCREEN_HEIGHT) || checkCollision(character.mBox, wall))
	{
		if (status == 2) {
			//Move back
			//y_pos -= character.velocityY;
			//character.mBox.y = y_pos;
			y_pos = wall.y - FIGURE_HEIGHT;
		}
		else if (status == 1) {
			//Move back
			//y_pos -= character.velocityY;
			//character.mBox.y = y_pos;
			y_pos = wall.y + wall.h;
		}
		
	}
}


void Figure::Gravity() {
	y_pos += 1;
	int x1 = x_pos / 64;
	int x2 = x1 + 1;
	int y1 = (y_pos + 64) / 64;
	SDL_Rect a = { 64 * x1,64 * y1,64,64 };
	if (numcheck[y1][x1] != 0 && checkCollision(character.mBox,a)==true ){
		y_pos = a.y- FIGURE_HEIGHT;
	}
	if (numcheck[y1][x2] != 0 && checkCollision(character.mBox, a) == true) {
		y_pos = a.y - FIGURE_HEIGHT;
	}
}


void Figure::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (x_pos + FIGURE_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (y_pos + FIGURE_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > SCREEN_WIDTH - camera.w)
	{
		camera.x = SCREEN_WIDTH - camera.w;
	}
	if (camera.y > SCREEN_HEIGHT - camera.h)
	{
		camera.y = SCREEN_HEIGHT - camera.h;
	}
}




void Figure::handleEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: character.velocityY -= FIGURE_VEL; status = 1; break;
		case SDLK_DOWN: character.velocityY += FIGURE_VEL; status = 2; break;
		case SDLK_LEFT: character.velocityX -= FIGURE_VEL; status = 3; break;
		case SDLK_RIGHT: character.velocityX += FIGURE_VEL; status = 4; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: character.velocityY += FIGURE_VEL; break;
		case SDLK_DOWN: character.velocityY -= FIGURE_VEL; break;
		case SDLK_LEFT: character.velocityX += FIGURE_VEL; break;
		case SDLK_RIGHT: character.velocityX -= FIGURE_VEL; break;
		}
	}
}