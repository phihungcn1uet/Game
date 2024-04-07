#pragma once
#ifndef LIB_FILE_H_
#define LIB_FILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include "BaseObject.h"
#include "Figure.h"
#include "enemy.h"
//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT =640;

static int toadoX = 0;
static int toadoY = 0;

static const int FIGURE_WIDTH = 64;
static const int FIGURE_HEIGHT = 64;

#endif // !LIB_FILE_H
