#include "application.h"

Application createApplication(void)
{
	sfVideoMode mode = { 800, 600 };
	sfRenderWindow* window = sfRenderWindow_create(mode, "game", sfDefaultStyle, NULL);

	Application app;
	app.m_window = window;

	return app;
}

void run(Application* app)
{
	while (sfRenderWindow_isOpen(app->m_window))
	{
		processInput(app);
		update(app);
		render(app);
	}
}

static void update(Application* app)
{
	/* ... */
}

static void processInput(Application* app)
{
	sfEvent event;
	while (sfRenderWindow_pollEvent(app->m_window, &event))
	{
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(app->m_window);

		if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
			sfRenderWindow_close(app->m_window);
	}
}

static void render(Application* app)
{
	sfRenderWindow_clear(app->m_window, sfBlack);

	/* ... */

	sfRenderWindow_display(app->m_window);
}
