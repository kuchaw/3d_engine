
#include "display.h"
bool is_running = false;

// se inicializa la ventana de sdl y se chequean si hay errores

// el color buffer define un espacio de memoria en el que se van a guardar los datos de los colores de los pixeles
//buffer_texture crea la textura que despues era utilizada para dibujar en la pantalla
void setup(){
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t)* window_width*window_height);

    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}
//evalua si se apreta la letra escape, si si, se cierra
void process_input(void){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }

}
// la funcion render coor buffer toma loz pixeles en el buffer de colores y los subre a una textura sdl en la que luego se van 
// a mostrar en pantalla


void update(void){
}


void render(void){
    SDL_SetRenderDrawColor(renderer, 100,100,100,100);
    SDL_RenderClear(renderer);
    render_color_buffer();
    //clear_color_buffer(0xFFFFFFFF);
    draw_rectangle(500,200,200,350,0xFFFFFF);
    //draw_grid(0x00F0F0F0);
    SDL_RenderPresent(renderer);



}

int main(){
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}
