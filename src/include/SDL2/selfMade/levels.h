#include <SDL2/selfMade/levelUtils.h>

int startPosX = 50;
int startPosY = 950;

void level1Loop()
{ 
    Uint32 frameStart;  // Use Uint32 for frameStart to hold SDL ticks
    Uint32 frameTime;   // Uint32 is a better match for SDL_GetTicks()

    // make finish block
    //
    FinishBlock finish((WIDTH/2)-50, 930, 100, 50);

    // make walls
    ///
    makePlat(0,1070,1920,10, 47,47,47);
    makePlat(0, 0, 10, 1080, 47,47,47);
    makePlat(1910, 0, 10, 1080, 47,47,47);
    makePlat(0, 0, 1920, 10, 47,47,47);

    // make platforms to jump on
    //
    makePlat((WIDTH/2)-100, 980, 200, 10, 0,0,255);

    player.isJumping = false;
    player.onGround = false;

    while (running) {
        if(!window) break;

        frameStart = SDL_GetTicks(); 
        input();
        player.update();
        handlePlatCollision(player, platforms);

        if(handleFinishCollision(player, finish) == true)
        {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player.render(renderer, 255,0,0);
        
        finish.render(renderer);

        for (Platform platform : platforms)
        {
            platform.render(renderer);
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    platforms.clear();
    lavaBlocks.clear();
    purplinBlocks.clear();
}

void level2Loop()
{
    Uint32 frameStart;  // Use Uint32 for frameStart to hold SDL ticks
    Uint32 frameTime;   // Uint32 is a better match for SDL_GetTicks()

    player.rect.x = 50;
    player.rect.y = 950;

    // make finish block
    //
    FinishBlock finish(1550,970, 100,100);

    // make walls
    ///
    makePlat(0,1070,1920,10, 47,47,47);
    makePlat(0, 0, 10, 1080, 47,47,47);
    makePlat(1910, 0, 10, 1080, 47,47,47);
    makePlat(0, 0, 1920, 10, 47,47,47);

    // make platforms to jump on
    //
    makePlat(300,970, 100,100, 0,0,255);
    makePlat(650,970, 100,100, 0,0,255);
    makePlat(1000,970, 100,100, 0,0,255);
    makePlat(1350,970, 100,100, 0,0,255);

    // make lava blocks
    //
    makeLava(400, 1020, 250, 50);
    makeLava(750, 1020, 250, 50);
    makeLava(1100, 1020, 250, 50);

    player.isJumping = false;
    player.onGround = false;

    while (running) {
        if(!window) break;
        frameStart = SDL_GetTicks(); 
        input();
        player.update();
        handlePlatCollision(player, platforms);
        handleLavaCollision(player, lavaBlocks, startPosX, startPosY);

        if(handleFinishCollision(player, finish) == true)
        {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player.render(renderer, 255,0,0);
        
        finish.render(renderer);

        for (Platform platform : platforms)
        {
            platform.render(renderer);
        }

        for (LavaBlock lava : lavaBlocks)
        {
            lava.render(renderer);
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    platforms.clear();
    lavaBlocks.clear();
    purplinBlocks.clear();
}

void level3Loop()
{
    Uint32 frameStart;  // Use Uint32 for frameStart to hold SDL ticks
    Uint32 frameTime;   // Uint32 is a better match for SDL_GetTicks()

    player.rect.x = 50;
    player.rect.y = 950;

    // make finish block
    //
    FinishBlock finish(1810,680, 100,100);

    // make walls
    ///
    makePlat(0,1070,1920,10, 47,47,47);
    makePlat(0, 0, 10, 1080, 47,47,47);
    makePlat(1910, 0, 10, 1080, 47,47,47);
    makePlat(0, 0, 1920, 10, 47,47,47);

    // make platforms to jump on
    //
    makePlat(200,980, 1710,10, 0,0,255);
    makePlat(10,880, 1710,10, 0,0,255);
    makePlat(200,780, 1710,10, 0,0,255);

    // make speed blocks
    //
    makePurplin(200,890,10,90, true);
    makePurplin(200,790,10,90, false);
    
    player.isJumping = false;
    player.onGround = false;

    while (running) {
        if(!window) break;
        frameStart = SDL_GetTicks(); 
        input();
        player.update();
        handlePlatCollision(player, platforms);
        handleLavaCollision(player, lavaBlocks, startPosX, startPosY);
        handlePurplinCollision(player, purplinBlocks, 10.0f);

        if(handleFinishCollision(player, finish) == true)
        {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player.render(renderer, 255,0,0);
        
        finish.render(renderer);

        for (Platform platform : platforms)
        {
            platform.render(renderer);
        }

        for (LavaBlock lava : lavaBlocks)
        {
            lava.render(renderer);
        }

        for (purplin speed : purplinBlocks)
        {
            speed.render(renderer);
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    platforms.clear();
    lavaBlocks.clear();
    purplinBlocks.clear();
}

void level4Loop()
{
    Uint32 frameStart;  // Use Uint32 for frameStart to hold SDL ticks
    Uint32 frameTime;   // Uint32 is a better match for SDL_GetTicks()

    player.rect.x = 50;
    player.rect.y = 950;

    // make finish block
    //
    FinishBlock finish(1810,680, 100,100);

    makeWalls();

    // make platforms to jump on
    //
    makePlat(200,1810,100,100,0,0,255);

    // make speed blocks
    //
    makePurplin(200,890,10,90, true);
    makePurplin(200,790,10,90, false);
    
    player.isJumping = false;
    player.onGround = false;

    while (running) {
        if(!window) break;
        frameStart = SDL_GetTicks(); 
        input();
        player.update();
        handlePlatCollision(player, platforms);
        handleLavaCollision(player, lavaBlocks, startPosX, startPosY);
        handlePurplinCollision(player, purplinBlocks, 10.0f);

        if(handleFinishCollision(player, finish) == true)
        {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player.render(renderer, 255,0,0);
        
        finish.render(renderer);

        for (Platform platform : platforms)
        {
            platform.render(renderer);
        }

        for (LavaBlock lava : lavaBlocks)
        {
            lava.render(renderer);
        }

        for (purplin speed : purplinBlocks)
        {
            speed.render(renderer);
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    platforms.clear();
    lavaBlocks.clear();
    purplinBlocks.clear();
}