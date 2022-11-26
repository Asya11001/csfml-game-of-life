#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.h>

typedef struct Application
{
	sfRenderWindow* m_window;
} Application;

void run(Application* app);

void update(Application* app);
void processInput(Application* app);
void render(Application* app);

Application createApplication();

#endif
