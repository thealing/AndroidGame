#pragma once

#include <stdbool.h>

#define GROUP_LEVEL -1

#define GROUP_BLUE_CAR -2

#define GROUP_RED_CAR -3

#define FLAG_CAR 1

#define FLAG_CHASSIS 2

#define FLAG_HEAD 4

#define FLAG_WATER 8

#define FLAG_OBJECT 16

#define FLAG_MINE 32

#define FLAG_LIFTER 64

#define DEATH_DELAY 2

#define AIR_TIME_THRESHOLD 0.5

#define MINE_RANGE 250

#define MINE_EXPLOSION_DURATION 0.1

extern bool g_debug_hud;

extern bool g_same_random_car;

extern bool g_random_objects;

extern int g_sudden_death_time;

extern int g_sudden_death_countdown;

extern int g_max_score;

extern int g_selected_level;

extern int g_selected_blue_car;

extern int g_selected_red_car;

extern bool g_blue_is_bot;

extern bool g_red_is_bot;

void global_init();
