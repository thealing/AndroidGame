#pragma once

#include "util.h"

#include "global.h"

#include "sounds.h"

#include "cars.h"

typedef enum Object_Type Object_Type;

typedef struct Object Object;

typedef struct Saw Saw;

typedef struct Mine Mine;

enum Object_Type
{
	OBJECT_TYPE_SAW,

	OBJECT_TYPE_MINE,

	OBJECT_TYPE_COUNT
};

struct Object
{
	Object_Type type;
};

struct Saw
{
	Object_Type type;

	Physics_Body* body;

	double radius;
};

struct Mine
{
	Object_Type type;

	Physics_Body* body;

	int state;

	double count_time;

	int counter;
};

Object* object_create_saw(Physics_World* world, Vector position, double radius, bool reversed);

Object* object_create_mine(Physics_World* world, Vector position);

void object_destroy(Object* object);

void object_update(Object* object, double delta_time);

void object_render(Object* object);
