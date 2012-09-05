#include "../include/Game.h"
#include <SDL/SDL.h>


Game::Game()
{
    run     = true;
    surface = NULL;
    //ctor
}

Game::~Game()
{
    //dtor
}


void Game::Execute()
{
    Init();
    SDL_Event event;

    while(run)
    {
        while(SDL_PollEvent(&event))
        {
            Event(&event);
        }
        Loop();
        Render();
    }
    CleanUp();
}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((surface= SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    return true;
}



bool Game::Event(SDL_Event* event)
{
    if(event->type == SDL_QUIT)
    {
        run = false;
    }
}

void Game::Loop()
{

}

void Game::Render()
{

}

void Game::CleanUp()
{
    SDL_Quit();
}


/*
void Game::loop()
{
    bool run = true;
    while (run)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                run = false;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        run = false;
                    break;
                }
            } // end switch
        } // end of message processing
        SDL_Flip(screen);
    }
}
*/

