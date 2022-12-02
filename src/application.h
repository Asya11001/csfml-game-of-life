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

void updateApp(Application* app, sfTime deltaTime);
void processInput(Application* app);
void render(Application* app);

Application createApplication(void);

#endif
