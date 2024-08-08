#include "objects.h"

static const Vector s_mine[] = {{-23,-10},{-9,8},{9,8},{23,-10}};

static bool saw_collision_callback(Physics_Collider* mine_collider, Physics_Collider* other_collider)
{
	if (other_collider->flags & FLAG_HEAD)
	{
		Car* car = other_collider->data;

		return !car->done;
	}

	return false;
}

static bool mine_collision_callback(Physics_Collider* mine_collider, Physics_Collider* other_collider)
{
	if (other_collider->flags & FLAG_CAR)
	{
		Mine* mine = mine_collider->data;

		if (mine->state == 0)
		{
			mine->state = 1;

			mine->count_time = 0;
		}
	}

	return true;
}

Object* object_create_saw(Physics_World* world, Vector position, double radius, bool reversed)
{
	Saw* saw = calloc(1, sizeof(Saw));

	saw->type = OBJECT_TYPE_SAW;

	saw->body = physics_body_create(world, PHYSICS_BODY_TYPE_KINEMATIC);

	saw->body->position = position;

	saw->body->angular_velocity = reversed ? -3 : 3;

	Shape* shape = shape_create_circle(vector_create(0, 0), radius);

	Physics_Collider* collider = physics_collider_create(saw->body, move_shape(shape), 1);

	collider->collision_callback = saw_collision_callback;

	saw->radius = radius;

	return saw;
}

Object* object_create_mine(Physics_World* world, Vector position)
{
	Mine* mine = calloc(1, sizeof(Mine));

	mine->type = OBJECT_TYPE_MINE;

	mine->body = physics_body_create(world, PHYSICS_BODY_TYPE_DYNAMIC);

	mine->body->position = position;

	Shape* shape = shape_create_polygon(countof(s_mine), s_mine);

	Physics_Collider* collider = physics_collider_create(mine->body, move_shape(shape), 5);

	collider->static_friction = 1;

	collider->dynamic_friction = 1;

	collider->collision_callback = mine_collision_callback;

	collider->data = mine;

	collider->flags |= FLAG_MINE;

	return mine;
}

void object_destroy(Object* object)
{
	switch (object->type)
	{
		case OBJECT_TYPE_SAW:
		{
			Saw* saw = object;

			physics_body_destroy(saw->body);

			break;
		}
		case OBJECT_TYPE_MINE:
		{
			Mine* mine = object;

			physics_body_destroy(mine->body);

			sound_stop(g_sounds.beep);

			sound_stop(g_sounds.explosion);

			break;
		}
	}

	free(object);
}

void object_update(Object* object, double delta_time)
{
	switch (object->type)
	{
		case OBJECT_TYPE_SAW:
		{
			break;
		}
		case OBJECT_TYPE_MINE:
		{
			Mine* mine = object;

			if (mine->state == 1)
			{
				if (mine->count_time / 0.3 >= mine->counter)
				{
					sound_play(g_sounds.beep);

					mine->counter++;
				}

				if (mine->counter >= 4)
				{
					mine->state = 2;

					mine->count_time = 0;

					sound_stop(g_sounds.beep);

					sound_play(g_sounds.explosion);
				}
			}

			if (mine->state == 2)
			{
				Physics_World* world = mine->body->world;

				for (List_Node* collider_node = world->collider_list.first; collider_node != NULL; collider_node = collider_node->next)
				{
					Physics_Collider* collider = collider_node->item;

					if (collider->body != mine->body)
					{
						Vector target = shape_project_point(collider->world_shape, mine->body->position);

						Vector vector = vector_subtract(target, mine->body->position);

						double distance = vector_length(vector);

						if (distance < 250)
						{
							double impulse = 1e6 / distance;

							physics_body_apply_impulse_at_world_point(collider->body, target, vector_multiply(vector, impulse / distance));
						}
					}
				}

				if (mine->count_time > 0.1)
				{
					mine->state = 3;

					mine->body->position = vector_create(10000, 10000);
				}
			}

			mine->count_time += delta_time;

			break;
		}
	}
}

void object_render(Object* object)
{
	switch (object->type)
	{
		case OBJECT_TYPE_SAW:
		{
			Saw* saw = object;

			set_texture_and_color(saw->body->angular_velocity > 0 ? g_textures.saw_left : g_textures.saw_right, NULL);

			draw_texture_scaled(saw->body->position, saw->body->angle, saw->radius);

			break;
		}
		case OBJECT_TYPE_MINE:
		{
			Mine* mine = object;

			if (mine->state == 0)
			{
				set_texture_and_color(g_textures.mine_0, NULL);

				graphics_draw_texture_at(mine->body->position, mine->body->angle);
			}

			if (mine->state == 1)
			{
				if (fmod(mine->count_time, 0.3) < 0.1)
				{
					set_texture_and_color(g_textures.mine_1, NULL);
				}
				else
				{
					set_texture_and_color(g_textures.mine_2, NULL);
				}

				graphics_draw_texture_at(mine->body->position, mine->body->angle);
			}

			if (mine->state == 2)
			{
				double progress = mine->count_time / 0.1;

				set_texture_and_color(NULL, &(Color){ 1, 0, 0, 1.2 - progress });

				graphics_draw_circle(&(Circle){ mine->body->position, square(progress) * 200 }, true);
			}

			break;
		}
	}
}
