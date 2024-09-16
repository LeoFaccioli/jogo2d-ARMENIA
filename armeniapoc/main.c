#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>


int main() {
    //INICIAÇÃO
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_set_new_window_title("Criação da POC");
    //Imagem


    ALLEGRO_DISPLAY* tela = al_create_display(640, 480); //Cria um display com um tamanho especificado w, h
    ALLEGRO_FONT* font = al_create_builtin_font(); //Adiciona uma fonte, nesse caso a padrão.
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); //FPS
    ALLEGRO_BITMAP* fantasma = al_load_bitmap("./fantasma.bmp");

    ALLEGRO_EVENT_QUEUE* lista_eventos = al_create_event_queue(); //Cria uma lista de eventos 

    al_register_event_source(lista_eventos, al_get_display_event_source(tela)); //Recupera a fonte de evento associada a janela.
    al_register_event_source(lista_eventos, al_get_timer_event_source(timer));
    al_register_event_source(lista_eventos, al_get_keyboard_event_source());
    al_start_timer(timer); //Precisa dela para registrar os eventos

    float frame = 0.f;
    int pos_x = 100, pos_y = 100;

    while (true) { //Evento para fechar a janela 
        ALLEGRO_EVENT event; //Cria um evento
        al_wait_for_event(lista_eventos, &event); //Espera pelo evento, quando executado executa a linha debaixo 
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //Evento de "apertar no xzinho da janela, finaliza o programa
            break; // fechar
        
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) 
            pos_x += 10;
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) 
            pos_x -= 10;
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
            pos_y -= 10;
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            pos_y += 10;
        
       
        if (pos_x >= 565)
            pos_x = 565;
        if (pos_x <= -30)
            pos_x = -30;
        if (pos_y >= 405)
            pos_y = 405;
        if (pos_y <= -20)
            pos_y = -20;

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(fantasma, pos_x, pos_y, 0);
        al_draw_text(font, al_map_rgb(0, 0, 0), 0, 0, 0, "isso e um teste.");
        al_flip_display();
    }

    al_destroy_bitmap(fantasma);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_event_queue(lista_eventos);

    return 0;
}