#include "util.h"

Vector create_isotropic_vector(double value)
{
	return vector_create(value, value);
}

Shape* create_rect_shape(Vector min, Vector max)
{
	return shape_create_polygon(4, (Vector[]){ { min.x, min.y }, { max.x, min.y }, { max.x, max.y }, { min.x, max.y } });
}

Shape* move_shape(Shape* shape)
{
	static Shape* old_shape;

	if (old_shape != NULL)
	{
		shape_destroy(old_shape);
	}

	old_shape = shape;

	return shape;
}

void set_texture_and_color(const Texture* texture, const Color* color)
{
	graphics_set_texture(texture);

	if (color == NULL)
	{
		graphics_set_color(&(Color){ 1, 1, 1, 1 });
	}
	else
	{
		graphics_set_color(color);
	}
}

void draw_physics_world(const Physics_World* world)
{
	set_texture_and_color(NULL, &(Color){ 0, 1, 0, 1 });

	for (const List_Node* body_node = world->body_list.first; body_node != NULL; body_node = body_node->next)
	{
		const Physics_Body* body = body_node->item;

		draw_physics_body(body);
	}

	set_texture_and_color(NULL, &(Color){ 0, 0, 1, 1 });

	for (const List_Node* joint_node = world->joint_list.first; joint_node != NULL; joint_node = joint_node->next)
	{
		const Physics_Joint* joint = joint_node->item;

		draw_physics_joint(joint);
	}
}

void draw_physics_body(const Physics_Body* body)
{
	graphics_save_transform();

	graphics_translate(body->position);

	graphics_rotate(body->angle);

	for (const List_Node* collider_node = body->collider_list.first; collider_node != NULL; collider_node = collider_node->next)
	{
		const Physics_Collider* collider = collider_node->item;

		graphics_draw_shape(collider->local_shape, false);
	}

	graphics_load_transform();
}

void draw_physics_joint(const Physics_Joint* joint)
{
	graphics_draw_segment(&(Segment){ joint->world_anchor_1, joint->world_anchor_2 }, false);
}

void lerp_colors(Color* result, const Color* a, const Color* b, double t) 
{
	result->red = (1 - t) * a->red + t * b->red;

	result->green = (1 - t) * a->green + t * b->green;

	result->blue = (1 - t) * a->blue + t * b->blue;

	result->alpha = (1 - t) * a->alpha + t * b->alpha;
}
