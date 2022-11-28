#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.h>

#include "states/state_stack.h"

typedef struct Application
{
	sfRenderWindow* m_window;
	StateStack m_stateStack;
} Application;

void run(Application* app);

static void updateApp(Application* app, sfTime deltaTime);
static void processInput(Application* app);
static void render(Application* app);

Application createApplication(void);

#endif
