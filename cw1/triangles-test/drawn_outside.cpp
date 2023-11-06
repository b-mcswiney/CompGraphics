#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "Drawn outside", "[draw outside][!mayfail]")
{
    Surface surface( 320, 240 );
    surface.clear();

    SECTION( "Barycentric test" )
    {
        REQUIRE( 0 == 0);
    }
    SECTION( "Solid test" )
    {
        REQUIRE( 0 == 0);
    }
}