#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/selfMade/gameClasses.h>
#include <vector>

#define WIDTH 1920
#define HEIGHT 1080

bool fullscreen = false;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;
Player player;
bool running = true;
const int FPS = 60;
const int frameDelay = 1000/FPS;

inline bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed on SDL_INIT_EVERYTHING." << std::endl;
        return false;
    }

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    if (window == NULL || renderer == NULL) 
    {
        if (window == NULL)
            std::cout << "Could not make window" << std::endl;
        else
            std::cout << "Could not make renderer" << std::endl;
        return false;
    }

    return true;
}

void input() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            running = false;  // Quit the game
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_F11)
            {
                fullscreen = !fullscreen;
            }
        }

        player.handleEvent();  // Handle player input
    }

    if (fullscreen == true) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if (fullscreen == false) SDL_SetWindowFullscreen(window, 0);
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // Simple AABB collision detection
    if (a.x + a.w <= b.x) return false;  // a is to the left of b
    if (a.x >= b.x + b.w) return false;  // a is to the right of b
    if (a.y + a.h <= b.y) return false;  // a is above b
    if (a.y >= b.y + b.h) return false;  // a is below b
    return true;
}

bool isPlayerInAir(Player& player, std::vector<Platform>& platforms) {
    SDL_Rect playerFeet = player.rect;
    playerFeet.y += player.rect.h;  // Move the rect to the bottom of the player
    playerFeet.h -= player.rect.h-1;
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer, &playerFeet);

    for (Platform& platform : platforms) {
        if (checkCollision(playerFeet, platform.rect)) {
            return false;  // Player is on the ground (colliding with a platform)
        }
    }
    return true;  // Player is in the air (no collision detected)
}

void handlePlatCollision(Player& player, std::vector<Platform> platforms) {
    player.onGround = !isPlayerInAir(player, platforms);
    for (Platform platform : platforms)
    {
        SDL_Rect& a = player.rect;
        SDL_Rect& b = platform.rect;

        if (checkCollision(a, b)) {
            int overlapTop = (b.y + b.h) - a.y;
            int overlapBottom = (a.y + a.h) - b.y;
            int overlapLeft = (b.x + b.w) - a.x;
            int overlapRight = (a.x + a.w) - b.x;

            if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
                // Top collision
                player.rect.y = b.y + b.h;
                player.yVel = 0;  // Stop falling
                player.onGround = false;
                player.isJumping = true;
            } 
            else if (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
                // Bottom collision
                player.rect.y = b.y - player.rect.h;
                player.yVel = 0;  // Stop upward movement
                player.isJumping = false;  // Player has landed
                player.onGround = true;
            } 
            else if (overlapLeft < overlapRight) {
                // Left collision
                player.rect.x = b.x + b.w;
                player.xVel = 0;
                player.onGround = false;
            }
            else {
                // Right collision
                player.rect.x = b.x - player.rect.w;
                player.xVel = 0;
                player.onGround = false;
            }
        }
    }
}

void handleLavaCollision(Player& player, std::vector<LavaBlock> lavaBlocks, int startPosX, int startPosY) {
    for (LavaBlock lava : lavaBlocks)
    {
        SDL_Rect& a = player.rect;
        SDL_Rect& b = lava.rect;

        if (checkCollision(a, b)) {
            int overlapTop = (b.y + b.h) - a.y;
            int overlapBottom = (a.y + a.h) - b.y;
            int overlapLeft = (b.x + b.w) - a.x;
            int overlapRight = (a.x + a.w) - b.x;

            if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
                a.x = startPosX;
                a.y = startPosY;
            } else if (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
                a.x = startPosX;
                a.y = startPosY;
            } else if (overlapLeft < overlapRight) {
                a.x = startPosX;
                a.y = startPosY;
            } else {
                a.x = startPosX;
                a.y = startPosY;
            }
        }
    }
}

void handlePurplinCollision(Player& player, std::vector<purplin>& speedBlocks, float newSpeed) {
    for (purplin& speedBlock : speedBlocks) {
        SDL_Rect& a = player.rect;
        SDL_Rect& b = speedBlock.rect;

        if (checkCollision(a, b)) {
            if (speedBlock.on) {
                // Activate speed boost
                player.speedBoostActive = true;
                player.speed = newSpeed;
            } else {
                // Deactivate speed boost
                player.speedBoostActive = false;
                player.speed = player.originalSpeed;
            }
        }
    }
}


bool handleFinishCollision(Player& player, FinishBlock& FinishBlock) {
    SDL_Rect& a = player.rect;
    SDL_Rect& b = FinishBlock.rect;

    if (checkCollision(a, b)) {
        int overlapTop = (b.y + b.h) - a.y;
        int overlapBottom = (a.y + a.h) - b.y;
        int overlapLeft = (b.x + b.w) - a.x;
        int overlapRight = (a.x + a.w) - b.x;

        if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
            return true;
        } else if (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
            return true;
        } else if (overlapLeft < overlapRight) {
            return true;
        } else {
            return true;
        }
    }
    return false;
}
