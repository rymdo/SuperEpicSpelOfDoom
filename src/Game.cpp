#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../include/Game.h"
#include "../include/Surface.h"
#include "../include/Event.h"


Game::Game()
{
    run             = true;
    surface         = NULL;
    surface_test    = NULL;
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

    if((surface_test = Surface::Load("files/background/lava.jpg")) == NULL)
    {
        return false;
    }

    return true;
}



bool Game::Event(SDL_Event* event)
{
    Event::OnEvent(event);
    return true;
}

void Game::Exit()
{
    run = false;
}

void Game::Loop()
{

}

void Game::Render()
{
    Surface::Draw(surface, surface_test, 0, 0);
    SDL_Flip(surface);
}

void Game::CleanUp()
{
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface_test);
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


bool Game::Event(SDL_Event* event)
{
    if(event->type == SDL_QUIT)
    {
        run = false;
    }
}
*/

