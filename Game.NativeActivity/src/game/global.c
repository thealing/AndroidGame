#include "global.h"

bool g_debug_hud;

bool g_random_objects;

bool g_same_random_car;

int g_sudden_death_time;

int g_sudden_death_countdown;

int g_max_score;

int g_selected_level;

int g_selected_blue_car;

int g_selected_red_car;

bool g_blue_is_bot;

bool g_red_is_bot;

void global_init()
{
	g_debug_hud = false;

	g_random_objects = true;

	g_same_random_car = false;

	g_sudden_death_time = 12;

	g_sudden_death_countdown = 3;

	g_max_score = 5;

	g_selected_level = 10;

	g_selected_blue_car = 1;

	g_selected_red_car = 1;

	g_blue_is_bot = false;

	g_red_is_bot = true;
}
