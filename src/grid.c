#include "grid.h"

#include <time.h>
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
	grid->m_blueColor = false;

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

void updateGrid(Grid* grid, sfTime deltaTime)
{
	grid->m_elapsedTime.microseconds += deltaTime.microseconds;

	if (grid->m_elapsedTime.microseconds >= sfSeconds(1.0f).microseconds)
	{
		grid->m_blueColor = !grid->m_blueColor;
		grid->m_elapsedTime = sfTime_Zero;
	}
}

void drawGrid(const Grid* grid, sfRenderWindow* window)
{
	int size = grid->m_currentSize;
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			if (grid->m_blueColor)
			{
				sfRectangleShape_setFillColor(grid->m_rectangles[row][col], sfBlue);
			}
			else
			{
				sfRectangleShape_setFillColor(grid->m_rectangles[row][col], sfWhite);
			}
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
			int coordinate = rand() % 31 + 5;
			sfVector2f position = { row * coordinate + 5, col * coordinate  + 5 };
			sfRectangleShape_setPosition(rectangle, position);
			sfVector2f sizes = { 10, 10 };
			sfRectangleShape_setSize(rectangle, sizes);
			sfRectangleShape_setFillColor(rectangle, sfWhite);
			rectangles[row][col] = rectangle;
		}
	}
}
