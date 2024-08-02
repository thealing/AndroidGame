#include "assets.h"

Textures g_textures;

Sounds g_sounds;

static void create_blue_red_textures(Texture* textures[2], const char* path)
{
	Image* image = image_load(path);

	texture_create_from_image(&textures[0], image);

	for (int i = 0; i < image->height; i++)
	{
		for (int j = 0, k = image->width - 1; j <= k; j++, k--)
		{
			Pixel* left_pixel = &image->pixels[i * image->width + j];

			Pixel* right_pixel = &image->pixels[i * image->width + k];

			Pixel temp = *left_pixel;

			left_pixel->red = right_pixel->blue;

			left_pixel->green = right_pixel->green;

			left_pixel->blue = right_pixel->red;

			left_pixel->alpha = right_pixel->alpha;

			right_pixel->red = temp.blue;

			right_pixel->green = temp.green;

			right_pixel->blue = temp.red;

			right_pixel->alpha = temp.alpha;
		}
	}

	texture_create_from_image(&textures[1], image);

	image_destroy(image);
}

void textures_init()
{
	texture_create_from_file(&g_textures.font, "images/font.png");

	texture_create_from_file(&g_textures.laser, "images/laser.png");

	texture_resize(g_textures.laser, vector_create(1300, 4));

	texture_create_from_file(&g_textures.level_cave, "images/levels/cave.png");

	texture_create_from_file(&g_textures.level_tunnel, "images/levels/tunnel.png");

	texture_create_from_file(&g_textures.level_desert_cave, "images/levels/desert_cave.png");

	texture_create_from_file(&g_textures.level_desert_tunnel, "images/levels/desert_tunnel.png");

	texture_create_from_file(&g_textures.level_ramp, "images/levels/ramp.png");

	texture_create_from_file(&g_textures.level_gap, "images/levels/gap.png");

	texture_create_from_file(&g_textures.plank, "images/cars/plank.png");

	texture_create_from_file(&g_textures.garbage, "images/cars/garbage.png");

	create_blue_red_textures(g_textures.car_monster_truck, "images/cars/monster_truck.png");

	create_blue_red_textures(g_textures.car_dragster, "images/cars/dragster.png");

	create_blue_red_textures(g_textures.car_go_cart, "images/cars/go_cart.png");

	create_blue_red_textures(g_textures.car_minibus, "images/cars/minibus.png");

	create_blue_red_textures(g_textures.car_tractor, "images/cars/traktor.png");

	create_blue_red_textures(g_textures.car_timber_lorry, "images/cars/timber_lorry.png");

	create_blue_red_textures(g_textures.car_garbage_truck, "images/cars/garbage_truck.png");

	create_blue_red_textures(g_textures.wheel_tire, "images/wheels/tire.png");

	create_blue_red_textures(g_textures.wheel_small, "images/wheels/small.png");

	create_blue_red_textures(g_textures.wheel_cycle, "images/wheels/cycle.png");

	create_blue_red_textures(g_textures.wheel_monster, "images/wheels/monster.png");

	create_blue_red_textures(g_textures.head_neck, "images/head_neck.png");

	create_blue_red_textures(g_textures.head_only, "images/head_only.png");

	texture_resize(g_textures.head_neck[0], vector_create(32, 32));

	texture_resize(g_textures.head_neck[1], vector_create(32, 32));

	texture_resize(g_textures.head_only[0], vector_create(32, 32));

	texture_resize(g_textures.head_only[1], vector_create(32, 32));

	create_blue_red_textures(g_textures.timber_holder, "images/cars/timber_holder.png");

	create_blue_red_textures(g_textures.garbage_lid, "images/cars/garbage_lid.png");

	texture_create_from_file(&g_textures.overlay, "images/overlay.png");

	texture_create_from_file(&g_textures.ui_checked, "images/ui/checked.png");

	texture_create_from_file(&g_textures.ui_unchecked, "images/ui/unchecked.png");

	texture_create_from_file(&g_textures.ui_arrow_pressed, "images/ui/arrow_pressed.png");

	texture_create_from_file(&g_textures.ui_arrow_released, "images/ui/arrow_released.png");

	texture_create_from_file(&g_textures.ui_arrow_disabled, "images/ui/arrow_disabled.png");

	texture_create_from_file(&g_textures.ui_star_opaque, "images/ui/star_opaque.png");

	texture_create_from_file(&g_textures.ui_star_translucent, "images/ui/star_translucent.png");

	g_textures.ui_star_opaque->center.y = 56;

	g_textures.ui_star_translucent->center.y = 56;

	texture_resize(g_textures.ui_star_opaque, vector_create(50, 50));

	texture_resize(g_textures.ui_star_translucent, vector_create(50, 50));

	texture_create_from_file(&g_textures.ui_play_pressed, "images/ui/play_pressed.png");

	texture_create_from_file(&g_textures.ui_play_released, "images/ui/play_released.png");

	texture_create_from_file(&g_textures.ui_pause_pressed, "images/ui/pause_pressed.png");

	texture_create_from_file(&g_textures.ui_pause_released, "images/ui/pause_released.png");

	texture_create_from_file(&g_textures.ui_restart_pressed, "images/ui/restart_pressed.png");

	texture_create_from_file(&g_textures.ui_restart_released, "images/ui/restart_released.png");

	texture_create_from_file(&g_textures.ui_back_pressed, "images/ui/back_pressed.png");

	texture_create_from_file(&g_textures.ui_back_released, "images/ui/back_released.png");

	create_blue_red_textures(g_textures.ui_brake_pressed, "images/ui/left_pressed.png");

	create_blue_red_textures(g_textures.ui_brake_released, "images/ui/left_released.png");

	create_blue_red_textures(g_textures.ui_gas_pressed, "images/ui/right_pressed.png");

	create_blue_red_textures(g_textures.ui_gas_released, "images/ui/right_released.png");
}

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

	sound_set_volume(g_sounds.intro, 0.6);

	sound_set_volume(g_sounds.laser, 0.4);

	sound_set_volume(g_sounds.airhorn, 0.5);
}
