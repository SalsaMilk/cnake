button button_pause_resume, button_pause_settings, button_pause_exit;
void menu_pause() {
    BYTE pressingEscape = 1;

    button_draw(renderer, &button_pause_settings);
    button_draw(renderer, &button_pause_resume);
    button_draw(renderer, &button_pause_exit);

    while(!button_pressed(&button_pause_resume, &event)) {
        SDL_PollEvent(&event);

        if (button_pressed(&button_pause_exit, &event) || event.type == SDL_QUIT) {
            gaming = 0;
            return;
        }

        if (button_pressed(&button_pause_settings, &event)) {
            printf("Settings");
        }

        if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            pressingEscape = 0;
        else if (!pressingEscape && event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            return;


        SDL_RenderPresent(renderer);

        SDL_Delay(1000/30);
    }
}

SDL_Texture* youDiedTexture;
SDL_Rect youDiedRect;
button button_death_retry, button_death_exit;
void menu_death() {
    SDL_RenderCopy(renderer, youDiedTexture, NULL, &youDiedRect);
    button_draw(renderer, &button_death_retry);
    button_draw(renderer, &button_death_exit);

    while(1) {
        SDL_PollEvent(&event);

        if (button_pressed(&button_death_exit, &event) || event.type == SDL_QUIT) {
            gaming = 0;
            return;
        }

        if (button_pressed(&button_death_retry, &event) || event.key.keysym.scancode == SDL_SCANCODE_RETURN)
            return;

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/30);
    }
}