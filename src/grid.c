#include "grid.h"
#include "util.h"

#include <SFML/Graphics/Color.h>

#include <stdlib.h>

Grid* createNewGrid(int size)
{
	Grid* grid = malloc(sizeof(Grid));
	sfRectangleShape*** rectangles = malloc(size * sizeof(sfRectangleShape**));
	for (int i = 0; i < size; ++i)
	{
		rectangles[i] = malloc(size * sizeof(sfRectangleShape*));
	}

	initializeRectangleMatrix(rectangles, size);

	grid->m_rectangles = rectangles;
	grid->m_currentSize = size;
	grid->m_elapsedTime = sfTime_Zero;

	return grid;
}

void deleteGrid(Grid* grid)
{
	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		for (int j = 0; j < grid->m_currentSize; ++j)
		{
			sfRectangleShape_destroy(grid->m_rectangles[i][j]);
		}
	}

	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		free(grid->m_rectangles[i]);
	}
	free(grid->m_rectangles);

	free(grid);
	grid = NULL;
}

void updateGrid(Grid* grid, sfTime deltaTime)
{
	grid->m_elapsedTime.microseconds += deltaTime.microseconds;

	if (grid->m_elapsedTime.microseconds >= sfSeconds(1.0f).microseconds)
	{
		updateGridLogic(grid);
	}
}

void drawGrid(const Grid* grid, sfRenderWindow* window)
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

void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size)
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			sfRectangleShape* rectangle = sfRectangleShape_create();
			sfVector2f position = { row * 15 + 5, col * 15 + 5 };
			sfRectangleShape_setPosition(rectangle, position);
			sfVector2f sizes = { 10, 10 };
			sfRectangleShape_setSize(rectangle, sizes);
			sfRectangleShape_setFillColor(rectangle, sfWhite);
			rectangles[row][col] = rectangle;
		}
	}
}

void updateGridLogic(Grid* grid)
{
	// create new rectangle grid
	sfRectangleShape*** newRectangles = malloc(grid->m_currentSize * sizeof(sfRectangleShape**));
	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		newRectangles[i] = malloc(grid->m_currentSize* sizeof(sfRectangleShape*));
	}

	// check the game logic
	for (int row = 0; row < grid->m_currentSize; ++row)
	{
		for (int col = 0; col < grid->m_currentSize; ++col)
		{
			sfRectangleShape* cell = grid->m_rectangles[row][col];
			sfRectangleShape* newCell = newRectangles[row][col];
			if (isAlive(cell))
			{
				updateAliveCell(cell, newCell);
			}
			else
			{
				updateDeadCell(cell, newCell);
			}
		}
	}
}

void updateAliveCell(sfRectangleShape* old, sfRectangleShape* new)
{

}

void updateDeadCell(sfRectangleShape* old, sfRectangleShape* new)
{

}

bool isAlive(sfRectangleShape* cell)
{
	sfColor cellColor = sfRectangleShape_getFillColor(cell);
	return (colorsAreEqual(&cellColor, &sfWhite));
}
