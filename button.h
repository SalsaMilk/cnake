typedef struct {
    SDL_Rect rect;
    SDL_Rect textRect;
    SDL_Texture* texture;

    struct {
        BYTE r, g, b, a;
    } color;

    BYTE pressed;
} button;

button button_pause_resume, button_pause_settings, button_pause_exit;

// Button constructor; x coord is middle of the button for convenience
button button_new(int x, int y, const char* text, BYTE colorR, BYTE colorG, BYTE colorB, BYTE colorA) {
    button _button = {
            .color = { .r = colorR, .g = colorG, .b = colorB, .a = colorA },
            .rect = { .x = x, .y = y },
            .texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, text, white))
    };
    SDL_QueryTexture(_button.texture, NULL, NULL, &_button.textRect.w, &_button.textRect.h);
    _button.textRect.x = _button.rect.x - (_button.textRect.w >> 1);
    _button.textRect.y = _button.rect.y + (_button.textRect.h >> 1);
    _button.rect.w = _button.textRect.w + _button.textRect.h;
    _button.rect.h = _button.textRect.h << 1;
    _button.rect.x -= _button.rect.w >> 1;
    return _button;
}

// react on mouse click within button rectangle by setting 'pressed'
unsigned char button_pressed(button *btn, const SDL_Event *ev) {
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
           ev->button.x >= btn->rect.x &&
           ev->button.x <= (btn->rect.x + btn->rect.w) &&
           ev->button.y >= btn->rect.y &&
           ev->button.y <= (btn->rect.y + btn->rect.h)) {
            return 1;
        }
        else return 0;
    }
    else return 0;
}

// Draws a button's rectangle, text, and adds a white border
unsigned char button_draw(SDL_Renderer *r, button *btn) {
    SDL_SetRenderDrawColor(r, btn->color.r, btn->color.g, btn->color.b, btn->color.a);
    SDL_RenderFillRect(r, &btn->rect);

    SDL_SetRenderDrawColor(r, 255, 255, 255, 50);
    SDL_RenderDrawRect(r, &btn->rect);
    SDL_RenderCopy(r, btn->texture, NULL, &btn->textRect);
    if(btn->pressed) {
        btn->pressed = 0;
        return 1;
    }
    return 0;
}

void DestroyButton(button btn) {
    SDL_DestroyTexture(btn.texture);
}