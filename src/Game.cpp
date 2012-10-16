#include "../include/Game.h"

using namespace std;

/**
Constructor for Game
*/
Game::Game()
{
    run = true;
}

/**
Default destructor for Game
*/
Game::~Game()
{
    //dtor
}

/**
Initilization and starts the game loop
Basically it Calls Game::Init()
and then loop the following:
1 Event Polling
2 Game::Loop
3 Game::Render

Until the Game exits, then Game::Cleanup is called.
Call Game::Execute after instansiating a Game
*/
void Game::Execute()
{
    if (!Init())
        run == false;

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

/**
Initilization for Game
All dependencies are initiated
@return true on success, false on fail
*/
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
    runTime = 0;
    gameTime = 0;
    timeElapsed = 0;

    return true;
}

/**
Pass call to base Event
@return true on success, false on fail
*/
bool Game::Event(SDL_Event* event)
{
    Event::OnEvent(event);
    return true;
}

/**
Make the game exit on next Game loop
*/
void Game::Exit()
{
    run = false;
}

/**
Handle key down events
*/
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
        player->SetMovementX(0);
    }
    if(sym == SDLK_UP)
    {
        player->SetMovementY(-0.5);
        player->SetMovementX(0);
    }
    if(sym == SDLK_LEFT)
    {
        player->SetMovementX(-0.5);
        player->SetMovementY(0);
    }
    if(sym == SDLK_RIGHT)
    {
        player->SetMovementX(0.5);
        player->SetMovementY(0);
    }

    if(sym == SDLK_SPACE)
    {
        Object* testObj = new Object(player->getPosX(), player->getPosY()+50, 10);
        if (testObj->Load("files/sprites/cinnamonbun.png"))
            cout << "Player x: " << testObj->getPosX() << " y: " << testObj->getPosY() << endl;
    }
}

/**
Handle key up events
*/
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

/**
Starts a new Game
*/
bool Game::NewGame()
{
    Camera* cam = new Camera();
    Surface::setCamera(cam);

    if (!Tile::loadAll())
        return false;

    player = new Player(cam, 620, 810, 20);
    player->Load();

    Object* poke = new Object(600, 700, 10, 1, 100);
    poke->Load("files/sprites/poke.png");

    gameTime = 0;

    return true;
}

/**
Save current running Game
@return true on success, false on fail
*/
bool Game::SaveGame()
{
    ofstream savefile;
    savefile.open("save.txt");

    if(player==NULL)
    {
        popUp=new Popup("There is no game to save!", runTime);
        return false;
    }

    Vec v = player->getLastVec();

    savefile << player->getPosX() << " " << player->getPosY() << " " << v.x << " " << v.y;
    popUp = new Popup("Game saved successfully!", runTime);

    savefile.close();

    return true;
}

/**
Load the saved Game
@return true on success, false on fail
*/
bool Game::LoadGame()
{
    Sprite::Cleanup();
    Surface::Cleanup();

    if (!NewGame())
        return false;

    float x;
    float y;
    float a;
    float b;
    Vec v;
    ifstream loadfile;
    loadfile.open("save.txt");
    loadfile >> x >> y >> a >> b;

    //if(player == NULL) return false;
    player->setPos(x,y);
    loadfile.close();
    v.x=a;
    v.y=b;
    player->setLastVec(v);
    //fixa kanelbullar, urladdning, att man kan loada ett spel direkt
    return true;
}

/**
Update the game timers and Updates all Sprites
*/
void Game::Loop()
{
    runTime = SDL_GetTicks();
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

/**
Render all game components
*/
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
    popUp->DrawAll(surface, runTime);
    SDL_Flip(surface);
}

/**
Cleans up everything to make a smooth exit
*/
void Game::CleanUp()
{
    SDL_FreeSurface(surface);
    Sprite::Cleanup();
    Surface::Cleanup();

    TTF_Quit();
    SDL_Quit();
}
