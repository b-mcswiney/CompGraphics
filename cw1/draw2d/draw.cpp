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

float half_line_test(Vec2f Q, Vec2f P, Vec2f X)
{	
	Vec2f D = {Q.x - P.x, Q.y - P.y};
	Vec2f N = {D.y * -1, D.x};

	return (N.x * (X.x - P.x)) + (N.y * (X.y - P.y));
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
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
		if(points[i].x < minY) {minY = points[i].y;}
	}
	
	// Vec2f P = {0, 3};
	// Vec2f Q = {5, 0};
	// Vec2f R = {6, 4};
	// Vec2f S = {1, 1};

	// std::cout << "half line test result 1 " << half_line_test(Q, P, R) << std::endl;
	// std::cout << "half line test result 2 " << half_line_test(Q, P, S) << std::endl;

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
			if(x > 0 && (float)x < aSurface.get_width()
				&& y > 0 && (float)y < aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(x, y, aColor);
			}

		}
	}
	// for(int j = minY; j <= maxY; j++)
	// {
	// 	for(int i = minX; i <= maxX; i++)
	// 	{
	// 		//Equation is F(x) = n * (X-P)
			
	// 		// aP0 to aP1 test
	// 		float dx = aP0.x - aP1.x;
	// 		float dy = aP0.y - aP1.y;
	// 		float nx = -1 * dy;
	// 		float ny = dx;

	// 		if( (nx * (i - aP0.x) + (ny * (j - aP0.y))) > 0)
	// 		{
	// 			continue;
	// 		}


	// 		// aP1 to aP2 test
	// 		dx = aP1.x - aP2.x;
	// 		dy = aP1.y - aP2.y;
	// 		nx = -1 * dy;
	// 		ny = dx;

	// 		if( (nx * (i - aP1.x) + (ny * (j - aP1.y))) > 0)
	// 		{
	// 			continue;
	// 		}

	// 		// aP2 to aP0 test
	// 		dx = aP2.x - aP0.x;
	// 		dy = aP2.y - aP0.y;
	// 		nx = -1 * dy;
	// 		ny = dx;

	// 		if( (nx * (i - aP0.x) + (ny * (j - aP0.y))) > 0)
	// 		{
	// 			continue;
	// 		}


			// // Only draw what's within the surface
			// if(i > 0 && (float)i < aSurface.get_width()
			// 	&& j > 0 && (float)j < aSurface.get_height()) 
			// {
			// 	aSurface.set_pixel_srgb(i, j, aColor);
			// }
	// 	}
	// }
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
	// float maxX = aP0.x;
	// float maxY = aP0.x;
	// float minX = aP0.x;
	// float minY = aP0.x;

	// // Put points into list so we can iterate through them
	// std::vector<Vec2f> points = {aP0, aP1, aP2};

	// // Find max and minimum bounds of triangle
	// for(int i = 0; i < 3; i++)
	// {
	// 	std::cout << "point numb " << i << ": " << points[i].x << " , " << points[i].y << std::endl;
	// 	if(points[i].x > maxX) {maxX = points[i].x;}
	// 	if(points[i].y > maxY) {maxY = points[i].y;}
	// 	if(points[i].x < minX) {minX = points[i].x;}
	// 	if(points[i].x < minY) {minY = points[i].y;}
	// }

	// std::cout << "max = " << maxX << " , " << maxY << std::endl;
	// std::cout << "min = " << minX << " , " << minY << std::endl;

	// // Find area of whole triangle
	// float totalArea = find_triangle_area(aP0, aP1, aP2);	

	// for(int y = minY; y <= maxY; y++)
	// {
	// 	for(int x = minX; x <= maxX; x++)
	// 	{
	// 		// // Stop calculations if point is outside bounds
	// 		// if(x < 0 || (float)x > aSurface.get_width() || y < 0 || (float)y > aSurface.get_height())
	// 		// {
	// 		// 	continue;
	// 		// }

	// 		// Vec2f currentPoint = {(float)x, (float)y};

	// 		// // Alpha calculation
	// 		// float alpha = find_triangle_area(aP1, aP2, currentPoint) / totalArea;

	// 		// if(alpha > 1 || alpha < 0)
	// 		// {
	// 		// 	continue;
	// 		// }

	// 		// // Beta calculation
	// 		// float beta = find_triangle_area(aP0, currentPoint, aP2) / totalArea;


	// 		// if(beta > 1 || beta < 0)
	// 		// {
	// 		// 	continue;
	// 		// }

	// 		// // Gamma calculation
	// 		// float gamma = find_triangle_area(aP0, aP1, currentPoint) / totalArea;


	// 		// if(gamma > 1 || gamma < 0)
	// 		// {
	// 		// 	continue;
	// 		// }

	// 		// if((alpha + beta + gamma) == 1)
	// 		// {
	// 		// 	// Only draw what's within the surface
	// 		// 	if(x > 0 && (float)x < aSurface.get_width()
	// 		// 		&& y > 0 && (float)y < aSurface.get_height()) 
	// 		// 	{
	// 		// 		aSurface.set_pixel_srgb(x, y, linear_to_srgb( aC0 ));
	// 		// 	}
	// 		// }

	// 		// Only draw what's within the surface
	// 		// if(x > 0 && (float)x < aSurface.get_width()
	// 		// 	&& y > 0 && (float)y < aSurface.get_height()) 
	// 		// {
	// 		// 	aSurface.set_pixel_srgb(x, y, linear_to_srgb( aC0 ));
	// 		// }
	// 	}
	// }

	// //TODO: Remove the following when you start your implementation!
	// //TODO: This draws a solid triangle until you implement the function
	// //TODO: properly. (This is such that you can see the asteroids with solid
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
