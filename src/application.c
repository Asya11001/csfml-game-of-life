#include "application.h"
#include "grid.h"

#include <SFML/Window/Event.h>
#include <SFML/System/Clock.h>

#include <stdio.h>

Application createApplication(void)
{
	sfVideoMode mode = { 800, 600, 32 };
	sfRenderWindow* window = sfRenderWindow_create(mode, "game", sfDefaultStyle, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);

	Grid* grid = createNewGrid(20);

	Context context = createContext(window, grid);
	StateStack stateStack = createStateStack(context);

	Application app = { window, stateStack };
	pushStateToStack(&app.m_stateStack, title);
	return app;
}

void run(Application* app)
{
	sfClock* clock = sfClock_create();
	while (sfRenderWindow_isOpen(app->m_window))
	{
		processInput(app);
		updateApp(app, sfClock_restart(clock));

		if (isStateStackEmpty(&app->m_stateStack))
		{
			sfRenderWindow_close(app->m_window);
		}

		render(app);
	}

	sfClock_destroy(clock);
	sfRenderWindow_destroy(app->m_window);
}

void updateApp(Application* app, sfTime deltaTime)
{
	updateStateStack(&app->m_stateStack, deltaTime);
}

void processInput(Application* app)
{
	sfEvent event;
	while (sfRenderWindow_pollEvent(app->m_window, &event))
	{
		handleStateStackEvent(&app->m_stateStack, &event);

		if (event.type == sfEvtClosed)
			sfRenderWindow_close(app->m_window);
	}
}

void render(Application* app)
{
	sfRenderWindow_clear(app->m_window, sfBlack);

	drawStateStack(&app->m_stateStack);

	sfRenderWindow_display(app->m_window);
}
