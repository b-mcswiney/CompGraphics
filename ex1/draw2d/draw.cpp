#include "draw.hpp"

#include <algorithm>
#include <iostream>

#include <cmath>

#include "color.hpp"
#include "surface.hpp"

void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{	

	// If the max is less than the min swap them
	if (aMaxCorner.x < aMinCorner.x)
	{
		std::swap(aMaxCorner.x, aMinCorner.x);
	}
	if (aMaxCorner.y < aMinCorner.y)
	{
		std::swap(aMaxCorner.y, aMinCorner.y);
	}

	// Draw every pixel within the spaces
	for (int y = aMinCorner.y; y < aMaxCorner.y; y++)
	{
		for (int x = aMinCorner.x; x < aMaxCorner.x; x++)
		{
			aSurface.set_pixel_srgb(x, y, aColor);
		}
	}
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	// If the max is less than the min swap them
	if (aMaxCorner.x < aMinCorner.x)
	{
		std::swap(aMaxCorner.x, aMinCorner.x);
	}
	if (aMaxCorner.y < aMinCorner.y)
	{
		std::swap(aMaxCorner.y, aMinCorner.y);
	}

	// Draw every pixel on the outline
	for (int y = aMinCorner.y; y <= aMaxCorner.y; y++)
	{
		for (int x = aMinCorner.x; x <= aMaxCorner.x; x++)
		{
			if(x == aMinCorner.x || x == aMaxCorner.x || y == aMinCorner.y || y == aMaxCorner.y)
			{
				aSurface.set_pixel_srgb(x, y, aColor);
			}
		}
	}
}
