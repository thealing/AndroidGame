#pragma once

#include "global.h"

#include "scene.h"

#include "engine/window.h"

#include "engine/sound.h"

void settings_init();

void settings_enter();

void settings_leave();

void settings_pause();

void settings_resume();

void settings_update(double delta_time);

void settings_render();