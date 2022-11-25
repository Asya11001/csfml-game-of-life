#include "util.h"

bool colorsAreEqual(const sfColor* first, const sfColor* second)
{
	return (first->r == second->r && first->g == second->g && first->b == second->b);
}
