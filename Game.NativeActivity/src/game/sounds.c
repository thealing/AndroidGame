#include "sounds.h"

Sounds g_sounds;

void sounds_init()
{
	g_sounds.intro = sound_load("sounds/intro.mp2");

	g_sounds.music = sound_load("sounds/music.mp3");

	g_sounds.airhorn = sound_load("sounds/airhorn.mp3");

	g_sounds.applause = sound_load("sounds/applause.mp3");

	g_sounds.blip = sound_load("sounds/blip.mp3");

	g_sounds.click = sound_load("sounds/click.mp3");

	g_sounds.click2 = sound_load("sounds/click2.mp3");

	g_sounds.laser = sound_load("sounds/laser.mp2");

	g_sounds.water = sound_load("sounds/water.mp2");

	g_sounds.beep = sound_load("sounds/beep.mp3");

	g_sounds.explosion = sound_load("sounds/explosion.mp3");

	sound_set_volume(g_sounds.intro, 0.6);

	sound_set_volume(g_sounds.airhorn, 0.4);

	sound_set_looping(g_sounds.intro, true);

	sound_set_looping(g_sounds.music, true);

	sound_set_looping(g_sounds.laser, true);

	sound_set_looping(g_sounds.water, true);
}

void sounds_pause_all()
{
	for (int i = 0; i < sizeof(g_sounds) / sizeof(Sound*); i++)
	{
		Sound* sound = ((Sound**)&g_sounds)[i];

		sound_pause(sound);
	}
}

void sounds_resume_all()
{
	for (int i = 0; i < sizeof(g_sounds) / sizeof(Sound*); i++)
	{
		Sound* sound = ((Sound**)&g_sounds)[i];

		sound_resume(sound);
	}
}

void sounds_stop_all()
{
	for (int i = 0; i < sizeof(g_sounds) / sizeof(Sound*); i++)
	{
		Sound* sound = ((Sound**)&g_sounds)[i];

		sound_stop(sound);
	}
}
