#include <catch2/catch_amalgamated.hpp>

#include <algorithm>
#include <iostream>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "no gaps in whole surface ", "[whole surface]")
{
    Surface surface ( 10, 10);
    surface.clear();

    SECTION( "whole surface ")
    {
        for(int y = 0; (float)y <= surface.get_height(); y++)
        {
            draw_line_solid( surface,
                { 0.f, (float)y },
                { (float)surface.get_width(), (float)y },
                { 255, 255, 255}
            );
        }

        auto const counts = count_pixel_neighbours( surface );

        // All inner pixels should have 8 neighbours
        REQUIRE( counts[8] ==  64);
        // All edges should have 5 neighbours
        REQUIRE( counts[5] == 32);
        // 4 pixels should have 3 neighbours (corners)
        REQUIRE( counts[3] == 4);
        // All pixels should have neighbours
        REQUIRE( counts[0] == 0 );
    }
}