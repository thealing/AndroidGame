#include "main.h"

void android_main()
{
	log_info("Game started!");

	double width = 1;

	double height = 1;

	double last_time = get_time();

	int frame_count = 0;

	int frames_per_second = 0;

	Texture* font = NULL;

	while (true) 
	{
		Android_Event e;

		while (android_poll_event(&e))
		{
			switch (e.type)
			{
				case ANDROID_EVENT_RESUMED:
				{
					log_warning("Activity resumed!");

					break;
				}
				case ANDROID_EVENT_PAUSED:
				{
					log_warning("Activity paused!");

					break;
				}
				case ANDROID_EVENT_WINDOW_CREATED:
				{
					width = window_get_width(e.window_event.window);

					height = window_get_height(e.window_event.window);

					graphics_init(e.window_event.window);

					texture_create_from_file(&font, "font.png");

					graphics_set_font(font);

					graphics_set_camera(&(Rect){ 0, 0, 1280, 720 });

					log_warning("Window created!");

					break;
				}
				case ANDROID_EVENT_WINDOW_DESTROYED:
				{
					graphics_uninit(e.window_event.window);

					log_warning("Window destroyed!");

					break;
				}
			}
		}

		frame_count++;

		double current_time = get_time();

		if (current_time > last_time + 1)
		{
			last_time = current_time;

			frames_per_second = frame_count;

			frame_count = 0;

			log_info("A second passed!");
		}

		graphics_clear(&(Color){ fabs(fmod(current_time, 2) - 1), 0, 0, 1 });

		graphics_draw_format_in_rect(&(Rect){ 10, 10, 0, 50 }, ALIGNMENT_LEFT, "FPS: %d", lround(frames_per_second));

		graphics_display();
	}
}
