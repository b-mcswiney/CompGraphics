#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "flat triangle", "[flat triangle][!mayfail]")
{
    Surface surface( 320, 240 );
    surface.clear();

    SECTION( "Barycentric test" )
    {
        draw_triangle_interp( surface,
            { 20.f, 20.f}, {30.f, 20.f}, {40.f, 20.f},
            {100, 100, 100}, {100, 100, 100}, {100,100,100}
            );
        
        auto const stride = surface.get_height() << 2;

        int rowCount = 0;

        for(int x = 0; (float)x < surface.get_height(); x++)
        {
            for(int y = 0; y < (float)surface.get_width(); y++)
            {
                auto const idx = y * stride + (x<<2);
                auto const ptr = surface.get_surface_ptr() + idx;

                if( ptr[0] > 0)
                {
                    rowCount += 1;
                }
            }
        }

        // Ensure only 1 row has pixels
        REQUIRE( rowCount == 1);
    }
    SECTION( "Solid test" )
    {
        draw_triangle_solid( surface,
            { 20.f, 20.f}, {30.f, 20.f}, {40.f, 20.f},
            {100, 100, 100}
            );
        
        auto const stride = surface.get_height() << 2;

        int rowCount = 0;

        for(int x = 0; (float)x < surface.get_height(); x++)
        {
            for(int y = 0; y < (float)surface.get_width(); y++)
            {
                auto const idx = y * stride + (x<<2);
                auto const ptr = surface.get_surface_ptr() + idx;

                if( ptr[0] > 0)
                {
                    rowCount += 1;
                    break;
                }
            }
        }

        // Ensure only 1 row has pixels
        REQUIRE( rowCount == 1);
    }
}