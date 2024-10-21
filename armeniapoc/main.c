#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

void tela_inicial(ALLEGRO_DISPLAY* tela, ALLEGRO_FONT* font, ALLEGRO_BITMAP* area_central) {

    al_set_target_bitmap(al_get_backbuffer(tela));
    al_draw_text(font, al_map_rgb(255, 255, 255), 270, 70, 80, "Título do Jogo");
    al_draw_bitmap(area_central, 150, 200, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 295, 225, 80, "Iniciar");
    al_draw_bitmap(area_central, 150, 280, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 305, 305, 80, "Sair");
}

void movimentacao(ALLEGRO_EVENT evento, int pos_x, int pos_y) {

    if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
    else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
    else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
    else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

    if (pos_x >= 565) pos_x = 565;
    if (pos_x <= -30) pos_x = -30;
    if (pos_y >= 405) pos_y = 405;
    if (pos_y <= -20) pos_y = -20;


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
    ALLEGRO_BITMAP* coracao = al_load_bitmap("./coracao.png");
    ALLEGRO_BITMAP* botaosair = al_load_bitmap("./botao_sair.png");
    ALLEGRO_BITMAP* botaojogar = al_load_bitmap("./botao_jogar.png");
    ALLEGRO_BITMAP* cenarioRadio = al_load_bitmap("./cenario_radio.png");
    ALLEGRO_BITMAP* cenarioBar = al_load_bitmap("./cenario_bar.png");
    ALLEGRO_BITMAP* cenarioEscritorio = al_load_bitmap("./cenario_escritorio.png");
    ALLEGRO_BITMAP* cenarioFora = al_load_bitmap("./cenario_fora.png");
    ALLEGRO_BITMAP* cenarioGaragem = al_load_bitmap("./cenario_garagem.png");
    ALLEGRO_BITMAP* cenarioDormitorio = al_load_bitmap("./cenario_dormitorio.png");


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

    int estadoatual = 0; // Modificado: Inicializei com 0 em vez de 2 (tela inicial)
    bool jogando = true;

    ALLEGRO_EVENT evento; // Cria um evento

    while (jogando) { // Evento para fechar a janela 
        al_wait_for_event(lista_eventos, &evento); // Espera pelo evento, quando executado executa a linha debaixo 

        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // Evento de "apertar no xzinho da janela, finaliza o programa
            jogando = false; // Modificado: Usei false em vez de 0 para maior clareza
        }



        switch (estadoatual) {

        case 0:

            al_draw_bitmap(coracao, 295, 150, 0);
            al_draw_bitmap(botaojogar, 220, 220, 0); // 220 + 200, 220 + 80
            al_draw_bitmap(botaosair, 220, 270, 0); // 220 + 200, 270 + 80 

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouseX = evento.mouse.x;
                int mouseY = evento.mouse.y;

                if (mouseX >= 220 && mouseX <= 420 && mouseY >= 220 && mouseY <= 300)
                    estadoatual = 2;
                if (mouseX >= 220 && mouseX <= 420 && mouseY >= 270 && mouseY <= 350) {
                    jogando = false;
                }
            }

            break;
        case 1:
            break;
        case 2: //RADIO

            al_draw_bitmap(cenarioRadio, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;

            if (pos_x > LARGURA_TELA - 90 && pos_y < ALTURA_TELA - 250 && pos_y > ALTURA_TELA - 300)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = -50; pos_y = ALTURA_TELA / 2 - 50;
                        estadoatual = 3;
                    }
                }
            }

            break;


        case 3: //PARTE DE FORA
            al_draw_bitmap(cenarioFora, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;



            //ENTRA para cima
            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y < ALTURA_TELA - 490)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 50;
                        estadoatual = 4;
                    }
                }
            }
           
            //Entrar para baixo                                                    480 - 50
            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y > ALTURA_TELA - 90)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 530;
                        estadoatual = 5;
                    }
                }
            }

            //direita
            if (pos_x > LARGURA_TELA - 90 && pos_y < ALTURA_TELA - 250 && pos_y > ALTURA_TELA - 300)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = -50; pos_y = ALTURA_TELA / 2 - 50;
                        estadoatual = 6;
                    }
                }
            }

            //Entrar para a esquerda
            if (pos_x < LARGURA_TELA - 540 && pos_y < ALTURA_TELA - 250 && pos_y > ALTURA_TELA - 300)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA; pos_y = ALTURA_TELA / 2 - 50;
                        estadoatual = 2;
                    }
                }
            }

            break;


        case 4: //DORMITORIO
            al_draw_bitmap(cenarioDormitorio, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;

            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y > ALTURA_TELA - 90)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 530;
                        estadoatual = 3;
                    }
                }
            }
            break;
        case 5: //BAR
            al_draw_bitmap(cenarioBar, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;


            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y < ALTURA_TELA - 490) {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 50;
                        estadoatual = 3;
                    }

                }
            }
            break;
        case 6: //ESCRITORIO
            al_draw_bitmap(cenarioEscritorio, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;

            //ESQUERDA
            if (pos_x < LARGURA_TELA - 540 && pos_y < ALTURA_TELA - 250 && pos_y > ALTURA_TELA - 300)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA; pos_y = ALTURA_TELA / 2 - 50;
                        estadoatual = 3;
                    }
                }
            }

            //Entrar para baixo                                                    480 - 50
            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y > ALTURA_TELA - 90)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 530;
                        estadoatual = 7;
                    }
                }
            }


            break;



        case 7: //GARAGEM
            al_draw_bitmap(cenarioGaragem, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 565) pos_x = 565;
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 405) pos_y = 405;
            if (pos_y <= -20) pos_y = -20;


            //ENTRA para cima
            if (pos_x < LARGURA_TELA - 300 && pos_x > LARGURA_TELA - 350 && pos_y < ALTURA_TELA - 490)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 50;
                        estadoatual = 6;
                    }
                }
            }



            break;

            
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


        // Atualiza a tela

        al_flip_display();
    }

    al_destroy_bitmap(botaojogar);
    al_destroy_bitmap(botaosair);
    al_destroy_bitmap(coracao);
    al_destroy_bitmap(fantasma);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_event_queue(lista_eventos);
    al_destroy_bitmap(area_central);
    al_destroy_bitmap(cenarioDormitorio);
    al_destroy_bitmap(cenarioRadio);
    al_destroy_bitmap(cenarioFora);
    al_destroy_bitmap(cenarioGaragem);
    al_destroy_bitmap(cenarioBar);
    al_destroy_bitmap(cenarioEscritorio);


    return 0;
}
