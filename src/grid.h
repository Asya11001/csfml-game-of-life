#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>

typedef struct Grid
{
	sfRectangleShape*** m_rectangles;
	int m_currentSize;
} Grid;

Grid createGrid(int size);

void changeGridSize(Grid* grid, int newSize);
void updateGrid(Grid* grid);

static void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size);

#endif
