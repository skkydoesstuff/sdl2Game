#include <SDL2/selfMade/screen.h>

std::vector<Platform> platforms;
std::vector<LavaBlock> lavaBlocks;
std::vector<purplin> purplinBlocks;

void makePlat(float x, float y, float w, float h, int r, int g, int b)
{
    Platform plat(x, y, w, h, r,g,b);
    platforms.push_back(plat);
}

void makeLava(float x, float y, float w, float h)
{
    LavaBlock lava(x,y,w,h);
    lavaBlocks.push_back(lava);
}

void makePurplin(float x, float y, float w, float h, bool on)
{
    purplin speed(x,y,w,h, on);
    purplinBlocks.push_back(speed);
}

void makeWalls()
{
    makePlat(0,1070,1920,10, 47,47,47);
    makePlat(0, 0, 10, 1080, 47,47,47);
    makePlat(1910, 0, 10, 1080, 47,47,47);
    makePlat(0, 0, 1920, 10, 47,47,47);
}