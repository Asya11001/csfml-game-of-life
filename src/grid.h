#ifndef GRID_STRUCTURE_H
#define GRID_STRUCTURE_H

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>

#include <stdbool.h>

typedef struct Grid
{
	sfRectangleShape*** m_rectangles;
	int m_currentSize;
	sfTime m_elapsedTime;
} Grid;

Grid* createNewGrid(int size);
void deleteGrid(Grid* grid);

void updateGrid(Grid* grid, sfTime deltaTime);
void updateGridLogic(Grid* grid);
void updateAliveCell(sfRectangleShape* old, sfRectangleShape* new);
void updateDeadCell(sfRectangleShape* old, sfRectangleShape* new);
bool isAlive(sfRectangleShape* cell);

void drawGrid(const Grid* grid, sfRenderWindow* window);

void initializeRectangleMatrix(sfRectangleShape*** rectangles, int size);

#endif
