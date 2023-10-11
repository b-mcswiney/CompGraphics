#include <glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <typeinfo>
#include <stdexcept>

#include <cstdio>
#include <vector>


#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

#include "../support/error.hpp"
#include "../support/context.hpp"

#define 	GLFW_MOUSE_BUTTON_1   0
#define 	GLFW_MOUSE_BUTTON_LEFT  GLFW_MOUSE_BUTTON_1   

int mouseX;
int mouseY;

std::vector<float> mousePos;


namespace
{
	constexpr int kInitialWindowWidth = 1280;
	constexpr int kInitialWindowHeight = 720;
	constexpr char const* kWindowTitle = "COMP3811-Exercise 1";

	void glfw_callback_error_( int, char const* );

	void glfw_callback_key_( GLFWwindow*, int, int, int, int );

	void glfw_cb_motion_( GLFWwindow* aWindow, double mousePosX, double mousePosY);

	void glfw_cb_button_( GLFWwindow* aWindow, int aButton, int aAction, int aMod );

	struct GLFWCleanupHelper
	{
		~GLFWCleanupHelper();
	};
}

int main() try
{
	if( GLFW_TRUE != glfwInit() )
	{
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwInit() failed with '%s' (%d)", msg, ecode );
	}

	// Ensure that we call glfwTerminate() at the end of the program.
	GLFWCleanupHelper cleanupHelper;

	glfwSetErrorCallback( &glfw_callback_error_ );

	glfwWindowHint( GLFW_SRGB_CAPABLE, GLFW_TRUE );
	glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );

	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE ); // Prevent resizing for now...

#	if !defined(__APPLE__)
	// Most platforms will support OpenGL 4.3
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
#	else // defined(__APPLE__)
	// Apple has at most OpenGL 4.1, so don't ask for something newer.
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
#	endif // ~ __APPLE__
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#	if !defined(NDEBUG)
	// When building in debug mode, request an OpenGL debug context. This
	// enables additional debugging features. However, this can carry extra
	// overheads. We therefore do not do this for release builds.
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );
#	endif // ~ !NDEBUG

	GLFWwindow* window = glfwCreateWindow(
		kInitialWindowWidth,
		kInitialWindowHeight,
		kWindowTitle,
		nullptr, nullptr
	);

	if( !window )
	{
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwCreateWindow() failed with '%s' (%d)", msg, ecode );
	}

	int iwidth, iheight;
	glfwGetFramebufferSize( window, &iwidth, &iheight );

	float wscale = 1.f, hscale = 1.f;
#	if defined(__APPLE__)
	// HACK: Window content scaling on MacOS.
	//
	// This is a workaround for MacOS, where scaling affects retina displays.
	// Windows technically also does content scaling, but it seems to do this
	// more transparently. Either way, the behaviour doesn't seem to be
	// consistent across the platforms, though, which is slightly unfortunate.
	// (And not having a (retina) Mac to test on makes figuring this out a tad
	// more tricky.)
	glfwGetWindowContentScale( window, &wscale, &hscale );
#	endif

	assert( iwidth >= 0 && iheight >= 0 && wscale != 0.f && hscale != 0.f );
	auto const fbwidth = std::uint32_t(iwidth / wscale);
	auto const fbheight = std::uint32_t(iheight / hscale);

	glfwSetKeyCallback( window, &glfw_callback_key_ );

	glfwSetCursorPosCallback( window, &glfw_cb_motion_ );

	glfwSetMouseButtonCallback( window, &glfw_cb_button_ );

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );

	Context context( fbwidth, fbheight );
	Surface surface( fbwidth, fbheight );

	while( !glfwWindowShouldClose( window ) )
	{
		// Let GLFW process events
		glfwWaitEvents();
		//glfwPollEvents();

		// Update state
		// Nothing to do at the moment...
	
		// Draw scene
		surface.clear();

		surface.set_pixel_srgb( 10, 100, { 255, 255, 255 } );
		surface.set_pixel_srgb( 1, 10, { 255, 255, 255 } );
		surface.set_pixel_srgb( 10, 1, { 255, 0, 0 } );
		//TODO: drawing code goes here

		// draw_rectangle_solid(
		// 	surface,
		// 	{ 500.f, 300.f },
		// 	{ 650.f, 450.f },
		// 	{ 255, 0, 0 } // red
		// 	);
		// draw_rectangle_outline(
		// 	surface,
		// 	{  50.f, 300.f },
		// 	{ 200.f, 450.f },
		// 	{ 0, 255, 0 } // green
		// 	);

		draw_rectangle_outline(
			surface,
			{  50.f, 300.f },
			{ 200.f, 450.f },
			{ 0, 255, 0 } // green
			);

		if(mousePos.size() > 3)
		{	
			std::cout << "MousePos 0 and 1: " << mousePos[0] << ", " << mousePos[1] << std::endl;
			std::cout << "MousePos 2 and 3: " << mousePos[2] << ", " << mousePos[3] << std::endl;
			// mousePos[0] = 50.f;
			// mousePos[1] = 300.f;
			// mousePos[2] = 200.f;
			// mousePos[3] = 450.f;
			draw_rectangle_solid(
				surface,
				{ mousePos[0], mousePos[3]},
				{ mousePos[2], mousePos[1]},
				{ 0, 0, 255 } // blue
				);
		}

		context.draw( surface );

		// Display results
		glfwSwapBuffers( window );
	}

	// Cleanup.
	// For now, all objects are automatically cleaned up when they go out of
	// scope.
	
	return 0;
}
catch( std::exception const& eErr )
{
	std::fprintf( stderr, "Top-level Exception (%s):\n", typeid(eErr).name() );
	std::fprintf( stderr, "%s\n", eErr.what() );
	std::fprintf( stderr, "Bye.\n" );
	return 1;
}


namespace
{
	void glfw_callback_error_( int aErrNum, char const* aErrDesc )
	{
		std::fprintf( stderr, "GLFW error: %s (%d)\n", aErrDesc, aErrNum );
	}

	void glfw_callback_key_( GLFWwindow* aWindow, int aKey, int, int aAction, int )
	{
		if( GLFW_KEY_ESCAPE == aKey && GLFW_PRESS == aAction )
		{
			glfwSetWindowShouldClose( aWindow, GLFW_TRUE );
			return;
		}
	}

	void glfw_cb_motion_( GLFWwindow* aWindow, double mousePosX, double mousePosY)
	{
		//std::cout << "Mouse position: " << mousePosX << ", " << mousePosY << std::endl;
		mouseX = mousePosX;
		mouseY = mousePosY;
	}

	void glfw_cb_button_( GLFWwindow* aWindow, int aButton, int aAction, int aMod )
	{
		if (glfwGetMouseButton(aWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			std::cout << "Mouse position: " << mouseX << ", " << mouseY << std::endl;

			mousePos.push_back(mouseX);
			mousePos.push_back(mouseY);

			return;
		}
	}
}

namespace
{
	GLFWCleanupHelper::~GLFWCleanupHelper()
	{
		glfwTerminate();
	}
}


