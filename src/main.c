#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width;
int window_height;
uint32_t* color_buffer = NULL;


// se inicializa la ventana de sdl y se chequean si hay errores
bool initialize_window(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0){
        fprintf(stderr, "error iniciando SDL gato.\n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height,SDL_WINDOW_BORDERLESS);
    if (!window){
        fprintf(stderr, "error generando la la window gt");
        return false;
        
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        fprintf(stderr, "error creando el SDL rederer");
        return false;   
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}  
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

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
//recorre todos los pixeles de la ventana sdl y los pone de un solo color
void clear_color_buffer(uint32_t color){
    for (int y = 0; y < window_height; y++){
        for (int x =0; x <window_width; x++){
            color_buffer[(window_width * y) + x] = color;
        }
    };

}
void update(void){

}

void draw_grid(uint32_t color){
    for (int y = 0; y < window_height; y+=10)  {
        for (int x =0; x <window_width; x+=10)
        {
            color_buffer[(window_width * y)+x ] = color;
        }
    };

    /*for (int x = 0; x < window_width; x+=10)  {
        for (int y =0; y <window_height; y++)
        {
            color_buffer[(window_width * y)+x ] = color;
        }
    };*/
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(window_width * current_y) + current_x] = color;
        }
    }
}


void render(void){
    SDL_SetRenderDrawColor(renderer, 100,100,100,100);
    SDL_RenderClear(renderer);
    render_color_buffer();
    //clear_color_buffer(0xFFFFFFFF);
    draw_rectangle(300,400,100,350,0x553322);
    //draw_grid(0x00F0F0F0);
    SDL_RenderPresent(renderer);



}

void destroy_window(void){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
