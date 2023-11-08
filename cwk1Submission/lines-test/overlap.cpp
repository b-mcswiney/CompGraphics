#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "correct overlap", "[overlap]")
{
    Surface surface(200, 200);
    surface.clear();

    SECTION( "horizontal" )
    {
        draw_line_solid( surface,
            {10.f, 10.f},
            {110.f, 10.f},
            { 255, 255, 255}
        );

        auto const rowBefore = max_row_pixel_count(surface);
        auto const colBefore = max_col_pixel_count(surface);


        draw_line_solid( surface,
            {10.f, 10.f},
            {110.f, 10.f},
            { 50, 100, 50}
        );

        auto const rowAfter = max_row_pixel_count(surface);
        auto const colAfter = max_col_pixel_count(surface);

        // Pixel counts should be the same after the 2nd line is drawn
        REQUIRE( rowBefore == rowAfter );
        REQUIRE( colBefore == colAfter );
    }
    SECTION( "vertical" )
    {
        draw_line_solid( surface,
            {10.f, 10.f},
            {10.f, 110.f},
            { 255, 255, 255}
        );

        auto const rowBefore = max_row_pixel_count(surface);
        auto const colBefore = max_col_pixel_count(surface);


        draw_line_solid( surface,
            {10.f, 10.f},
            {10.f, 110.f},
            { 50, 100, 50}
        );

        auto const rowAfter = max_row_pixel_count(surface);
        auto const colAfter = max_col_pixel_count(surface);

        // Pixel counts should be the same after the 2nd line is drawn
        REQUIRE( rowBefore == rowAfter );
        REQUIRE( colBefore == colAfter );
    }
    SECTION( "diagonal" )
    {
        draw_line_solid( surface,
            {10.f, 10.f},
            {110.f, 110.f},
            { 255, 255, 255}
        );

        auto const rowBefore = max_row_pixel_count(surface);
        auto const colBefore = max_col_pixel_count(surface);


        draw_line_solid( surface,
            {10.f, 10.f},
            {110.f, 110.f},
            { 50, 100, 50}
        );

        auto const rowAfter = max_row_pixel_count(surface);
        auto const colAfter = max_col_pixel_count(surface);

        // Pixel counts should be the same after the 2nd line is drawn
        REQUIRE( rowBefore == rowAfter );
        REQUIRE( colBefore == colAfter );
    }
}