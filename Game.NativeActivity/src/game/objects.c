#include "objects.h"

static const Vector s_mine[] = {{-23,-10},{-9,8},{9,8},{23,-10}};

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

static Physics_Body* create_body(Physics_World* world, Vector position, const Vector* hitbox, int hitbox_length, Physics_Collision_Callback callback, void* data, int flag)
{
	Physics_Body* body = physics_body_create(world, PHYSICS_BODY_TYPE_DYNAMIC);

	body->position = position;

	Shape* shape = shape_create_polygon(hitbox_length, hitbox);

	Physics_Collider* collider = physics_collider_create(body, move_shape(shape), 5);

	collider->static_friction = 1;

	collider->dynamic_friction = 1;

	collider->collision_callback = callback;

	collider->data = data;

	collider->flags |= flag;

	return body;
}

Object* object_create(Object_Type type, Physics_World* world, Vector position)
{
	switch (type)
	{
		case OBJECT_TYPE_MINE:
		{
			Mine* mine = calloc(1, sizeof(Mine));

			mine->type = OBJECT_TYPE_MINE;

			mine->body = create_body(world, position, s_mine, countof(s_mine), mine_collision_callback, mine, FLAG_MINE);

			return mine;
		}
	}
}

void object_destroy(Object* object)
{
	switch (object->type)
	{
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
		case OBJECT_TYPE_MINE:
		{
			Mine* mine = object;

			if (mine->state == 1)
			{
				if (mine->count_time / 0.35 >= mine->counter)
				{
					sound_play(g_sounds.beep);

					mine->counter++;
				}

				if (mine->counter >= 6)
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
						Vector vector = vector_subtract(collider->body->position, mine->body->position);

						double distance = vector_length(vector);

						double impulse = 100000 / square(distance);

						// apply impulse to closest point

						//physics_body_apply_impulse_at_world_point(collider->body, mine->body->position, )

						collider->body->linear_velocity = vector_add(collider->body->linear_velocity, vector_multiply(vector, impulse / distance));
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
				if (fmod(mine->count_time, 0.35) < 0.1)
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

				set_texture_and_color(NULL, &(Color){ 1, 0, 0, 0.5 + progress });

				graphics_draw_circle(&(Circle){ mine->body->position, square(progress) * 150 }, true);
			}

			break;
		}
	}
}
