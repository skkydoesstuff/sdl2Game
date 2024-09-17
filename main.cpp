#define SDL_MAIN_HANDLED
#include <SDL2/selfMade/levels.h>

int currentLevel = 1;

int main()
{
    init();

    while (true)
    {
        if (currentLevel == 1)
        {
            level1Loop();
            currentLevel++;
        }
        else if (currentLevel == 2)
        {
            level2Loop();
            currentLevel++;
        }
        else if (currentLevel == 3)
        {
            level3Loop();
            currentLevel++;
        }

        else
        {
            break;
        }
    }

    return 0;
}
