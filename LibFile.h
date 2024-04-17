#pragma once
#ifndef LIB_FILE_H_
#define LIB_FILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include "BaseObject.h"
#include "Figure.h"
#include "enemy.h"
#include"time.h"
#include"Rocket.h"
#include "Boom.h"
#include"Special.h"
#include"Life.h"
#include"Menu.h"
#include"TextObject.h"

//Screen dimension constants
const int FRAME_PER_SECOND = 60;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT =640;

static int toadoX = 0;
static int toadoY = 0;

static const int FIGURE_WIDTH = 64;
static const int FIGURE_HEIGHT = 64;

static Mix_Chunk* soundnormalbullet;
static Mix_Chunk* soundrocket;
#endif // !LIB_FILE_H
