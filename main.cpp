//Using SDL and standard IO
#include <SDL2/SDL.h>  
#include <cstdio>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gTurtle = NULL;

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

bool loadTurtleMedia(char fname[]) {
    //Loading success flag
    bool success = true;

    //Load splash image
    gTurtle = SDL_LoadBMP(fname);
    if(gTurtle == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", fname, SDL_GetError() );
        success = false;
    }

    return success;
}

void close() {
    SDL_FreeSurface(gTurtle);
    gTurtle = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}


int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadTurtleMedia("images/turtley_screen.bmp")) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;

            //Apply the image
            SDL_Delay(2000);

            //While application is running
            while(!quit) {
                while( SDL_PollEvent( &e ) != 0 ) {
                    //User requests quit
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_BlitSurface(gTurtle, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}

