#include <catch2/catch_amalgamated.hpp>

#include <algorithm>
#include <iostream>
#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "no gaps in parallel lines", "[parallel]" )
{
    Surface surface(200, 200);
    surface.clear();

    SECTION( "horizontal" )
    {
        draw_line_solid( surface,
            { 10.f, 10.f },
            { 20.f, 10.f },
            { 255, 255, 255}
        );
        draw_line_solid( surface,
            { 10.f, 11.f },
            { 20.f, 11.f },
            { 255, 255, 255}
        );

        auto const counts = count_pixel_neighbours( surface );

        // 4 pixels should have 3 neighbours (corners)
        REQUIRE( counts[3] == 4);

        // Every other pixel should have 5 neighbours (edges)
        REQUIRE( counts[5] == 16);

        // No pixel should have 0,1,2 or 4 neighbours
        REQUIRE( counts[0] == 0);
        for(std::size_t i = 0; i < counts.size(); i++)
        {
            if(i != 3 && i != 5)
            {
                REQUIRE( counts[i] == 0);
            }
        }
    }
    SECTION( "vertical" )
    {
        draw_line_solid( surface,
            { 10.f, 10.f },
            { 10.f, 20.f },
            { 255, 255, 255}
        );
        draw_line_solid( surface,
            { 11.f, 10.f },
            { 11.f, 20.f },
            { 255, 255, 255}
        );

        auto const counts = count_pixel_neighbours( surface );

        // 4 pixels should have 3 neighbours (corners)
        REQUIRE( counts[3] == 4);

        // Every other pixel should have 5 neighbours (edges)
        REQUIRE( counts[5] == 16);

        // No pixel should have 0,1,2 or 4 neighbours
        REQUIRE( counts[0] == 0);
        for(std::size_t i = 0; i < counts.size(); i++)
        {
            if(i != 3 && i != 5)
            {
                REQUIRE( counts[i] == 0);
            }
        }
    }
    SECTION( "diagonal" )
    {
        draw_line_solid( surface,
            { 10.f, 10.f },
            { 20.f, 20.f },
            { 255, 255, 255}
        );
        draw_line_solid( surface,
            { 10.f, 11.f },
            { 20.f, 21.f },
            { 255, 255, 255}
        );

        auto const counts = count_pixel_neighbours( surface );

        // 2 pixels should have 2 neighbours
        REQUIRE( counts[2] == 2);

        // 2 pixels should have 3 neighbours (corners)
        REQUIRE( counts[3] == 2);

        // Every other pixel should have 4 neighbours (edges)
        REQUIRE( counts[4] == 16);

        // No pixel should have 0,1,2 or 4 neighbours
        REQUIRE( counts[0] == 0);
        for(std::size_t i = 0; i < counts.size(); i++)
        {
            if( i != 2 && i != 3 && i != 4)
            {
                REQUIRE( counts[i] == 0);
            }
        }
    }
}