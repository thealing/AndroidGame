#pragma once

#include <stdbool.h>

#include <math.h>

typedef struct Sound Sound;

Sound* sound_load(const char* path);

void sound_destroy(Sound* sound);

bool sound_is_looping(Sound* sound);

void sound_set_looping(Sound* sound, bool looping);

void sound_play(Sound* sound);

void sound_stop(Sound* sound);

void sound_pause(Sound* sound);

void sound_resume(Sound* sound);

double sound_get_volume(Sound* sound);

void sound_set_volume(Sound* sound, double volume);

double sound_get_position(Sound* sound);

void sound_set_position(Sound* sound, double position);
