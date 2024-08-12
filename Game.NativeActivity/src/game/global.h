#pragma once

#include "save.h"

#include <stdbool.h>

#define DEATH_DELAY 2

#define AIR_TIME_THRESHOLD 0.5

#define MINE_RANGE 250

#define MINE_EXPLOSION_DURATION 0.1

#define BOOSTER_STRENGTH 35

enum
{
	GROUP_LEVEL = -1,

	GROUP_BLUE_CAR = -2,

	GROUP_RED_CAR = -3,
};

enum
{
	FLAG_CAR = (1 << 0),

	FLAG_CHASSIS = (1 << 1),

	FLAG_WHEEL = (1 << 2),

	FLAG_HEAD = (1 << 3),

	FLAG_WATER = (1 << 4),

	FLAG_OBJECT = (1 << 5),

	FLAG_TOUCHED = (1 << 6),

	FLAG_MINE = (1 << 7),

	FLAG_SAFE = (1 << 8),
};

extern bool g_debug_hud;

extern int g_sudden_death_countdown;

extern int g_max_score;

extern int g_selected_level;

extern int g_selected_blue_car;

extern int g_selected_red_car;

extern bool g_blue_is_bot;

extern bool g_red_is_bot;

void global_init();
