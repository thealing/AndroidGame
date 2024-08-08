#pragma once

#include "util.h"

#include "global.h"

typedef enum Object_Type Object_Type;

typedef struct Object Object;

typedef struct Mine Mine;

enum Object_Type
{
	OBJECT_TYPE_MINE,

	OBJECT_TYPE_COUNT
};

struct Object
{
	Object_Type type;
};

struct Mine
{
	Object_Type type;

	Physics_Body* body;

	int state;

	double count_time;

	int counter;
};

Object* object_create(Object_Type type, Physics_World* world, Vector position);

void object_destroy(Object* object);

void object_update(Object* object, double delta_time);

void object_render(Object* object);
