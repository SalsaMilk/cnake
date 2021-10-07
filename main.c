#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <memory.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#define HEAD snake[0]

#define SPEED 10.0f
#define SCALE 20
#define GAP 1
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20
#define WINDOW_WIDTH (unitConst * (BOARD_WIDTH + 2))
#define WINDOW_HEIGHT (unitConst * (BOARD_HEIGHT + 2))

SDL_Color white = {255, 255, 255};
SDL_Renderer* renderer;
TTF_Font *font, *fontBig, *fontHuge;
SDL_Event event;
BYTE gaming = 1;

#include "button.h"
#include "menus.h"

SDL_Point direction = {0, 0};
int score, length, unitConst = SCALE + GAP;
SDL_Rect* snake;
char* scoreCounter;
SDL_Rect apple;

void setup() {
    gaming = 1;
    length = 1;
    score = 0;
    snake = calloc(BOARD_WIDTH * BOARD_HEIGHT, sizeof(SDL_Rect));
    apple.x = unitConst * BOARD_WIDTH/2;
    apple.y = unitConst * BOARD_HEIGHT/2;
    scoreCounter = "Score: 000";
}

int main(int argc, char *argv[]) {
    apple.w = SCALE; apple.h = SCALE;
    srand(time(NULL));

    // SDL_Init returns 0 on success
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    TTF_Init();

    SDL_Window* win = SDL_CreateWindow("cnake",
                                       SDL_WINDOWPOS_CENTERED, // x
                                       SDL_WINDOWPOS_CENTERED, // y
                                       WINDOW_WIDTH,  // w
                                       WINDOW_HEIGHT, // h
                                       0); // flag

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(win, -1, render_flags);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    font = TTF_OpenFont("..\\fonts\\envy.ttf", SCALE);
    fontBig = TTF_OpenFont("..\\fonts\\envy.ttf", SCALE * 2);
    fontHuge = TTF_OpenFont("..\\fonts\\envy.ttf", SCALE * 10);

    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, scoreCounter, white));
    SDL_Texture* appleTexture = IMG_LoadTexture(renderer, "..\\images\\apple.png");
    SDL_Texture* goldAppleTexture = IMG_LoadTexture(renderer, "..\\images\\apple_gold.png");

    SDL_Rect scoreRect = {0, 0, 0, 0};
    SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);

    // Pause menu buttons
    button_pause_resume = button_new(WINDOW_WIDTH >> 1, 2 * SCALE, "Resume", 20, 20, 20, 150);
    button_pause_settings = button_new(WINDOW_WIDTH >> 1, 5 * SCALE, "Settings", 20, 20, 20, 150);
    button_pause_exit = button_new(WINDOW_WIDTH >> 1, 8 * SCALE, "Exit", 60, 20, 20, 150);

    SDL_Rect bg = {SCALE, SCALE + 1, SCALE, SCALE};

    START:

    setup();

    HEAD.x = unitConst; HEAD.y = unitConst;
    HEAD.w = SCALE; HEAD.h = SCALE;

    // Small chance to generate a "golden apple" which adds 5 to the length
    BYTE goldenApple = 0;

    // main game loop
    while (gaming) {
        //BYTE* keyBuf = malloc(8); // 1 - up  |  2 - down  |  3 - left  |  4 - right
        //BYTE keysInBuf = 0;

        // Events management
        if (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    gaming = 0;
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
                            length += 10;
                            break;
                        case SDL_SCANCODE_P:
                        case SDL_SCANCODE_ESCAPE:
                            menu_pause();
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        // Randomly place new apple when
        if (!memcmp(&HEAD, &apple, 8)) {
            length += 1 + (goldenApple << 2);
            score += 1 + (goldenApple << 2);
            goldenApple = 1 * (rand() % 100 < 5);
            for (;;) { // Ensure apple doesn't spawn in snake
                BYTE appleInSnake = 0;
                apple.x = (rand() % BOARD_WIDTH) * unitConst + unitConst;
                apple.y = (rand() % BOARD_HEIGHT) * unitConst + unitConst;
                for (int i = 0; i < length; i++) {
                    if(!memcmp(&apple, (snake + i), 8)) {
                        appleInSnake = 1;
                        break;
                    }
                }
                if (!appleInSnake) break;
            }
            // Sexy way to handle the score counter
            itoa(score, scoreCounter + 9 - (score >= 10) - (score >= 100), 10);
            scoreTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, scoreCounter, white));
        }

        SDL_Rect prev = HEAD, next;

        HEAD.x += direction.x * unitConst;
        HEAD.y += direction.y * unitConst;

        // Make snake follow head
        for (int i = 1; i < length; i++) {
            if (!memcmp(&HEAD, (snake + i), 8))
                gaming = 0;
            next        = snake[i];
            snake[i]    = prev;
            prev        = next;
        }

        // boundaries
        if ((HEAD.x + HEAD.w > (BOARD_WIDTH + 1) * unitConst) ||
            (HEAD.x < unitConst) ||
            (HEAD.y + HEAD.h > (BOARD_HEIGHT + 1) * unitConst) ||
            (HEAD.y < unitConst))
            gaming = 0;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // clear the screen
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);

        // Draw background
        if(GAP) {
            bg.y = unitConst + 1;
            for (BYTE j = 0; j < BOARD_HEIGHT; j++) {
                bg.x = unitConst;
                for (BYTE k = 0; k < BOARD_WIDTH; k++) {
                    SDL_RenderFillRect(renderer, &bg);
                    bg.x += unitConst;
                }
                bg.y += unitConst;
            }
        }
        else {
            bg.w = BOARD_WIDTH * SCALE;
            bg.h = BOARD_HEIGHT * SCALE;
            SDL_RenderFillRect(renderer, &bg);
        }

        SDL_SetRenderDrawColor(renderer, 255, 215 * goldenApple, 0, 255);

        // Render the apple
        if(!goldenApple)
            SDL_RenderCopy(renderer, appleTexture, NULL, &apple);
        else SDL_RenderCopy(renderer, goldAppleTexture, NULL, &apple);

        SDL_SetRenderDrawColor(renderer, 255 * !gaming, 255, 255, 255);

        // Render entire snake with a single sexy SDL function
        SDL_RenderFillRects(renderer, snake, length);

        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(100/(SPEED/10.0f));
    }

    // Free font stuff
    TTF_CloseFont(font);
    TTF_CloseFont(fontBig);

    // Free menu buttons
    DestroyButton(button_pause_resume);
    DestroyButton(button_pause_settings);
    DestroyButton(button_pause_exit);

    // Free game stuff
    SDL_DestroyTexture(appleTexture);
    SDL_DestroyTexture(goldAppleTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);


    TTF_Quit();
    SDL_Quit();

    return 0;
}
