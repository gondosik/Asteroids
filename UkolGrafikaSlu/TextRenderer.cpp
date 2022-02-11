#include "TextRenderer.h"

void TextRenderer::getTextAndRect(SDL_Renderer *renderer, int x, int y, std::string text,
	TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
	int text_width;
	int text_height;
	SDL_Surface *surface;
	SDL_Color textColor = { 255, 255, 255, 0 };

	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);
	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}


void TextRenderer::buttonProcessEvent(button_t *btn, const SDL_Event *ev) {
	if (ev->type == SDL_MOUSEBUTTONDOWN) {
		if (ev->button.button == SDL_BUTTON_LEFT &&
			ev->button.x >= btn->draw_rect.x &&
			ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
			ev->button.y >= btn->draw_rect.y &&
			ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
			btn->pressed = true;
		}
	}
}

bool TextRenderer::button(SDL_Renderer *r, button_t *btn) {
	SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
	SDL_RenderFillRect(r, &btn->draw_rect);

	if (btn->pressed) {
		btn->pressed = false;
		return true;
	}
	return false;
}