#include <SFML/Graphics.h>
#include <stdlib.h>
#include "logic.h"

int main(void)
{
	sfVideoMode mode = { 800, 600 };
	sfRenderWindow* window = sfRenderWindow_create(mode, "window", sfDefaultStyle, NULL);

	sfRectangleShape*** grid = calloc(5, sizeof(sfRectangleShape**));
	for (int i = 0; i < 5; ++i)
	{
		grid[i] = calloc(5, sizeof(sfRectangleShape*));
	}

	// need to be initialized to avoid seg faults
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			sfRectangleShape* rectangle = sfRectangleShape_create();
			grid[i][j] = rectangle;
		}
	}

	update_grid(grid, 5);

	while (sfRenderWindow_isOpen(window))
	{
		sfEvent event;
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);

			if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
		}

		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_display(window);
	}

	return 0;
}
