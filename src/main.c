#include <SFML/Graphics.h>

int main()
{
	sfVideoMode mode = { 200, 200 };
	sfRenderWindow* window = sfRenderWindow_create(mode, "window", sfDefaultStyle, NULL);
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfGreen);

	while (sfRenderWindow_isOpen(window))
	{
		sfEvent event;
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_drawCircleShape(window, circle, NULL);
		sfRenderWindow_display(window);
	}

	return 0;
}
