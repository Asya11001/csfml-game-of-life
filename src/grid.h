#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>

#include <stdbool.h>

typedef struct Grid
{
	sfRectangleShape*** m_cells;
	int m_currentSize;
	sfTime m_elapsedTime;
} Grid;

Grid* createNewGrid(int size);
void deleteGrid(Grid* grid);
void deleteGridCells(Grid* grid);

void updateGrid(Grid* grid, sfTime deltaTime);

void updateGridLogic(Grid* grid);
void updateAliveCell(Grid* grid, sfRectangleShape* new, int row, int col);
void updateDeadCell(Grid* grid, sfRectangleShape* new, int row, int col);

int getNumberOfAliveNeighbours(Grid* grid, int row, int col);
bool isAlive(sfRectangleShape* cell);

void drawGrid(const Grid* grid, sfRenderWindow* window);

void initializeCellMatrix(sfRectangleShape*** cells, int size);
sfRectangleShape*** allocateAndInitializeCells(int size);

// reset to the image that is displayed on first launch
void resetGridCellColors(sfRectangleShape*** cells, int size);

void makeGlider(sfRectangleShape* cell, int row, int col);

#endif
