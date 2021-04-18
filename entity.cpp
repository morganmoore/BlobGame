#include "entity.h"
#include <cmath>

Vec2 Entity::getPos()
{
	return pos;
}

int Entity::getRadius()
{
	return radius;
}


void Entity::updateSize(int consumedRadius)
{
	float newArea = (3.14 * pow(radius, 2)) + (3.14 * pow(consumedRadius, 2));
	radius = sqrt(newArea / 3.14);
}
