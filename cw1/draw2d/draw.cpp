#include "draw.hpp"

#include <algorithm>

#include <iostream>

#include <cmath>

#include "surface.hpp"

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	// Calculate D vector
	float dX = aEnd.x - aBegin.x;
	float dY = aEnd.y - aBegin.y;

	// initialize step
	int step;

	//initialize current x and y values
	float currentY = aBegin.y;
	float currentX = aBegin.x;

	// Finding X major or Y Major
	if(abs(dX) > abs(dY)) {
		step = abs(dX);
	}
	else {
		step = abs(dY);
	}

	// Find step in each iteration
	float yInc = dY/step;
	float xInc = dX/step;

	// Set pixels in the line
	for(int i = 0; i < step; i++)
	{
		// Only draw what's within the surface
		if(currentX > 0 && currentX < aSurface.get_width()
			&& currentY > 0 && currentY < aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(currentX, currentY, aColor);
			}

		currentY += yInc;
		currentX += xInc;
	}
}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	// Draw three lines between the points of the triangle
	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP1, aP2, aColor);
	draw_line_solid(aSurface, aP2, aP0, aColor);
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	// Ensure vectors are in order of height so calculations function
	if(aP0.y > aP1.y)
	{
		std::swap(aP0, aP1);
	}
	if(aP0.y > aP2.y)
	{
		std::swap(aP2, aP0);
	}
	if(aP1.y > aP2.y)
	{
		std::swap(aP2, aP1);
	}

	// Initialize variables needed for drawing triangle
	float slopeRight;
	float slopeLeft;
	float currentStartX;
	float currentEndX;

	// We already have flat top
	if(aP0.y == aP1.y)
	{
		// Calculate slopes
		slopeLeft = (aP1.x - aP0.x) / (aP1.y - aP0.y);
		slopeRight = (aP2.x - aP0.x) / (aP2.y - aP0.y);

		// Initialise starting values
		currentStartX = aP0.x;
		currentEndX = aP0.x;

		// Fill flat bottom triangle
		for (int currentY = aP0.y; currentY <= aP1.y; currentY++)
		{
			draw_line_solid(aSurface, {currentStartX, (float)currentY}, {currentEndX, (float)currentY}, aColor);
			currentStartX += slopeLeft;
			currentEndX += slopeRight;
		}
	}
	// We have a flat bottom
	else if(aP1.y == aP2.y)
	{
		// find slope and currentX variables
		slopeLeft = (aP2.x - aP0.x) / (aP2.y - aP0.y);
		slopeRight = (aP2.x - aP1.x) / (aP2.y - aP1.y);

		// Fill flat top triangle
		currentStartX = aP2.x;
		currentEndX = aP2.x;

		for (int currentY = aP2.y; currentY >= aP1.y; currentY--)
		{
			draw_line_solid(aSurface, {currentStartX, (float)currentY}, {currentEndX, (float)currentY}, aColor);
			currentStartX -= slopeLeft;
			currentEndX -= slopeRight;
		}
	}
	// We have neither a flat top or bottom
	else
	{
		//Find mid point where we can split triangle into 2
		float midX = aP0.x + ((aP1.y - aP0.y) / (aP2.y - aP0.y)) * (aP2.x - aP0.x);

		Vec2f aP3 = {midX, aP1.y};

		// Calculate slopes
		slopeLeft = (aP1.x - aP0.x) / (aP1.y - aP0.y);
		slopeRight = (aP3.x - aP0.x) / (aP3.y - aP0.y);

		// Initialise starting values
		currentStartX = aP0.x;
		currentEndX = aP0.x;

		// Fill flat bottom triangle
		for (int currentY = aP0.y; currentY <= aP1.y; currentY++)
		{
			draw_line_solid(aSurface, {currentStartX, (float)currentY}, {currentEndX, (float)currentY}, aColor);
			currentStartX += slopeLeft;
			currentEndX += slopeRight;
		}

		// Reuse slope and current variables for bottom triangle
		slopeLeft = (aP2.x - aP1.x) / (aP2.y - aP1.y);
		slopeRight = (aP2.x - aP3.x) / (aP2.y - aP3.y);

		// Fill flat top triangle
		currentStartX = aP2.x;
		currentEndX = aP2.x;

		for (int currentY = aP2.y; currentY >= aP1.y; currentY--)
		{
			draw_line_solid(aSurface, {currentStartX, (float)currentY}, {currentEndX, (float)currentY}, aColor);
			currentStartX -= slopeLeft;
			currentEndX -= slopeRight;
		}

	}
}

void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: Remove the following when you start your implementation!
	//TODO: This draws a solid triangle until you implement the function
	//TODO: properly. (This is such that you can see the asteroids with solid
	//TODO: shading until that point.)
	draw_triangle_solid( aSurface, aP0, aP1, aP2, linear_to_srgb( aC0 ) );
	(void)aC1;
	(void)aC2;
}


void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
