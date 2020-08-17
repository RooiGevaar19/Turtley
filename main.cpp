//Using SDL and standard IO
#include <SDL2/SDL.h>  
#include <cstdio>
#include <cstring>
#include <string>

using std::string;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Key press surfaces constants
enum SurfacesIndexes
{
    SURFACE_DEFAULT,
    SURFACE_INTRO,
    SURFACE_KEY_PRESS_UP,
    SURFACE_KEY_PRESS_DOWN,
    SURFACE_KEY_PRESS_LEFT,
    SURFACE_KEY_PRESS_RIGHT,
    SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        gWindow = SDL_CreateWindow( "Turtley 0.0.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(gWindow == NULL) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

SDL_Surface* loadSurface(string path)
{
    //The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	} else {
        //Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if( optimizedSurface == NULL ) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[SURFACE_DEFAULT] = loadSurface("images/turtley_screen.bmp");
    if (gKeyPressSurfaces[SURFACE_DEFAULT] == NULL)
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_INTRO] = loadSurface("images/turtley_intro.bmp");
    if (gKeyPressSurfaces[SURFACE_INTRO] == NULL)
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[SURFACE_KEY_PRESS_UP] = loadSurface("images/turtley_screen_up.bmp");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_UP] == NULL) {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[SURFACE_KEY_PRESS_DOWN] = loadSurface("images/turtley_screen_down.bmp");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_DOWN] == NULL) {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[SURFACE_KEY_PRESS_LEFT] = loadSurface("images/turtley_screen_left.bmp");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_LEFT] == NULL) {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[SURFACE_KEY_PRESS_RIGHT] = loadSurface("images/turtley_screen_right.bmp");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_RIGHT] == NULL) {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close() {
	//Deallocate surfaces
	for(int i = 0; i < SURFACE_TOTAL; ++i) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[SURFACE_INTRO];
            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
            gCurrentSurface = gKeyPressSurfaces[SURFACE_DEFAULT];

            //While application is running
            while(!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0 ) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN) {
                        //Select surfaces based on key press
                        switch(e.key.keysym.sym) {
                            case SDLK_UP: {
                                gCurrentSurface = gKeyPressSurfaces[SURFACE_KEY_PRESS_UP];
                                break;
                            }
                            case SDLK_DOWN: {
                                gCurrentSurface = gKeyPressSurfaces[SURFACE_KEY_PRESS_DOWN];
                                break;
                            }
                            case SDLK_LEFT: {
                                gCurrentSurface = gKeyPressSurfaces[SURFACE_KEY_PRESS_LEFT];
                                break;
                            }

                            case SDLK_RIGHT: {
                                gCurrentSurface = gKeyPressSurfaces[SURFACE_KEY_PRESS_RIGHT];
                                break;
                            }

                            default: {
                                gCurrentSurface = gKeyPressSurfaces[SURFACE_DEFAULT];
                                break;
                            }
                        }
                    }
                }
                //Apply the current image
                SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
            
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}

