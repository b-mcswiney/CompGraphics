#include <benchmark/benchmark.h>

#include "../draw2d/draw.hpp"
#include "../draw2d/surface.hpp"

void draw_line_bresenham( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	// Calculate slope
	float dx = aEnd.x - aBegin.x;
	float dy = aEnd.y - aEnd.x;

	// Initialise driver
	float driver;
	float currentPxl;

	if(abs(dx) > abs(dy))
	{
		driver = dy/dx;
		currentPxl = aBegin.y;
	}
	else
	{
		driver = dx/dy;
		currentPxl = aBegin.x;
	}
	int error = abs(driver)-1;

	if(abs(dx)>abs(dy))
	{
		for(int i = aBegin.x; i <= aEnd.x; i++)
		{
			if(i >= 0 && i < (float)aSurface.get_width()
				&& currentPxl >= 0 && currentPxl < (float)aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(i, currentPxl, aColor);
			}

			if(error >= 0)
			{
				currentPxl += 1;
				error -= 1;
			}

			error += driver;
		}
	}
	else
	{
		for(int i = aBegin.y; i <= aEnd.y; i++)
		{
			if(currentPxl >= 0 && currentPxl < (float)aSurface.get_width()
				&& i >= 0 && i < (float)aSurface.get_height()) 
			{
				aSurface.set_pixel_srgb(currentPxl, i, aColor);
			}

			if(error >= 0)
			{
				currentPxl += 1;
				error -= 1;
			}

			error += driver;
		}
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
	void DDA_benchmark_horizontal( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			draw_line_solid( surface, 
							{(float)surface.get_width() * 0.2f, (float)surface.get_height() * 0.5f}, 
							{(float)surface.get_width() * 0.8f, (float)surface.get_height() * 0.5f}, 
							{255, 255, 255}
						);

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}
	}
	void besenham_benchmark_horizontal( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			draw_line_bresenham( surface, 
							{(float)surface.get_width() * 0.2f, (float)surface.get_height() * 0.5f}, 
							{(float)surface.get_width() * 0.8f, (float)surface.get_height() * 0.5f}, 
							{255, 255, 255}
						);

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}
	}
	void DDA_benchmark_fullscreen( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			for(int i=0; i < (int)surface.get_height(); i++)
			{
				// Draw line from corner to corner
				draw_line_solid( surface, 
								{0, (float)i}, 
								{(float)surface.get_width(), (float)i}, 
								{255, 255, 255}
							);
			}

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}
	}
	void bresenham_benchmark_fullscreen( benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		for( auto _ : aState )
		{
			// Draw line from corner to corner
			for(int i=0; i < (int)surface.get_height(); i++)
			{
				// Draw line from corner to corner
				draw_line_bresenham( surface, 
								{0, (float)i}, 
								{(float)surface.get_width(), (float)i}, 
								{255, 255, 255}
							);
			}

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
BENCHMARK( DDA_benchmark_horizontal )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;
BENCHMARK( besenham_benchmark_horizontal )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;
BENCHMARK( DDA_benchmark_fullscreen )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;
BENCHMARK( bresenham_benchmark_fullscreen )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;


BENCHMARK_MAIN();
