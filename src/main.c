#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "stdio.h"

int main() {
    // Создаем DisplayMode.
    SDL_DisplayMode displayMode;

    // Инициализируем все модули SDL.
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init error: %s", SDL_GetError());
        return 1;
    }

    // Получаем состояние нулевого монитора.
    int request = SDL_GetDesktopDisplayMode(0, &displayMode);

    // Создаем окно
    SDL_Window *win = SDL_CreateWindow("ffffff", 0, 0, displayMode.w / 2,
    displayMode.h / 2, SDL_WINDOW_SHOWN);
    if(win == NULL) {
        printf("SDL_CreateWindow error: %s", SDL_GetError());
        return 2;
    }

    // А теперь наконец создадим рендерер окна.
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("SDL_CreateRenderer error: %s", SDL_GetError());
        return 3;
    }

    // Создаем прямоугольники текстур.
    SDL_Rect player_rect;
    player_rect.x = 0;
    player_rect.y = 0;
    player_rect.h = 64;
    player_rect.w = 64;
    // ----------
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.h = displayMode.h / 2;
    background_rect.w = displayMode.w / 2;
    // ----------
    const int player_w = 64;
    const int player_h = 64;
    double player_scale = 1.0;

    SDL_Texture *player = IMG_LoadTexture(renderer, "../res/player-mock.png");
    SDL_Texture *background;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &background_rect);
    SDL_RenderCopy(renderer, player, NULL, &player_rect);
    SDL_RenderPresent(renderer);
    printf("ffffff v1.0\n");

    SDL_Texture *textures_array[2] = {background, player};
    SDL_Rect *rect_array[2] = {&background_rect, &player_rect};
    int textureState_array[2] = {1, 1};

    SDL_Event event;
    bool exit = false;
    while(!exit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                exit = true;
            }
            SDL_PumpEvents();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
