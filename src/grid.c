#include "grid.h"
#include "util.h"

#include <SFML/Graphics/Color.h>

#include <stdlib.h>
#include <stdio.h>

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
		grid->m_elapsedTime.microseconds = 0;
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
			// column is x, row is y
			sfVector2f position = { col * 15 + 5, row * 15 + 5 };
			sfRectangleShape_setPosition(rectangle, position);
			sfVector2f sizes = { 10, 10 };
			sfRectangleShape_setSize(rectangle, sizes);
			if (row == 0 && col == 1 || row == 1 && col == 2 || row == 2 && col == 0 ||
				row == 2 && col == 1 || row == 2 && col == 2)
			{
				sfRectangleShape_setFillColor(rectangle, sfWhite);
			}
			else
			{
				sfRectangleShape_setFillColor(rectangle, sfGreen);
			}
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
		newRectangles[i] = malloc(grid->m_currentSize * sizeof(sfRectangleShape*));
	}

	initializeRectangleMatrix(newRectangles, grid->m_currentSize);

	// check the game logic
	for (int row = 0; row < grid->m_currentSize; ++row)
	{
		for (int col = 0; col < grid->m_currentSize; ++col)
		{
			sfRectangleShape* cell = grid->m_rectangles[row][col];
			sfRectangleShape* newCell = newRectangles[row][col];
			if (isAlive(cell))
			{
				updateAliveCell(grid->m_rectangles, newCell, row, col);
			}
			else
			{
				updateDeadCell(grid->m_rectangles, newCell, row, col);
			}
		}
	}

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

	grid->m_rectangles = newRectangles;
}

void updateAliveCell(sfRectangleShape*** oldCells, sfRectangleShape* new, int row, int col)
{
	int numberOfAliveNeighbours = getNumberOfAliveNeighbours(oldCells, row, col);
	if (numberOfAliveNeighbours == 2 || numberOfAliveNeighbours == 3)
	{
		sfRectangleShape_setFillColor(new, sfWhite);
	}
	else
	{
		sfRectangleShape_setFillColor(new, sfGreen);
	}
}

void updateDeadCell(sfRectangleShape*** oldCells, sfRectangleShape* new, int row, int col)
{
	if (getNumberOfAliveNeighbours(oldCells, row, col) == 3)
	{
		sfRectangleShape_setFillColor(new, sfWhite);
	}
	else
	{
		sfRectangleShape_setFillColor(new, sfGreen);
	}
}

int getNumberOfAliveNeighbours(sfRectangleShape*** oldCells, int row, int col)
{
	int numberOfAliveNeighbours = 0;
	// 8 possible neighbour indices:
	int rowOffset[] = { 1, 0, 1, -1, 0, -1, -1, 1 };
	int colOffset[] = { 0, 1, 1, 0, -1, -1, 1, -1 };
	for (int i = 0; i < 8; ++i)
	{
		int neighbourRowIndex = row + rowOffset[i];
		int neighbourColIndex = col + colOffset[i];
		// if it's a corner type cell it will have either 5 or 3 neighbours
		if (neighbourRowIndex < 0 || neighbourRowIndex > 10 - 1 ||
			neighbourColIndex < 0 || neighbourColIndex > 10 - 1)
		{
			continue;
		}

		if (isAlive(oldCells[neighbourRowIndex][neighbourColIndex]))
		{
			++numberOfAliveNeighbours;
		}
	}

	return numberOfAliveNeighbours;
}

bool isAlive(sfRectangleShape* cell)
{
	sfColor cellColor = sfRectangleShape_getFillColor(cell);
	return (colorsAreEqual(&cellColor, &sfWhite));
}
