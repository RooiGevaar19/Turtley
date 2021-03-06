#include "ApplicationTest.h"

bool ApplicationTest::init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        gWindow = SDL_CreateWindow( "Turtley Test 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(gWindow == NULL) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init( imgFlags ) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

SDL_Surface* ApplicationTest::loadSurface(string path) {
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	} else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if( optimizedSurface == NULL ) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool ApplicationTest::loadMedia() {
    bool success = true;

    gKeyPressSurfaces[SURFACE_DEFAULT] = loadSurface("images/turtley_screen.png");
    if (gKeyPressSurfaces[SURFACE_DEFAULT] == NULL) {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_INTRO] = loadSurface("images/turtley_intro.png");
    if (gKeyPressSurfaces[SURFACE_INTRO] == NULL) {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_KEY_PRESS_UP] = loadSurface("images/turtley_screen_up.png");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_UP] == NULL) {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_KEY_PRESS_DOWN] = loadSurface("images/turtley_screen_down.png");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_DOWN] == NULL) {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_KEY_PRESS_LEFT] = loadSurface("images/turtley_screen_left.png");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_LEFT] == NULL) {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    gKeyPressSurfaces[SURFACE_KEY_PRESS_RIGHT] = loadSurface("images/turtley_screen_right.png");
    if (gKeyPressSurfaces[SURFACE_KEY_PRESS_RIGHT] == NULL) {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void ApplicationTest::close() {
	for(int i = 0; i < SURFACE_TOTAL; ++i) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

ApplicationTest::ApplicationTest() {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else if (!loadMedia()) {
        printf("Failed to load media!\n");
    }
}

ApplicationTest::~ApplicationTest() {
    close();
}

void ApplicationTest::run() {
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
