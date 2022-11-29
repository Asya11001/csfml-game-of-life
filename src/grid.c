#include "grid.h"

#include <stdlib.h>

Grid createGrid(int size)
{
	sfRectangleShape*** rectangles = malloc(size * sizeof(sfRectangleShape**));
	for (int i = 0; i < size; ++i)
	{
		rectangles[i] = malloc(size * sizeof(sfRectangleShape*));
	}

	initializeRectangleMatrix(rectangles, size);

	Grid grid = { rectangles, size };
	return grid;
}

void changeGridSize(Grid* grid, int newSize)
{
	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		free(grid->m_rectangles[i]);
		grid->m_rectangles[i] = NULL;
	}
	free(grid->m_rectangles);
	grid->m_rectangles = NULL;

	sfRectangleShape*** newRectangles = malloc(newSize * sizeof(sfRectangleShape**));
	for (int i = 0; i < newSize; ++i)
	{
		newRectangles[i] = malloc(newSize * sizeof(sfRectangleShape*));
	}

	initializeRectangleMatrix(newRectangles, newSize);
}

void updateGrid(Grid* grid)
{

}

static void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size)
{
	
}
