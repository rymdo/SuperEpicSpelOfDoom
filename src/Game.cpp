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

    Font::Load();

    player = NULL;

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

        if(sym == SDLK_m || sym == SDLK_ESCAPE)
        {
            if(player != NULL)
                mainMenu->SetState();
        }

        if(sym == SDLK_SPACE || sym == SDLK_RETURN)
        {
            string s = mainMenu->select();

            if (s == "New Game")
            {
                if (NewGame())
                    mainMenu->SetState();
            }

            if (s == "Load")
            {
                if (LoadGame())
                    mainMenu->SetState();
            }

            if (s == "Save")
                SaveGame();

            if (s == "Exit")
                Exit();
        }

        return;
    }

    if(sym == SDLK_m || sym == SDLK_ESCAPE)
        mainMenu->SetState();

    if (player == NULL) return;

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

    if(sym == SDLK_SPACE)
    {
        cout << "Player x: " << player->getPosX() << " y: " << player->getPosY() << endl;

        Object* testObj = new Object(player->getPosX(), player->getPosY()+50, 10, 3, 50);
        testObj->Load("files/sprites/cinnamonbun.png");

    }
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if (player == NULL) return;
    if(sym == SDLK_DOWN || sym == SDLK_UP)
    {
        player->SetMovementY(0);
    }

    if(sym == SDLK_LEFT || sym == SDLK_RIGHT)
    {
        player->SetMovementX(0);
    }

}

bool Game::NewGame()
{
    Camera* cam = new Camera();
    Surface::setCamera(cam);

    if (!Tile::loadAll())
        return false;

    player = new Player(cam, 500, 500, 20);
    player->Load();

    Sprite* monk1 = new Sprite(32, 110, 10, 3, 32);
    monk1->Load("files/sprites/monk/monk_stand_front.png");

    Sprite* monk3 = new Sprite(96, 110, 10, 3, 32);
    monk3->Load("files/sprites/monk/monk_stand_back.png");

    Object* poke = new Object(600, 700, 10, 1, 100);
    poke->Load("files/sprites/poke.png");

    gameTime = 0;

    return true;
}

bool Game::SaveGame()
{
    ofstream savefile;
    savefile.open("save.txt");

    /*if(!savefile.is_open())
    {
        cout << "Error occurred while saving";
        return;
    }

    cout << "Saved Successfully!";*/

    if(player==NULL)
    {
        cout << "There is no game to save!";
        return false;
    }

    savefile << player->getPosX() << " " << player->getPosY();

    savefile.close();

    return true;
}

bool Game::LoadGame()
{
    Sprite::Cleanup();
    if (!NewGame())
        return false;

    float x;
    float y;
    ifstream loadfile;
    loadfile.open("save.txt");
    loadfile >> x >> y;

    //if(player == NULL) return false;
    player->setPos(x,y);
    loadfile.close();
    //fixa kanelbullar, urladdning, att man kan loada ett spel direkt
    return true;
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
        mainMenu->Draw(surface);
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
