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

void drawGrid(Grid* grid, sfRenderWindow* window)
{
	int size = grid->m_currentSize;
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			sfRenderWindow_drawRectangleShape(window, grid->m_rectangles[row][col], NULL);
		}
	}
}

static void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size)
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			sfRectangleShape* rectangle = sfRectangleShape_create();
			sfVector2f position = { row * 15 + 5, col * 15 + 5 };
			sfRectangleShape_setPosition(rectangle, position);
			sfVector2f size = { 10, 10 };
			sfRectangleShape_setSize(rectangle, size);
			sfRectangleShape_setFillColor(rectangle, sfWhite);
			rectangles[row][col] = rectangle;
		}
	}
}
