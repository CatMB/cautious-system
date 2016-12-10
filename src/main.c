#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

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
    double player_scale = 1.0;
    SDL_Rect player_rect;
    player_rect.x = 0;
    player_rect.y = 0;
    player_rect.h = (int) (64 * player_scale);
    player_rect.w = (int) (64 * player_scale);
    // ----------
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.h = displayMode.h / 2;
    background_rect.w = displayMode.w / 2;
    // ----------
    const int player_w = (const int) (64 * player_scale);
    const int player_h = (const int) (64 * player_scale);

    SDL_Texture *player = IMG_LoadTexture(renderer, "res/hero/sprites/hero-1/player_1.png");
    SDL_Texture *background;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &background_rect);
    SDL_RenderCopy(renderer, player, NULL, &player_rect);
    SDL_RenderPresent(renderer);
    printf("ffffff v1.0\n");

    SDL_Texture *player_2 = IMG_LoadTexture(renderer, "res/hero/sprites/hero-1/player_2.png");
    SDL_Texture *player_3 = IMG_LoadTexture(renderer, "res/hero/sprites/hero-1/player_3.png");
    SDL_Texture *player_4 = IMG_LoadTexture(renderer, "res/hero/sprites/hero-1/player_4.png");

    SDL_Texture *textures_array[5] = {background, player, player_2, player_3, player_4};
    SDL_Rect *rect_array[2] = {&background_rect, &player_rect};
    int textureState_array[2] = {1, 1};
    int move_multiplier = 10;
    int currentHero;
    currentHero = 1;
    //Переменные для ограничения количества обновлений/сек
    int fps = 60;
	int minimumFrameTime = 1000 / fps;
    int frameTime;
    int lastFrameTime = 0;
    int deltaTime = 0;


    SDL_Event event;
    bool exit = false;
    while(!exit) {
    	frameTime = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textures_array[0], NULL, rect_array[0]);
            SDL_RenderCopy(renderer, textures_array[currentHero], NULL, rect_array[1]);
            SDL_RenderPresent(renderer);
            
            if(event.type == SDL_QUIT) {
                exit = true;
            }
            if(event.type == SDL_KEYDOWN) {
                SDL_Keycode key_down = event.key.keysym.sym;


                switch(key_down) {
                    case SDLK_w: // Up
                        rect_array[1]->y -= move_multiplier;
                        if(currentHero != 2) {
                            currentHero = 2;
                        }
                        break;
                    case SDLK_d: // Right
                        rect_array[1]->x += move_multiplier;
                        if(currentHero != 3) {
                            currentHero = 3;
                        }
                        break;
                    case SDLK_a: // Left
                        rect_array[1]->x -= move_multiplier;
                        if(currentHero != 4) {
                            currentHero = 4;
                        }
                        break;
                    case SDLK_s: // Down
                        rect_array[1]->y += move_multiplier;
                        if(currentHero != 1) {
                            currentHero = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
            
            SDL_PumpEvents();

        }
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
        
        if ((SDL_GetTicks() - frameTime) < minimumFrameTime) // Ограничение обновлений/сек
            SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
