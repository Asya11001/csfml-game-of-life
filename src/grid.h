#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>

typedef struct Grid
{
	sfRectangleShape*** m_rectangles;
	int m_currentSize;
} Grid;

Grid* createNewGrid(int size);

void changeGridSize(Grid* grid, int newSize);

void updateGrid(Grid* grid, sfTime deltaTime);
void drawGrid(const Grid* grid, sfRenderWindow* window);

static void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size);

#endif
