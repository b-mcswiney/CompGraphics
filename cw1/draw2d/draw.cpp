#include "draw.hpp"

#include <algorithm>

#include <iostream>

#include <cmath>

#include "surface.hpp"

float half_line_test(Vec2f Q, Vec2f P, Vec2f X);

float find_area_triangle(Vec2f A, Vec2f B, Vec2f C);

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	// Calculate D vector
	float dX = aEnd.x - aBegin.x;
	float dY = aEnd.y - aBegin.y;

	// initialize length
	int length;

	//initialize current x and y values
	float currentY = aBegin.y;
	float currentX = aBegin.x;

	// Finding X major or Y Major
	// Absolute value ensures we never divide by 0
	if(abs(dX) > abs(dY)) {
		length = abs(dX);
	}
	else {
		length = abs(dY);
	}

	// Find step in each iteration
	float yInc = dY/length;
	float xInc = dX/length;

	// Set pixels in the line
	for(int i = 0; i < length; i++)
	{
		// Only draw what's within the surface
		if(currentX >= 0 && currentX < aSurface.get_width()
			&& currentY >= 0 && currentY < aSurface.get_height()) 
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

float half_line_test(Vec2f Q, Vec2f P, Vec2f X)
{	
	Vec2f D = {Q.x - P.x, Q.y - P.y};
	Vec2f N = {D.y * -1, D.x};

	return (N.x * (X.x - P.x)) + (N.y * (X.y - P.y));
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	// Set default max/min points for comparison
	float maxX = aP0.x;
	float maxY = aP0.x;
	float minX = aP0.x;
	float minY = aP0.x;

	// Put points into list so we can iterate through them
	std::vector<Vec2f> points = {aP0, aP1, aP2};

	// Find max and minimum bounds of triangle
	for(int i = 0; i < 3; i++)
	{
		if(points[i].x < minX) {minX = points[i].x;}
		if(points[i].y < minY) {minY = points[i].y;}
		if(points[i].x > maxX) {maxX = points[i].x;}
		if(points[i].y > maxY) {maxY = points[i].y;}
	}

	for(int y = minY; y <= maxY; y++)
	{
		for(int x = minX; x <= maxX; x++)
		{
			// Get current point into Vec2f form
			Vec2f currentP = {(float)x, (float)y};

			// Half line test for aP0 to AP1
			if(half_line_test(aP0, aP1, currentP) > 0)
			{
				continue;
			}

			// Half line test for aP1 to AP2
			if(half_line_test(aP1, aP2, currentP) > 0)
			{
				continue;
			}

			// Half line test for aP2 to AP0
			if(half_line_test(aP2, aP0, currentP) > 0)
			{
				continue;
			}


			// Only draw what's within the surface
			if(x >= 0 && (float)x < aSurface.get_width()
				&& y >= 0 && (float)y < aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(x, y, aColor);
			}

		}
	}
}


float find_triangle_area(Vec2f A, Vec2f B, Vec2f C)
{
	// Calculate area of triangle (used a lot with barycentric coords)
	float vX = C.x - A.x;
	float vY = C.y - A.y;
	float uX = B.x - A.x;
	float uY = B.y - A.y;

	return ((uX * vY) - (uY* vX)) / 2;
}


void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	float maxX = aP0.x;
	float maxY = aP0.x;
	float minX = aP0.x;
	float minY = aP0.x;

	// Put points into list so we can iterate through them
	std::vector<Vec2f> points = {aP0, aP1, aP2};

	// Find max and minimum bounds of triangle
	for(int i = 0; i < 3; i++)
	{
		if(points[i].x > maxX) {maxX = points[i].x;}
		if(points[i].y > maxY) {maxY = points[i].y;}
		if(points[i].x < minX) {minX = points[i].x;}
		if(points[i].y < minY) {minY = points[i].y;}
	}

	// Find area of whole triangle
	float totalArea = find_triangle_area(aP0, aP1, aP2);	

	for(int y = minY; y <= maxY; y++)
	{
		for(int x = minX; x <= maxX; x++)
		{
			// Stop calculations if point is outside bounds
			if(x < 0 || (float)x > aSurface.get_width() || y < 0 || (float)y > aSurface.get_height())
			{
				continue;
			}

			Vec2f currentPoint = {(float)x, (float)y};

			// Alpha calculation
			float alpha = find_triangle_area(aP1, aP2, currentPoint) / totalArea;

			if(alpha > 1 || alpha < 0)
			{
				continue;
			}

			// Beta calculation
			float beta = find_triangle_area(aP0, currentPoint, aP2) / totalArea;


			if(beta > 1 || beta < 0)
			{
				continue;
			}

			// Gamma calculation
			float gamma = find_triangle_area(aP0, aP1, currentPoint) / totalArea;


			if(gamma > 1 || gamma < 0)
			{
				continue;
			}

			// Only draw what's within the surface
			if(x >= 0 && (float)x < aSurface.get_width()
				&& y >= 0 && (float)y < aSurface.get_height()) 
			{
				float red = aC0.r * alpha + aC1.r * beta + aC2.r * gamma;
				float green = aC0.g * alpha + aC1.g * beta + aC2.g * gamma;
				float blue = aC0.b * alpha + aC1.b * beta + aC2.b * gamma;

				ColorF colourInterpol = {red, green, blue};

				aSurface.set_pixel_srgb(x, y, linear_to_srgb( colourInterpol ));
			}
		}
	}
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
