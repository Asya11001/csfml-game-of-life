#include "grid.h"
#include "util.h"

#include <SFML/Graphics/Color.h>

#include <stdlib.h>
#include <stdio.h>

Grid* createNewGrid(int size)
{
	Grid* grid = malloc(sizeof(Grid));
	sfRectangleShape*** cells = allocateAndInitializeCells(size);

	grid->m_cells = cells;
	grid->m_currentSize = size;
	grid->m_elapsedTime = sfTime_Zero;

	return grid;
}

void deleteGrid(Grid* grid)
{
	deleteGridCells(grid);

	free(grid);
	grid = NULL;
}

void deleteGridCells(Grid* grid)
{
	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		for (int j = 0; j < grid->m_currentSize; ++j)
		{
			sfRectangleShape_destroy(grid->m_cells[i][j]);
		}
	}

	for (int i = 0; i < grid->m_currentSize; ++i)
	{
		free(grid->m_cells[i]);
	}
	free(grid->m_cells);
}

void updateGrid(Grid* grid, sfTime deltaTime)
{
	grid->m_elapsedTime.microseconds += deltaTime.microseconds;

	if (grid->m_elapsedTime.microseconds >= sfSeconds(0.5f).microseconds)
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
			sfRenderWindow_drawRectangleShape(window, grid->m_cells[row][col], NULL);
		}
	}
}

void initializeCellMatrix(sfRectangleShape*** cells, int size)
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			sfRectangleShape* cell = sfRectangleShape_create();
			// column is x, row is y
			sfVector2f position = { (float)col * 15 + 5, (float)row * 15 + 5 };
			sfRectangleShape_setPosition(cell, position);
			sfVector2f sizes = { 10, 10 };
			sfRectangleShape_setSize(cell, sizes);
			if ((row == 0 && col == 1) || (row == 1 && col == 2) || (row == 2 && col == 0) ||
				(row == 2 && col == 1) || (row == 2 && col == 2))
			{
				sfRectangleShape_setFillColor(cell, sfWhite);
			}
			else
			{
				sfRectangleShape_setFillColor(cell, sfGreen);
			}
			cells[row][col] = cell;
		}
	}
}

void resetGridCellColors(sfRectangleShape*** cells, int size)
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			sfRectangleShape* cell = cells[row][col];
			if ((row == 0 && col == 1) || (row == 1 && col == 2) || (row == 2 && col == 0) ||
				(row == 2 && col == 1) || (row == 2 && col == 2))
			{
				sfRectangleShape_setFillColor(cell, sfWhite);
			}
			else
			{
				sfRectangleShape_setFillColor(cell, sfGreen);
			}
		}
	}
}

sfRectangleShape*** allocateAndInitializeCells(int size)
{
	sfRectangleShape*** cells = malloc((long unsigned int)size * sizeof(sfRectangleShape**));
	for (int i = 0; i < size; ++i)
	{
		cells[i] = malloc((long unsigned int)size * sizeof(sfRectangleShape*));
	}

	initializeCellMatrix(cells, size);

	return cells;
}

void updateGridLogic(Grid* grid)
{
	// create new rectangle grid
	sfRectangleShape*** newCells = allocateAndInitializeCells(grid->m_currentSize);

	// check the game logic
	for (int row = 0; row < grid->m_currentSize; ++row)
	{
		for (int col = 0; col < grid->m_currentSize; ++col)
		{
			sfRectangleShape* cell = grid->m_cells[row][col];
			sfRectangleShape* newCell = newCells[row][col];
			if (isAlive(cell))
			{
				updateAliveCell(grid, newCell, row, col);
			}
			else
			{
				updateDeadCell(grid, newCell, row, col);
			}
		}
	}

	// free the old grid
	deleteGridCells(grid);

	// assign the new one
	grid->m_cells = newCells;
}

void updateAliveCell(Grid* grid, sfRectangleShape* new, int row, int col)
{
	int numberOfAliveNeighbours = getNumberOfAliveNeighbours(grid, row, col);
	if (numberOfAliveNeighbours == 2 || numberOfAliveNeighbours == 3)
	{
		sfRectangleShape_setFillColor(new, sfWhite);
	}
	else
	{
		sfRectangleShape_setFillColor(new, sfGreen);
	}
}

void updateDeadCell(Grid* grid, sfRectangleShape* new, int row, int col)
{
	if (getNumberOfAliveNeighbours(grid, row, col) == 3)
	{
		sfRectangleShape_setFillColor(new, sfWhite);
	}
	else
	{
		sfRectangleShape_setFillColor(new, sfGreen);
	}
}

int getNumberOfAliveNeighbours(Grid* grid, int row, int col)
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
		if (neighbourRowIndex < 0 || neighbourRowIndex > grid->m_currentSize - 1 ||
			neighbourColIndex < 0 || neighbourColIndex > grid->m_currentSize - 1)
		{
			continue;
		}

		if (isAlive(grid->m_cells[neighbourRowIndex][neighbourColIndex]))
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
