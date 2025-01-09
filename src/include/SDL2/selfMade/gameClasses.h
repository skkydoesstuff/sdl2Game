#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class Player
{
public:
    SDL_Rect rect;
    float xVel, yVel;
    bool isJumping;
    bool onGround;
    int currentSize, maxSize, minSize;
    float speed = 5.0f;
    float jumpHeight = 12.0f;
    bool speedBoostActive = false;
    float originalSpeed = 5.0f;

    Player() {
        rect.x = 50;
        rect.y = 950;
        rect.w = 50;
        rect.h = 50;
        xVel = 0;
        yVel = 0;
        isJumping = false;
        speed = 5.0f;
        jumpHeight = 12.0f;
        speedBoostActive = false;
        originalSpeed = 5.0f;
    }

    void handleEvent() {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        xVel = 0;  // Reset horizontal velocity before checking input

        // Check if both left and right inputs are being pressed
        bool movingRight = state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];
        bool movingLeft = state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];

        // Only apply movement if one direction is pressed, not both
        if (movingRight && !movingLeft) {
            xVel = speed;
        } 
        else if (movingLeft && !movingRight) {
            xVel = -speed;
        }
        // If both are pressed, xVel remains 0

        // Handle jumping
        if (onGround && (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])) {
            yVel = -jumpHeight;
            isJumping = true;
            onGround = false;
        }

        // Handle diagonal jumps only if we're not pressing both left and right
        if (!movingLeft || !movingRight) {
            if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_SPACE] && onGround) {   
                xVel = speed;
                yVel = -jumpHeight;
                isJumping = true;
                onGround = false;
            }

            if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_SPACE] && onGround) {   
                xVel = -speed;
                yVel = -jumpHeight;
                isJumping = true;
                onGround = false;
            }
        }
    }


    void update() {
        rect.x += xVel;

        // Apply gravity if the player is not on the ground
        if (!onGround) {
            yVel += 0.5f;  // Simulate gravity
        } else {
            yVel = 0;  // Stop vertical movement when on the ground
        }

        rect.y += yVel;
    }


    void render(SDL_Renderer* renderer, int r, int g, int b) {
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);  // White color
        SDL_RenderFillRect(renderer, &rect);
    }
};

class Platform {
public:
    SDL_Rect rect;
    int red,green,blue;

    Platform(int x, int y, int w, int h, int r, int g, int b) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        red = r;
        green = g;
        blue = b;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, red, green, blue,255);  // Green color
        SDL_RenderFillRect(renderer, &rect);
    }
};

class FinishBlock {
public:
    SDL_Rect rect;

    FinishBlock(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0,255,0,255);
        SDL_RenderFillRect(renderer, &rect);
    }
};

class LavaBlock {
public:
    SDL_Rect rect;

    LavaBlock(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderFillRect(renderer, &rect);
    }
};

class purplin {
public:
    SDL_Rect rect;
    bool on;

    purplin(int x, int y, int w, int h, bool onb) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        on = onb;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255,0,255,255);
        SDL_RenderFillRect(renderer, &rect);
    }
};
