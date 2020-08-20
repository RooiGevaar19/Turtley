#ifndef APPLICATIONTEST2_H_
#define APPLICATIONTEST2_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <cstdio>
#include <cstring>
#include <string>

using std::string;

class ApplicationTest2 {
    private:
        //Loads individual image as texture
        SDL_Window* gWindow = NULL;
        SDL_Renderer* gRenderer = NULL;
        SDL_Texture* gTexture = NULL;
        SDL_Texture* loadTexture(string path);
        bool init();
        void close();
        bool loadMedia();
    public:
        ApplicationTest2();
        ~ApplicationTest2();
        void run();
};

#endif