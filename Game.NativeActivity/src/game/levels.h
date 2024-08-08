#pragma once

#include "textures.h"

#include "sounds.h"

#include "util.h"

#include "global.h"

#include "engine/random.h"

#include "engine/time.h"

typedef enum Level_Type Level_Type;

typedef enum Armageddon_Type Armageddon_Type;

typedef struct Level Level;

enum Level_Type
{
	LEVEL_TYPE_CAVE,

	LEVEL_TYPE_TUNNEL,

	LEVEL_TYPE_DESERT_CAVE,

	LEVEL_TYPE_DESERT_TUNNEL,

	LEVEL_TYPE_RAMP,

	LEVEL_TYPE_GAP,

	LEVEL_TYPE_BUMP,

	LEVEL_TYPE_DOUBLE_BUMP,

	LEVEL_TYPE_TRIPLE_BUMP,

	LEVEL_TYPE_SMILEY_FACE,

	LEVEL_TYPE_FROWNY_FACE,

	LEVEL_TYPE_NEUTRAL_FACE,

	LEVEL_TYPE_COUNT
};

enum Armageddon_Type
{
	ARMAGEDDON_TYPE_LASER_UP,

	ARMAGEDDON_TYPE_LASER_DOWN,

	ARMAGEDDON_TYPE_WATER_RISE,

	ARMAGEDDON_TYPE_COUNT
};

struct Level
{
	Physics_Body* body;

	Texture* texture;

	Vector blue_spawn;

	Vector red_spawn;

	double time;

	Armageddon_Type armageddon_type;

	bool armageddon_active;

	Physics_Body* laser_body;

	Physics_Body* water_body;
};

Level* level_create(Level_Type type, Physics_World* world, int group);

void level_destroy(Level* level);

void level_update(Level* level, double delta_time);

void level_render(Level* level);

void level_start_armageddon(Level* level);

void level_stop_armageddon(Level* level);