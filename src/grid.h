#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>

typedef struct Grid
{
	sfRectangleShape*** m_rectangles;
	int m_currentSize;
} Grid;

Grid createGrid(int size);

void changeGridSize(Grid* grid, int newSize);

void updateGrid(Grid* grid);
void drawGrid(Grid* grid, sfRenderWindow* window);

static void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size);

#endif
