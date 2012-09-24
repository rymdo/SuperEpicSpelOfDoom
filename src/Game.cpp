#include "../include/Game.h"

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

    player = new Object(150, 50, 10, "files/sprites/link/linkD1.gif");
    //player->Load("files/sprites/link/linkD1.gif");
    /*a call to player->Load() would be better. Where you dont define pahts to the files,
    but the paths are stored in the code in the player class which derives from Object...
    Then in the Load function for Player, all de needed surfaces are loaded via Surface::Load
    and stored inside the player object...
    */

    Sprite* monk1 = new Sprite(32, 110, 10, 3, 32);
    monk1->Load("files/sprites/monk/monk_stand_front.png");

    Sprite* monk2 = new Sprite(64, 110, 10, 3, 32);
    monk2->Load("files/sprites/monk/monk_stand_side.png");

    Sprite* monk3 = new Sprite(96, 110, 10, 3, 32);
    monk3->Load("files/sprites/monk/monk_stand_back.png");

    Sprite* monk4 = new Sprite(128, 110, 10, 3, 32);
    monk4->Load("files/sprites/monk/monk_walk_side.png");

    Camera* cam = new Camera();
    Surface::setCamera(cam);

    gameTime = 0;

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
        player->SetMovementY(0.5);
    }
    if(sym == SDLK_UP)
    {
        player->SetMovementY(-0.5);
    }
    if(sym == SDLK_LEFT)
    {
        player->SetMovementX(-0.5);
    }
    if(sym == SDLK_RIGHT)
    {
        player->SetMovementX(0.5);
    }
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if(sym == SDLK_DOWN || sym == SDLK_UP)
    {
        player->SetMovementY(0);
    }

    if(sym == SDLK_LEFT || sym == SDLK_RIGHT)
    {
        player->SetMovementX(0);
    }

}

void Game::Loop()
{
    Uint32 now = SDL_GetTicks();
    timeElapsed = now - gameTime;
    gameTime = now;

    Sprite::UpdateAll(timeElapsed);
    //SDL_Delay(30);
}

void Game::Render()
{
    //Surface::Draw(surface, surface_test, 0, 0);
    Sprite::DrawAll(surface, gameTime, timeElapsed);

    SDL_Flip(surface);
}

void Game::CleanUp()
{
    SDL_FreeSurface(surface);
    //SDL_FreeSurface(surface_test);
    SDL_Quit();
}
