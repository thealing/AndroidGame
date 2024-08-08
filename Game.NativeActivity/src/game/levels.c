#include "levels.h"

static const Vector s_cave_bottom[] = {{74,365},{80,309},{93,262},{110,224},{129,192},{149,167},{180,138},{213,112},{254,90},{290,78},{330,66},{927,66},{962,73},{1003,83},{1038,97},{1074,119},{1103,142},{1128,167},{1150,193},{1170,227},{1186,261},{1195,294},{1203,332},{1204,364}};

static const Vector s_desert_bottom[] = {{76,383},{75,347},{80,311},{88,280},{100,246},{113,218},{142,195},{173,175},{200,160},{224,143},{248,131},{274,119},{308,108},{349,105},{398,104},{443,112},{482,120},{520,133},{562,145},{608,151},{672,151},{723,144},{765,132},{810,118},{855,109},{889,104},{933,105},{978,111},{1013,122},{1051,142},{1086,164},{1110,180},{1133,193},{1152,209},{1169,222},{1182,251},{1192,283},{1202,321},{1205,353},{1205,375}};

static const Vector s_cave_top[] = {{74,364},{78,405},{87,444},{100,483},{118,517},{138,547},{164,576},{193,600},{220,618},{255,636},{290,649},{323,655},{356,658},{936,658},{982,652},{1017,639},{1043,628},{1073,610},{1099,590},{1123,567},{1145,543},{1161,516},{1175,488},{1187,461},{1196,425},{1203,388},{1204,364}};

static const Vector s_center[] = {{297,280},{977,280},{993,294},{992,432},{980,442},{297,442},{283,430},{282,295}};

static const Vector s_desert_on_center[] = {{311,443},{347,474},{383,490},{429,491},{473,477},{501,468},{539,466},{583,474},{613,485},{654,484},{685,477},{722,469},{758,467},{792,472},{821,483},{848,490},{886,491},{916,480},{942,462},{964,445}};

static const Vector s_ramp_bottom[] = {{76,378},{76,347},{80,313},{88,279},{102,242},{118,211},{142,178},{169,149},{195,126},{219,109},{247,95},{277,83},{311,73},{379,73},{414,77},{443,85},{468,91},{492,101},{517,116},{540,132},{565,151},{592,179},{610,205},{628,236},{637,261},{648,239},{666,207},{687,178},{710,153},{737,131},{774,107},{812,91},{851,79},{893,73},{966,74},{1001,83},{1038,97},{1076,120},{1107,144},{1135,173},{1158,207},{1178,243},{1192,279},{1200,318},{1203,369},{1203,380}};

static const Vector s_gap_bottom[] = {{75,380},{76,350},{80,320},{85,289},{93,264},{106,234},{122,206},{141,178},{165,152},{187,131},{224,107},{260,89},{299,77},{310,75},{354,75},{400,80},{435,91},{466,105},{500,124},{530,147},{530,29},{740,29},{740,150},{764,130},{786,115},{810,102},{840,90},{875,80},{910,74},{964,73},{1000,83},{1030,94},{1059,110},{1090,132},{1116,155},{1141,184},{1164,215},{1178,245},{1190,275},{1198,310},{1202,348},{1203,381}};

static const Vector s_left_eye[] = {{104,526},{109,535},{119,540},{343,540},{360,544},{376,550},{390,561}};

static const Vector s_right_eye[] = {{890,561},{904,550},{920,544},{937,540},{1161,540},{1171,535},{1176,526}};

static const Vector s_smiley_top[] = {{123,277},{184,239},{238,209},{295,185},{375,164},{457,149},{533,140},{595,135},{649,135},{736,140},{809,146},{877,158},{947,175},{1013,198},{1069,224},{1157,277}};

static const Vector s_smiley_bottom[] = {{123,276},{153,222},{191,179},{231,147},{278,119},{325,97},{384,74},{451,57},{525,44},{616,36},{672,37},{756,42},{835,58},{925,85},{993,116},{1059,156},{1110,203},{1144,251},{1157,276}};

static const Vector s_frowny[] = {{122,41},{139,77},{167,113},{203,148},{243,178},{292,206},{329,223},{404,249},{472,266},{542,276},{639,282},{730,277},{817,264},{891,245},{962,219},{1020,188},{1064,159},{1110,116},{1138,80},{1157,40}};

static const Vector s_neutral[] = {{157,189},{171,202},{1110,201},{1123,188},{1122,130},{1110,119},{171,120},{158,130}};

