#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/Game.h"
#include "../include/Surface.h"
#include "../include/Event.h"
#include "../include/Tile.h"
#include "../include/Sprite.h"

using namespace std;

Game::Game()
{
    run             = true;
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
    /*
    if((surface_temp = Surface::Load("files/sprites/link/linkD1.gif")) == NULL)
    {

        return false;
    }
    */

    if (!Tile::loadAll())
        return false;

    player = new Object(150, 50, "files/sprites/link/linkD1.gif");
    //player->Load("files/sprites/link/linkD1.gif");

    //Sprite* link = new Sprite(100, 100);
    //link->Load("files/sprites/link/linkD1.gif");

    //Sprite* link2 = new Sprite(200, 200);
    //link2->Load("files/sprites/link/linkD1.gif");



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

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if(sym == SDLK_DOWN)
    {
        player->SetMovement(0,2);
    }
    if(sym == SDLK_UP)
    {
        player->SetMovement(0,-2);
    }
    if(sym == SDLK_LEFT)
    {
        player->SetMovement(-2,0);
    }
    if(sym == SDLK_RIGHT)
    {
        player->SetMovement(2,0);
    }
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if(sym == SDLK_DOWN)
    {
        player->SetMovement(0,0);
    }
    if(sym == SDLK_UP)
    {
        player->SetMovement(0,0);
    }
    if(sym == SDLK_LEFT)
    {
        player->SetMovement(0,0);
    }
    if(sym == SDLK_RIGHT)
    {
        player->SetMovement(0,0);
    }
}

void Game::Loop()
{

    SDL_Delay(30);
}

void Game::Render()
{
    //Surface::Draw(surface, surface_test, 0, 0);
    Sprite::DrawAll(surface);

    SDL_Flip(surface);
}

void Game::CleanUp()
{
    SDL_FreeSurface(surface);
    //SDL_FreeSurface(surface_test);
    SDL_Quit();
}
