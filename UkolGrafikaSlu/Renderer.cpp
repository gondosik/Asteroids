#include "Renderer.h"

Renderer* Renderer::rendererInstance = nullptr;

Renderer::Renderer() {}

Renderer* Renderer::getInstance() { return rendererInstance; }

Renderer* Renderer::init(SDL_Renderer* r, int w, int h) {
	rendererInstance = new Renderer();
	rendererInstance->renderer = r;
	rendererInstance->width = w;
	rendererInstance->height = h;
	return rendererInstance;
}

SDL_Renderer* Renderer::getRenderer() {
	return renderer;
}

int Renderer::getWidth() {
	return width;
}

int Renderer::getHeight() {
	return height;
}