static const Vector s_peg[][5] = {{{0,432},{64,497},{62,535},{0,475}},{{63,499},{211,498},{174,535},{62,535}},{{211,501},{211,1000},{174,1000},{175,535}},{{1280,432},{1216,497},{1218,535},{1280,475}},{{1217,499},{1069,498},{1106,535},{1218,535}},{{1069,501},{1069,1000},{1106,1000},{1105,535}}};

static const Vector s_bump[] = {{119,1},{120,167},{138,194},{169,214},{380,215},{438,230},{479,256},{507,293},{541,326},{578,345},{621,357},{660,357},{701,346},{743,324},{772,293},{796,260},{829,237},{865,221},{905,215},{1112,215},{1141,196},{1159,167},{1160,2}};

static const Vector s_double_bump[] = {{120,2},{121,167},{140,195},{173,214},{290,214},{342,227},{379,257},{403,285},{441,303},{488,305},{527,288},{553,263},{583,231},{614,218},{639,216},{641,216},{666,218},{697,231},{727,263},{753,288},{792,305},{839,303},{877,285},{901,257},{938,227},{990,214},{1107,214},{1140,195},{1159,167},{1160,2}};

static const Vector s_triple_bump[] = {{97,3},{98,162},{114,189},{140,207},{176,219},{204,239},{223,269},{256,292},{280,300},{306,300},{335,289},{356,272},{376,246},{391,228},{415,214},{438,208},{500,208},{525,216},{557,244},{572,268},{593,285},{618,296},{623,298},{628,299},{652,299},{657,298},{662,296},{687,285},{708,268},{723,244},{755,216},{780,208},{842,208},{865,214},{889,228},{904,246},{924,272},{945,289},{974,300},{1000,300},{1024,292},{1057,269},{1076,239},{1104,219},{1140,207},{1166,189},{1182,162},{1183,3}};

static void add_polygon(Level* level, int group, double friction, const Vector* polygon, int polygon_length)
{
	Shape* shape = shape_create_polygon(polygon_length, polygon);

	Physics_Collider* collider = physics_collider_create(level->body, move_shape(shape), 1);

	collider->static_friction = friction;

	collider->dynamic_friction = friction;

	collider->filter_group = group;
}

static void add_polygons(Level* level, int group, double friction, const Vector* polygons, int polygon_count, int polygon_length)
{
	for (int i = 0; i < polygon_count; i++)
	{
		int length = 0;

		while (polygons[i * polygon_length + length].x || polygons[i * polygon_length + length].y)
		{
			length++;
		}

		Shape* shape = shape_create_polygon(length, polygons + i * polygon_length);

		Physics_Collider* collider = physics_collider_create(level->body, move_shape(shape), 1);

		collider->static_friction = friction;

		collider->dynamic_friction = friction;

		collider->filter_group = group;
	}
}

static void add_ground(Level* level, int group, double friction, double y, const Vector* surface, int surface_length)
{
	for (int i = 0; i + 1 < surface_length; i++)
	{
		Vector a = surface[i];

		Vector b = surface[i + 1];

		Vector c = vector_create(i + 2 < surface_length ? b.x + fmin(10, fabs(b.y - y) * (surface[i + 2].x - b.x) / fabs(surface[i + 2].y - b.y)) : b.x, y);

		Vector d = vector_create(i - 1 >= 0 ? a.x - fmin(10, fabs(a.y - y) * (a.x - surface[i - 1].x) / fabs(a.y - surface[i - 1].y)) : a.x, y);

		Shape* shape = shape_create_polygon(4, (Vector[]){ a, b, c, d });

		Physics_Collider* collider = physics_collider_create(level->body, move_shape(shape), 1);

		collider->static_friction = friction;

		collider->dynamic_friction = friction;

		collider->filter_group = group;
	}
}

static void add_platform(Level* level, int group, double friction, const Vector* top, int top_length, const Vector* bottom, int bottom_length)
{
	for (int i = 0, j = 0, k = 0; i + 1 < top_length; i++)
	{
		Vector a = top[i];

		Vector b = top[i + 1];

		while (j + 1 < bottom_length && bottom[j + 1].x <= a.x)
		{
			j++;
		}

		while (k + 1 < bottom_length && bottom[k].x < b.x)
		{
			k++;
		}

		Vector c = bottom[k];

		Vector d = bottom[j];

		Shape* shape = shape_create_polygon(4, (Vector[]){ a, b, c, d });

		Physics_Collider* collider = physics_collider_create(level->body, move_shape(shape), 1);

		collider->static_friction = friction;

		collider->dynamic_friction = friction;

		collider->filter_group = group;
	}
}

static void add_laser(Level* level)
{
	level->laser_body = physics_body_create(level->body->world, PHYSICS_BODY_TYPE_KINEMATIC);

	Physics_Collider* collider = physics_collider_create(level->laser_body, move_shape(shape_create_segment(vector_create(-1000, 0), vector_create(1000, 0))), 1);

	collider->sensor = true;
}

