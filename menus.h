void menu_pause() {

    BYTE pressingEscape = 1;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 40);

    button_draw(renderer, &button_pause_settings);
    button_draw(renderer, &button_pause_resume);
    button_draw(renderer, &button_pause_exit);

    while(!button_pressed(&button_pause_resume, &event)) {
        SDL_PollEvent(&event);

        if (button_pressed(&button_pause_exit, &event)) {
            gaming = 0;
            break;
        }

        if (button_pressed(&button_pause_settings, &event)) {
            printf("Settings");
        }

        if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            pressingEscape = 0;
        else if (!pressingEscape && event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            break;


        SDL_RenderPresent(renderer);

        SDL_Delay(1000/30);
    }
}

void menu_death() {
    while(1) {
    }
}