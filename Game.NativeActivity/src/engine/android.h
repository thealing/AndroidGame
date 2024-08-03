#pragma once

#include <stdbool.h>

typedef enum Android_Event_Type Android_Event_Type;

typedef struct Android_Activity_Event Android_Activity_Event;

typedef struct Android_Window_Event Android_Window_Event;

typedef struct Android_Touch_Event Android_Touch_Event;

typedef struct Android_Event Android_Event;

typedef struct Android_Event_Node Android_Event_Node;

enum Android_Event_Type 
{
	ANDROID_EVENT_UNKNOWN,

	ANDROID_EVENT_RESUMED,

	ANDROID_EVENT_PAUSED,

	ANDROID_EVENT_WINDOW_CREATED,

	ANDROID_EVENT_WINDOW_DESTROYED,

	ANDROID_EVENT_TOUCH_DOWN,

	ANDROID_EVENT_TOUCH_UP,

	ANDROID_EVENT_TOUCH_MOVE,
};

struct Android_Window_Event
{
	void* window;
};

struct Android_Touch_Event
{
	int index;

	float x;

	float y;
};

struct Android_Event 
{
	Android_Event_Type type;

	union
	{
		Android_Window_Event window_event;

		Android_Touch_Event touch_event;
	};
};

struct Android_Event_Node
{
	Android_Event event;

	Android_Event_Node* next;
};

bool android_poll_event(Android_Event* event);

void android_main();
