#include "../include/Font.h"

using namespace std;

TTF_Font* Font::ARIAL = NULL; /** Arial font 12pt, after Font::Load() has been called else NULL */
TTF_Font* Font::BITLIM = NULL; /** 8Bitlim font 20pt, after Font::Load() has been called else NULL */

/**
Default constructor for Font
*/
Font::Font()
{
    //def ctor
}

/**
Loads fonts from file
*/
void Font::Load()
{
    Font::ARIAL = TTF_OpenFont("files/fonts/arial.ttf", 12);
    Font::BITLIM = TTF_OpenFont("files/fonts/8bitlim.ttf", 20);
}

/**
Default destructor for Font
*/
Font::~Font()
{
    //dtor
}
