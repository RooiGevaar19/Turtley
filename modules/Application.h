#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstring>
#include <string>

using std::string;

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

class Application {
    private:
        SDL_Window* gWindow = NULL;
        SDL_Surface* gScreenSurface = NULL;
        SDL_Surface* gKeyPressSurfaces[SURFACE_TOTAL];
        SDL_Surface* gCurrentSurface = NULL;
        bool init();
        void close();
        SDL_Surface* loadSurface(string path);
        bool loadMedia();
    public:
        Application();
        ~Application();
        void run();
};

#endif