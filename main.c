#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#define HEAD (*(snake))
#define BOARD_WIDTH 25
#define BOARD_HEIGHT 20
#define KEY event.key.keysym.scancode

typedef char BYTE;
typedef unsigned char UBYTE;

int main(int argc, char *argv[]) {
    SDL_Point direction = {0, 0};
    UBYTE length = 1;
    SDL_Rect* snake = calloc(400, sizeof(SDL_Rect));
    SDL_Rect apple = {220, 220, 20, 20};
    srand(time(NULL));

    // SDL_Init returns 0 on success
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    //TTF_Init();

    //TTF_Font* font = TTF_OpenFont("fonts/bebas.ttf", 25);

    SDL_Window* win = SDL_CreateWindow("cnake",
                                       SDL_WINDOWPOS_CENTERED,  // x
                                       SDL_WINDOWPOS_CENTERED,  // y
                                       22*BOARD_WIDTH, 22*BOARD_HEIGHT, 0);   // w, h, flag

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, render_flags);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_CreateRGBSurface(0, 20, 20, 1, 0, 0, 0, 0));

    SDL_Rect bg = {0, 0, 20, 20};

    // Bind the texture to the head
    SDL_QueryTexture(texture, NULL, NULL, &HEAD.w, &HEAD.h);

    BYTE shouldClose = 0;
    
    // annimation loop
    while (!shouldClose) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    shouldClose = 1;
                    break;

                case SDL_KEYDOWN:
                    // Key presses
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            if (direction.y != 1) {
                                direction.y = -1;
                                direction.x = 0;
                            }
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            if (direction.x != 1) {
                                direction.y = 0;
                                direction.x = -1;
                            }
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            if (direction.y != -1) {
                                direction.y = 1;
                                direction.x = 0;
                            }
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            if (direction.x != -1) {
                                direction.y = 0;
                                direction.x = 1;
                            }
                            break;
                        case SDL_SCANCODE_C: // Cheat codes (:
                            length++;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            shouldClose++;
                            break;
                        default:
                            break;
                    }
            }
        }
        direction = direction;

        if (!memcmp(&HEAD, &apple, sizeof(SDL_Rect))) {
            length++;
            apple.x = (rand() % BOARD_WIDTH)  * 22;
            apple.y = (rand() % BOARD_HEIGHT) * 22;
        }

        SDL_Rect prev = HEAD, next;

        HEAD.x += direction.x * 22;
        HEAD.y += direction.y * 22;

        int i = 1;
        for (; i < length; i++) {
            if (!memcmp(&HEAD, (snake + i), sizeof(SDL_Rect)))
                shouldClose = 1;
            next        = snake[i];
            snake[i]    = prev;
            prev        = next;
        }

        // boundaries
        if ((HEAD.x + HEAD.w > BOARD_WIDTH*22) || (HEAD.x < 0) || (HEAD.y + HEAD.h > BOARD_HEIGHT*22) || (HEAD.y < 0))
            shouldClose++;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // clear the screen
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);

        // Draw background
        bg.y = 0;
        for (BYTE j = 0; j < BOARD_HEIGHT; j++) {
            bg.x = 0;
            for (BYTE k = 0; k < BOARD_WIDTH; k++) {
                SDL_RenderFillRect(renderer, &bg);
                bg.x += 22;
            }
            bg.y += 22;
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Render the apple
        SDL_RenderFillRect(renderer, &apple);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Render entire snake with a single sexy SDL function
        SDL_RenderFillRects( renderer, snake, length);

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    //TTF_CloseFont(font);


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);


    //TTF_Quit();
    SDL_Quit();

    return 0;
}