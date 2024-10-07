#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

void tela_inicial(ALLEGRO_DISPLAY* tela, ALLEGRO_FONT* font, ALLEGRO_BITMAP* area_central) {
    al_set_target_bitmap(al_get_backbuffer(tela));
    al_draw_text(font, al_map_rgb(255, 255, 255), 270, 70, 0, "Título do Jogo"); // Modificado: Troquei 80 por 0
    al_draw_bitmap(area_central, 150, 200, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 295, 225, 0, "Iniciar"); // Modificado: Troquei 80 por 0
    al_draw_bitmap(area_central, 150, 280, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 305, 305, 0, "Sair"); // Modificado: Troquei 80 por 0
}

int main() {
    // INICIAÇÃO
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_set_new_window_title("Primeira Tela");
    al_install_mouse();
    ALLEGRO_BITMAP* botao_sair = NULL, * area_central = 0;
    int sair = 0;

    // Imagem
    struct Imagem {
        int x;
        int y;
        int largura;
        int altura;
    };

    const int LARGURA_TELA = 640;
    const int ALTURA_TELA = 480;
    ALLEGRO_DISPLAY* tela = al_create_display(LARGURA_TELA, ALTURA_TELA); // Cria um display com um tamanho especificado w, h
    al_set_system_mouse_cursor(tela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    ALLEGRO_FONT* font = al_create_builtin_font(); // Adiciona uma fonte, nesse caso a padrão.
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // FPS
    ALLEGRO_BITMAP* fantasma = al_load_bitmap("./fantasma.bmp");

    area_central = al_create_bitmap(340, 55);
    botao_sair = al_create_bitmap(340, 55);
    ALLEGRO_EVENT_QUEUE* lista_eventos = al_create_event_queue(); // Cria uma lista de eventos 

    al_register_event_source(lista_eventos, al_get_display_event_source(tela)); // Recupera a fonte de evento associada a janela.
    al_register_event_source(lista_eventos, al_get_timer_event_source(timer));
    al_register_event_source(lista_eventos, al_get_keyboard_event_source());
    al_register_event_source(lista_eventos, al_get_mouse_event_source());
    al_start_timer(timer); // Precisa dela para registrar os eventos

    float frame = 0.f;
    int pos_x = 100, pos_y = 100;
    int na_area_central = 0;

    int estadoatual = 2; // Modificado: Inicializei com 0 em vez de 2 (tela inicial)
    bool jogando = true;

    ALLEGRO_EVENT evento; // Cria um evento

    while (jogando) { // Evento para fechar a janela 
        al_wait_for_event(lista_eventos, &evento); // Espera pelo evento, quando executado executa a linha debaixo 

        while (!al_is_event_queue_empty(lista_eventos)) {
            ALLEGRO_MOUSE_STATE state;
            al_get_mouse_state(&state);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // Evento de "apertar no xzinho da janela, finaliza o programa
                jogando = false; // Modificado: Usei false em vez de 0 para maior clareza
            }

            else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) { // Modificado: Adicionei verificação para o tipo de evento
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;
            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;
        }

        // Colorimos o bitmap correspondente ao retângulo central,
        // com a cor condicionada ao conteúdo da flag na_area_central
        /*
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_set_target_bitmap(area_central);
        if (!na_area_central) {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }
        */
        switch (estadoatual) {
        case 0:
            tela_inicial(tela, font, area_central); // Modificado: Chamando a função para a tela inicial
            // if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(area_central) / 2 &&
                    evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(area_central) / 2 &&
                    evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(area_central) / 2 &&
                    evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(area_central) / 2)
                    na_area_central = 1;
                else
                    na_area_central = 0;
            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(area_central) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(area_central) - 10) {
                    estadoatual = 1;
                }
            }
            break;

        case 1:
            // Criar Tela do puzzle (mas agora está o fantasma)
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            break;

        case 2: // teste // cria outra tela
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), 320, 240, ALLEGRO_ALIGN_CENTRE, "Aperte a tecla E");

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_E) {
                estadoatual = 1;
            }
            break;

        default:
            break;
        }

        // Atualiza a tela
        al_flip_display();
    }

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();

    al_destroy_bitmap(fantasma);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_event_queue(lista_eventos);
    al_destroy_bitmap(area_central);
    al_destroy_bitmap(botao_sair);

    return 0;
}