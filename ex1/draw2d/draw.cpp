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
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	// If the max is less than the min swap them
	if (aMaxCorner.x < aMinCorner.x)
	{
		std::swap(aMaxCorner.x, aMinCorner.x);
	}
	if (aMaxCorner.y < aMinCorner.y)
	{
		std::swap(aMaxCorner.y, aMinCorner.y);
	}


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

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
