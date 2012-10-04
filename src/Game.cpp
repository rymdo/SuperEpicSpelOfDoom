#include "../include/Game.h"

using namespace std;

Game::Game()
{
    run = true;
}

Game::~Game()
{
    //dtor
}


void Game::Execute()
{
    Init();
    SDL_Event event;
    mainMenu = new Menu();

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

    if((surface = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    if (TTF_Init() < 0)
    {
        cout << "oops TTF_Init fail...";
    }

    arial_test = TTF_OpenFont("files/fonts/arial.ttf", 12);

    if (arial_test==NULL)
    {
        cout << "oops TTF_Init fail...";
    }



    Camera* cam = new Camera();
    Surface::setCamera(cam);

    if (!Tile::loadAll())
        return false;

    player = new Player(cam, 300, 300, 20);
    player->Load();
    /*a call to player->Load() would be better. Where you dont define pahts to the files,
    but the paths are stored in the code in the player class which derives from Object...
    Then in the Load function for Player, all de needed surfaces are loaded via Surface::Load
    and stored inside the player object...
    */

    Sprite* monk1 = new Sprite(32, 110, 10, 3, 32);
    monk1->Load("files/sprites/monk/monk_stand_front.png");

    Sprite* monk3 = new Sprite(96, 110, 10, 3, 32);
    monk3->Load("files/sprites/monk/monk_stand_back.png");

    Object* testObj = new Object(200, 300, 10, 3, 32);
    testObj->Load("files/sprites/monk/monk_walk_side.png");

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
    if(mainMenu->Active())
    {
        if(sym == SDLK_DOWN)
        {
            mainMenu->next();
        }
        if(sym == SDLK_UP)
        {
            mainMenu->previous();
        }
        if(sym == SDLK_SPACE || sym == SDLK_RETURN)
        {
            mainMenu->select();
        }

        return;
    }

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
    if(sym == SDLK_m)
    {
        mainMenu->SetState();
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
    if(!mainMenu->Active())
    {
        Uint32 now = SDL_GetTicks();
        timeElapsed = now - gameTime;
        gameTime = now;

        Sprite::UpdateAll(gameTime, timeElapsed);
    //SDL_Delay(30);
    }

    //updateramenyy
}

void Game::Render()
{
    if(!mainMenu->Active())
    {
        //Surface::Draw(surface, surface_test, 0, 0);
        Sprite::DrawAll(surface, gameTime, timeElapsed);
    }
    else
    {
        mainMenu->Draw(surface, arial_test);
        /*Surface::Draw(surface, text_render_test, 100, 100);
        text_render_test = TTF_RenderText_Solid(arial_test, "HELLO WORLD!", color_test);*/
    }

    SDL_Flip(surface);
}

void Game::CleanUp()
{
    SDL_FreeSurface(surface);
    //SDL_FreeSurface(surface_test);
    TTF_Quit();
    SDL_Quit();
}
