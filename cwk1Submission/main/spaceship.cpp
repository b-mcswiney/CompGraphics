#include "spaceship.hpp"

#include <cstdio>

#include "../draw2d/shape.hpp"

/* Instructions - CUSTOM SPACESHIP DESIGNS
 *
 *  0. If you are OK with your space ship design being included in future
 *     computer graphics exercises and/or courseworks, please indicate this by
 *     placing a 'X' in the space between the [ ] on the following line:
 *     [X] I give permission for my space ship shape to be used in future
 *         computer graphics exercises and/or courseworks.
 *
 *     If you do not wish for your shape to be used, leave the line as is.
 *     Your decision will not affect the marking of Task 2.7 in CW1.
 *
 *     If you wish to be credited (name + year when you took the computer
 *     graphics mdoule) in a CREDITS.txt or similar file with future exercises
 *     and/or courseworks, please indicate this by ticking the following box
 *     [X] I wish to have my name + year listed with assignments that use my
 *         space ship shape.
 *
 *     If you do not wish to be credited, leave the [ ] empty.
 *
 *     Many thanks if you do permit the use of your cool space ship designs! It
 *     will help us to make future computer graphics exercises and courseworks
 *     more interesting.
 *
 *  1. Change the line
 *     #	define SPACESHIP SPACESHIP_DEFAULT
 *     to
 *     #	define SPACESHIP SPACESHIP_CUSTOM
 *
 *  2. Define your custom space ship design in the now active code section.
 *     (Look for the line that says '// TODO: YOUR DESIGN GOES HERE')
 */

#define SPACESHIP_DEFAULT 1
#define SPACESHIP_CUSTOM 2

#ifndef SPACESHIP
#	define SPACESHIP SPACESHIP_CUSTOM
#endif

LineStrip make_spaceship_shape()
{
#	if SPACESHIP == SPACESHIP_DEFAULT
	static constexpr float xs[] = { 250.f, 200.f, 150.f, 100.f, 000.f, 040.f, -50.f, -140.f, -170.f };
	static constexpr float ys[] = { 190.f, 180.f, 70.f, 50.f, 30.f, 20.f };

	LineStrip spaceship{ { 
		{ 0.2f * xs[0], 0.2f * +ys[5] }, // upper half. starts at front, goes towards the back
		{ 0.2f * xs[1], 0.2f * +ys[3] },
		{ 0.2f * xs[2], 0.2f * +ys[3] },
		{ 0.2f * xs[3], 0.2f * +ys[4] }, 
		{ 0.2f * xs[4], 0.2f * +ys[4] },
		{ 0.2f * xs[4], 0.2f * +ys[2] },
		{ 0.2f * xs[5], 0.2f * +ys[1] },
		{ 0.2f * xs[6], 0.2f * +ys[0] },
		{ 0.2f * xs[8], 0.2f * +ys[2] },
		{ 0.2f * xs[7], 0.2f * +ys[3] },

		{ 0.2f * xs[7], 0.2f * -ys[3] }, // lower half, starts at the back and goes towards the front
		{ 0.2f * xs[8], 0.2f * -ys[2] }, // this is essentially the same as the upper half, except in reverse.
		{ 0.2f * xs[6], 0.2f * -ys[0] },
		{ 0.2f * xs[5], 0.2f * -ys[1] },
		{ 0.2f * xs[4], 0.2f * -ys[2] },
		{ 0.2f * xs[4], 0.2f * -ys[4] },
		{ 0.2f * xs[3], 0.2f * -ys[4] }, 
		{ 0.2f * xs[2], 0.2f * -ys[3] },
		{ 0.2f * xs[1], 0.2f * -ys[3] },
		{ 0.2f * xs[0], 0.2f * -ys[5] }, 

		{ 0.2f * xs[0], 0.2f * +ys[5] } // link back to beginning (connects both sides at the "front")
	} };
#	elif SPACESHIP == SPACESHIP_CUSTOM
		float xOffset = 50.f;
		float yOffset = 40.f;

	LineStrip spaceship{ {
		
		// Cockpit (3 points)
		{ (0.2f * 460.f) - xOffset , (0.2f * 300.f) - yOffset },
		{ (0.2f * 500.f) - xOffset , (0.2f * 285.f) - yOffset },
		{ (0.2f * 500.f) - xOffset , (0.2f * 200.f) - yOffset },

		// Bottom wings (12 points)
		{ (0.2f * 460.f) - xOffset, (0.2f * 185.f) - yOffset },
		{ (0.2f * 500.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 490.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 420.f) - xOffset, (0.2f * 185.f) - yOffset },
		{ (0.2f * 410.f) - xOffset, (0.2f * 185.f) - yOffset },
		{ (0.2f * 400.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 390.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 380.f) - xOffset, (0.2f * 185.f) - yOffset },
		{ (0.2f * 370.f) - xOffset, (0.2f * 185.f) - yOffset },
		{ (0.2f * 320.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 310.f) - xOffset, (0.2f * -185.f) - yOffset },
		{ (0.2f * 340.f) - xOffset, (0.2f * 185.f) - yOffset },

		// Tail (3 points)
		{ (0.2f * 0.f) - xOffset, (0.2f * 225.f) - yOffset},
		{ (0.2f * 0.f) - xOffset, (0.2f * 245.f) - yOffset},
		{ (0.2f * 340.f) - xOffset, (0.2f * 300.f) - yOffset},

		// Top wings (12 points)
		{ (0.2f * 340.f) - xOffset, (0.2f * 300.f) - yOffset},
		{ (0.2f * 310.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 320.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 370.f) - xOffset, (0.2f * 300.f) - yOffset},
		{ (0.2f * 380.f) - xOffset, (0.2f * 300.f) - yOffset},
		{ (0.2f * 390.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 400.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 410.f) - xOffset, (0.2f * 300.f) - yOffset},
		{ (0.2f * 420.f) - xOffset, (0.2f * 300.f) - yOffset},
		{ (0.2f * 490.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 500.f) - xOffset, (0.2f * 670.f) - yOffset},
		{ (0.2f * 460.f) - xOffset, (0.2f * 300.f) - yOffset},
	
	} };
#	endif

	if( spaceship.vertex_count() > 32 )
	{
		std::fprintf( stderr, "WARNING: you must use at most 32 points for your custom spaceship design. You are currently using %zu\n", spaceship.vertex_count() );
	}

	return spaceship;
}