static void add_water(Level* level)
{
	level->water_body = physics_body_create(level->body->world, PHYSICS_BODY_TYPE_KINEMATIC);

	level->water_body->position = vector_create(640, 80);

	Physics_Collider* collider = physics_collider_create(level->water_body, move_shape(create_rect_shape(vector_create(-1000, -1000), vector_create(1000, 0))), 1);

	collider->sensor = true;

	collider->flags |= FLAG_WATER;
}

Level* level_create(Level_Type type, Physics_World* world, int group)
{
	Level* level = calloc(1, sizeof(Level));

	level->body = physics_body_create(world, PHYSICS_BODY_TYPE_STATIC);

	switch (type)
	{
		case LEVEL_TYPE_CAVE:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.8, 0, s_cave_bottom, countof(s_cave_bottom));

			level->texture = g_textures.level_cave;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = random_int_in_range(ARMAGEDDON_TYPE_LASER_UP, ARMAGEDDON_TYPE_LASER_DOWN);

			break;
		}
		case LEVEL_TYPE_TUNNEL:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.8, 0, s_cave_bottom, countof(s_cave_bottom));

			add_polygon(level, group, 0.8, s_center, countof(s_center));

			level->texture = g_textures.level_tunnel;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = random_int_in_range(ARMAGEDDON_TYPE_LASER_UP, ARMAGEDDON_TYPE_LASER_DOWN);

			break;
		}
		case LEVEL_TYPE_DESERT_CAVE:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.4, 0, s_desert_bottom, countof(s_desert_bottom));

			level->texture = g_textures.level_desert_cave;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = random_int_in_range(ARMAGEDDON_TYPE_LASER_UP, ARMAGEDDON_TYPE_LASER_DOWN);

			break;
		}
		case LEVEL_TYPE_DESERT_TUNNEL:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.4, 0, s_desert_bottom, countof(s_desert_bottom));

			add_polygon(level, group, 0.8, s_center, countof(s_center));

			add_ground(level, group, 0.4, 360, s_desert_on_center, countof(s_desert_on_center));

			level->texture = g_textures.level_desert_tunnel;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = random_int_in_range(ARMAGEDDON_TYPE_LASER_UP, ARMAGEDDON_TYPE_LASER_DOWN);

			break;
		}
		case LEVEL_TYPE_RAMP:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.8, 0, s_ramp_bottom, countof(s_ramp_bottom));

			level->texture = g_textures.level_ramp;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = ARMAGEDDON_TYPE_LASER_UP;

			break;
		}
		case LEVEL_TYPE_GAP:
		{
			add_ground(level, group, 0.8, 720, s_cave_top, countof(s_cave_top));

			add_ground(level, group, 0.8, 0, s_gap_bottom, countof(s_gap_bottom));

			level->texture = g_textures.level_gap;

			level->blue_spawn = vector_create(300, 200);

			level->red_spawn = vector_create(980, 200);

			level->armageddon_type = ARMAGEDDON_TYPE_LASER_DOWN;

			break;
		}
		case LEVEL_TYPE_BUMP:
		{
			add_ground(level, group, 1.2, 0, s_bump, countof(s_bump));

			add_polygons(level, group, 0.5, s_peg, countof(s_peg), countof(s_peg[0]));

			add_water(level);

			level->texture = g_textures.level_bump;

			level->blue_spawn = vector_create(250, 330);

			level->red_spawn = vector_create(1030, 330);

			level->armageddon_type = ARMAGEDDON_TYPE_WATER_RISE;

			break;
		}
		case LEVEL_TYPE_DOUBLE_BUMP:
		{
			add_ground(level, group, 1.2, 0, s_double_bump, countof(s_double_bump));

			add_polygons(level, group, 0.5, s_peg, countof(s_peg), countof(s_peg[0]));

			add_water(level);

			level->texture = g_textures.level_double_bump;

			level->blue_spawn = vector_create(250, 330);

			level->red_spawn = vector_create(1030, 330);

			level->armageddon_type = ARMAGEDDON_TYPE_WATER_RISE;

			break;
		}
		case LEVEL_TYPE_TRIPLE_BUMP:
		{
			add_ground(level, group, 1.2, 0, s_triple_bump, countof(s_triple_bump));

			add_polygons(level, group, 0.5, s_peg, countof(s_peg), countof(s_peg[0]));

			add_water(level);

			level->texture = g_textures.level_triple_bump;

			level->blue_spawn = vector_create(440, 330);

			level->red_spawn = vector_create(840, 330);

			level->armageddon_type = ARMAGEDDON_TYPE_WATER_RISE;

			break;
		}
		case LEVEL_TYPE_SMILEY_FACE:
		{
			add_ground(level, group, 2, 452, s_left_eye, countof(s_left_eye));

			add_ground(level, group, 2, 452, s_right_eye, countof(s_right_eye));

			add_platform(level, group, 1, s_smiley_top, countof(s_smiley_top), s_smiley_bottom, countof(s_smiley_bottom));

			add_water(level);

			level->texture = g_textures.level_smiley_face;

			level->blue_spawn = vector_create(200, 650);

			level->red_spawn = vector_create(1080, 650);

			level->armageddon_type = ARMAGEDDON_TYPE_LASER_DOWN;

			break;
		}
		case LEVEL_TYPE_FROWNY_FACE:
		{
			add_ground(level, group, 2, 452, s_left_eye, countof(s_left_eye));

			add_ground(level, group, 2, 452, s_right_eye, countof(s_right_eye));

			add_polygon(level, group, 1, s_frowny, countof(s_frowny));

			add_water(level);

			level->texture = g_textures.level_frowny_face;

			level->blue_spawn = vector_create(200, 650);

			level->red_spawn = vector_create(1080, 650);

			level->armageddon_type = ARMAGEDDON_TYPE_LASER_DOWN;

			break;
		}
		case LEVEL_TYPE_NEUTRAL_FACE:
		{
			add_polygon(level, group, 1, s_neutral, countof(s_neutral));

			add_ground(level, group, 2, 452, s_left_eye, countof(s_left_eye));

			add_ground(level, group, 2, 452, s_right_eye, countof(s_right_eye));

			add_water(level);

			level->texture = g_textures.level_neutral_face;

			level->blue_spawn = vector_create(200, 650);

			level->red_spawn = vector_create(1080, 650);

			level->armageddon_type = ARMAGEDDON_TYPE_LASER_DOWN;

			break;
		}
	}

	return level;
}

