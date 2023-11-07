#include <benchmark/benchmark.h>

#include <algorithm>

#include <cassert>
#include <cstring>

#include "../draw2d/image.hpp"
#include "../draw2d/surface.hpp"

void blit_no_mask( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	for(int y = 0; (float)y < aImage.get_height(); y++)
	{
		for(int x = 0; (float)x < aImage.get_width(); x++)
		{
			int surfaceX = x + aPosition.x;
			int surfaceY = y + aPosition.y;

			ColorU8_sRGB_Alpha pixel = aImage.get_pixel(x, y);

			// Only draw what's within the surface
			if(surfaceX > 0 && (float)surfaceX < aSurface.get_width()
				&& surfaceY > 0 && (float)surfaceY < aSurface.get_height()) 
			{
				ColorU8_sRGB colour = {pixel.r, pixel.g, pixel.b};
				aSurface.set_pixel_srgb(surfaceX, surfaceY, colour);
			}
		}
	}
}

void blit_memcpy(  Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	// Clipping X values
	int clipping_x_offset = 0;
	if(aPosition.x < 0)
	{
		clipping_x_offset = abs(aPosition.x);

	}
	if(aPosition.x > aSurface.get_width())
	{
		clipping_x_offset = aSurface.get_width() - aPosition.x;
	}
	// Clipping Y values
	int clipping_y_offset = 0;
	if(aPosition.y < 0)
	{
		clipping_y_offset = abs(aPosition.y);

	}
	if(aPosition.y > aSurface.get_height())
	{
		clipping_y_offset = aSurface.get_height() - aPosition.y;
	}

	const uint8_t *surfacePtr = aSurface.get_surface_ptr() + 
								aSurface.get_linear_index(aPosition.x + clipping_x_offset, aPosition.y + clipping_y_offset);

	for(int y = 0; (float)y < aImage.get_height(); y++)
	{
		
		const uint8_t *imageptr = aImage.get_image_ptr ()+ aImage.get_linear_index(clipping_x_offset , y);

		// Normally would not allow casting however since we are just testing for time it is allowed
		std::memcpy(const_cast<uint8_t*>(surfacePtr), imageptr, (aImage.get_width() - clipping_x_offset) * 4);
	}
}

namespace
{
	void default_blit_earth_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/earth.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_masked( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	void blit_no_mask_benchmark( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/earth.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_no_mask( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	void blit_memcpy_benchmark( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/earth.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_memcpy( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}
}

BENCHMARK( default_blit_earth_ )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;

BENCHMARK ( blit_no_mask_benchmark )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;

BENCHMARK ( blit_memcpy_benchmark )
	->Args( { 320, 240 } )
	->Args( { 7680, 4320 } )
;

BENCHMARK_MAIN();
