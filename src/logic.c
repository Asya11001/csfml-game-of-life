#include "logic.h"

void update_grid(sfRectangleShape*** grid, int size)
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			// if the cell is dead
			if (colorsAreEqual(sfRectangleShape_getFillColor(grid[row][col]), sfBlack))
			{
				/* ... */
			}
			else
			{
				/* ... */
			}
		}
	}
}
