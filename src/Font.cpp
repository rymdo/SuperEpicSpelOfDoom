#include "../include/Font.h"

using namespace std;

TTF_Font* Font::ARIAL = NULL;
TTF_Font* Font::BITLIM = NULL;

Font::Font()
{
    //ctor
}

void Font::Load()
{
    Font::ARIAL = TTF_OpenFont("files/fonts/arial.ttf", 12);
    Font::BITLIM = TTF_OpenFont("files/fonts/8bitlim.ttf", 20);
}

Font::~Font()
{
    //dtor
}
