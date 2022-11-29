#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>

typedef struct Grid
{
	sfRectangleShape*** m_grid;
	int m_currentSize;
} Grid;

void createGrid(int size);

void changeGridSize(Grid* grid, int newSize);
void updateGrid(Grid* grid);

#endif
