#ifndef FONT_H
#define FONT_H

#include <SDL/SDL_ttf.h>

using namespace std;

class Font
{
    public:
        Font();
        virtual ~Font();
        static void Load();

        static TTF_Font* ARIAL;
        static TTF_Font* BITLIM;

    protected:
    private:
};

#endif // FONT_H
