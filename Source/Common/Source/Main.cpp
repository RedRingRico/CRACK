#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

int main( int p_Argc, char **p_ppArgv )
{
	SDL_Window *pWindow = nullptr;
	SDL_GameController *pController = nullptr;
	SDL_DisplayMode Display;
	SDL_GLContext GLContext;

	std::cout << "CRACK" << std::endl;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC |
		SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0 )
	{
		std::cout << "Could not initialise SDL 2" << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );

	SDL_GetDesktopDisplayMode( 0, &Display );

	pWindow = SDL_CreateWindow( "CRACK", 0, 0, Display.w, Display.h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS |
		SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MOUSE_FOCUS |
		SDL_WINDOW_OPENGL );

	GLContext = SDL_GL_CreateContext( pWindow );

	if( GLContext == nullptr )
	{
		std::cout << "Failed to create the GL context: " << SDL_GetError( ) <<
			std::endl;

		return 1;
	}

	glewExperimental = GL_TRUE;
	GLenum GLEWError = glewInit( );

	if( GLEWError != GLEW_OK )
	{
		std::cout << "Could not initialise GLEW" << std::endl;
		return 1;
	}

	std::cout << "GL Vendor: " << glGetString( GL_VENDOR ) << std::endl;

	glClearColor( 0.0f, 1.0f, 0.0f, 1.0f );

	SDL_ShowCursor( 0 );

	if( pWindow == nullptr )
	{
		std::cout << "Failed to create an SDL 2 window" << std::endl;
		return 1;
	}

	SDL_SetWindowDisplayMode( pWindow, nullptr );

	SDL_Event Event;

	bool Run = true;

	while( Run )
	{
		while( SDL_PollEvent( &Event ) != 0 )
		{
			if( Event.type == SDL_KEYDOWN )
			{
				switch( Event.key.keysym.sym )
				{
					case SDLK_UP:
					{
						Run = false;
						break;
					}
				}
			}
			else if( Event.type == SDL_CONTROLLERBUTTONDOWN )
			{
				std::cout << "Controller button" << std::endl;
				switch( Event.cbutton.button )
				{
					case SDL_CONTROLLER_BUTTON_A:
					{
						Run = false;
						break;
					}
				}
			}
			else if( Event.type == SDL_CONTROLLERBUTTONUP )
			{
				std::cout << "Controller button up" << std::endl;
				switch( Event.cbutton.button )
				{
					case SDL_CONTROLLER_BUTTON_A:
					{
						Run = false;
						break;
					}
				}
			}
			else if( Event.type == SDL_CONTROLLERDEVICEADDED )
			{
				Sint32 ControllerIndex = Event.cdevice.which;
				if( SDL_IsGameController( ControllerIndex ) )
				{
					pController = SDL_GameControllerOpen( ControllerIndex );

					if( pController != nullptr )
					{
						std::cout << "Got controller: \"" <<
							SDL_GameControllerName( pController ) << "\"" <<
							std::endl;
						break;
					}
					else
					{
						std::cout << "Could not open game controller " <<
							ControllerIndex << ": " << SDL_GetError( ) <<
							std::endl;
					}
				}
			}
		}

		glClear( GL_COLOR_BUFFER_BIT );

		SDL_GL_SwapWindow( pWindow );
	}

	SDL_ShowCursor( 1 );

	SDL_GameControllerClose( pController );

	SDL_DestroyWindow( pWindow );
	SDL_Quit( );

	return 0;
}

