#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.h>

typedef struct Application
{
	sfRenderWindow* m_window;
} Application;

void run(Application* app);

static void update(Application* app);
static void processInput(Application* app);
static void render(Application* app);

Application createApplication(void);

#endif