void level_destroy(Level* level)
{
	physics_body_destroy(level->body);

	if (level->laser_body != NULL)
	{
		physics_body_destroy(level->laser_body);
	}

	if (level->water_body != NULL)
	{
		physics_body_destroy(level->water_body);
	}

	sound_stop(g_sounds.laser);

	sound_stop(g_sounds.water);

	free(level);
}

void level_update(Level* level, double delta_time)
{
	level->time += delta_time;
}

void level_render(Level* level)
{
	set_texture_and_color(level->texture, NULL);

	graphics_draw_texture_in_rect(&(Rect){ 0, 0, 1280, 720 });

	if (level->laser_body != NULL)
	{
		set_texture_and_color(g_textures.laser, &(Color){ 0.2, 0.8, 1, random_real() });

		graphics_draw_texture_at(level->laser_body->position, level->laser_body->angle);
	}

	if (level->water_body != NULL)
	{
		set_texture_and_color(g_textures.water, &(Color){ 1, 1, 1, 0.6 });

		double water_offset = level->time / 5;

		double water_level = level->water_body->position.y + 15;

		double water_height = 55;

		for (double y = water_level; y > 0; y -= water_height)
		{
			graphics_draw_texture_rect_in_rect(&(Rect){ water_offset, 0, 1 + water_offset, 1 }, &(Rect){ 0, y - water_height, 1280, y });

			water_offset *= 0.9;
		}
	}
}

void level_start_armageddon(Level* level)
{
	level->armageddon_active = true;

	switch (level->armageddon_type)
	{
		case ARMAGEDDON_TYPE_LASER_UP:
		{
			add_laser(level);

			level->laser_body->position = vector_create(640, 0);

			level->laser_body->linear_velocity = vector_create(0, 50);

			sound_play(g_sounds.laser);

			break;
		}
		case ARMAGEDDON_TYPE_LASER_DOWN:
		{
			add_laser(level);

			level->laser_body->position = vector_create(640, 720);

			level->laser_body->linear_velocity = vector_create(0, -50);

			sound_play(g_sounds.laser);

			break;
		}
		case ARMAGEDDON_TYPE_WATER_RISE:
		{
			level->water_body->linear_velocity = vector_create(0, 25);

			sound_play(g_sounds.water);

			break;
		}
	}
}

void level_stop_armageddon(Level* level)
{
	level->armageddon_active = false;

	if (level->laser_body != NULL)
	{
		level->laser_body->linear_velocity = vector_create(0, 0);
	}

	if (level->water_body != NULL)
	{
		level->water_body->linear_velocity = vector_create(0, 0);
	}

	sound_stop(g_sounds.laser);

	sound_stop(g_sounds.laser);
}
