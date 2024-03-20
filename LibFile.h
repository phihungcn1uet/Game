#pragma once
#ifndef LIB_FILE_H_
#define LIB_FILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "BaseObject.h"
#include "Figure.h"
#include "Map.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;



#endif // !LIB_FILE_H
