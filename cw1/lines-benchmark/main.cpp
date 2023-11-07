#include <benchmark/benchmark.h>

#include "../draw2d/draw.hpp"
#include "../draw2d/surface.hpp"

void draw_line_bresenham( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
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
	// Absolute value ensures we never divide by 0
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
		if(currentX >= 0 && currentX < aSurface.get_width()
			&& currentY >= 0 && currentY < aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(currentX, currentY, aColor);
			}

		currentY += yInc;
		currentX += xInc;
	}
}

namespace
{	
	void DDA_benchmark_diagonal( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			draw_line_solid( surface, 
							{0, 0}, 
							{(float)surface.get_width(), (float)surface.get_height()}, 
							{255, 255, 255}
						);

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}
	}
	void bresenham_benchmark_diagonal( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			draw_line_bresenham( surface, 
								{0, 0}, 
								{(float)surface.get_width(), (float)surface.get_height()}, 
								{255, 255, 255}
							);

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}
	}
}


BENCHMARK( DDA_benchmark_diagonal )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;
BENCHMARK( bresenham_benchmark_diagonal )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;

BENCHMARK_MAIN();
