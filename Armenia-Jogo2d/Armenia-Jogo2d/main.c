#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/timer.h>
#include <string.h>
#include <allegro5/allegro_primitives.h>
#define ALLEGRO_BPS_TO_SECS(x) (1.0 / (x))

void tela_inicial(ALLEGRO_DISPLAY* tela, ALLEGRO_FONT* font, ALLEGRO_BITMAP* area_central) {

    al_set_target_bitmap(al_get_backbuffer(tela));
    al_draw_text(font, al_map_rgb(255, 255, 255), 270, 70, 80, "T�tulo do Jogo");
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
bool verificar_posicao(int x, int y, int x_alvo, int y_alvo, int tolerancia) {
    printf("x: %d, y: %d, x_alvo: %d, y_alvo: %d, tolerancia: %d\n", x, y, x_alvo, y_alvo, tolerancia);
    if (x >= x_alvo - tolerancia && x <= x_alvo + tolerancia && y >= y_alvo - tolerancia && y <= y_alvo + tolerancia) {
        printf("Posição correta!\n");
        return true;
    }
    else {
        printf("Posição incorreta!\n");
        return false;
    }
}


int posicao_inicial_x;
int posicao_inicial_y;

typedef struct {
    float x, y;
    int largura, altura, ax, ay;
    bool sendo_arrastada;
    ALLEGRO_BITMAP* bitmap;
} Imagem;



int main() {
    // INICIA��O
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_set_new_window_title("Primeira Tela");
    al_install_mouse();
    ALLEGRO_BITMAP* botao_sair = NULL, * area_central = 0;
    int sair = 0;

    const int LARGURA_TELA = 1280;
    const int ALTURA_TELA = 700;
    ALLEGRO_DISPLAY* tela = al_create_display(LARGURA_TELA, ALTURA_TELA); // Cria um display com um tamanho especificado w, h
    al_set_system_mouse_cursor(tela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    ALLEGRO_FONT* font = al_create_builtin_font(); // Adiciona uma fonte, nesse caso a padr�o.
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // FPS
    ALLEGRO_TIMER* timer2 = al_create_timer(1.0);
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
    ALLEGRO_BITMAP* palavraCruzada = al_load_bitmap("./cruzada2.png");
    ALLEGRO_BITMAP* g_linear = al_load_bitmap("./linear.png");
    ALLEGRO_BITMAP* g_expo = al_load_bitmap("./exponencial.png");
    ALLEGRO_BITMAP* g_quadra = al_load_bitmap("./quadratica.png");
    ALLEGRO_BITMAP* g_log = al_load_bitmap("./logaritimica.png");
    ALLEGRO_BITMAP* res_lin = al_load_bitmap("./res_lin.png");
    ALLEGRO_BITMAP* res_expo = al_load_bitmap("./res_expo.png");
    ALLEGRO_BITMAP* res_quad = al_load_bitmap("./res_quad.png");
    ALLEGRO_BITMAP* res_log = al_load_bitmap("./res_log.png");
    ALLEGRO_BITMAP* qua_resp = al_load_bitmap("./local_resp.png");


    area_central = al_create_bitmap(340, 55);
    botao_sair = al_create_bitmap(340, 55);
    ALLEGRO_EVENT_QUEUE* lista_eventos = al_create_event_queue(); // Cria uma lista de eventos 

    al_register_event_source(lista_eventos, al_get_display_event_source(tela)); // Recupera a fonte de evento associada a janela.
    al_register_event_source(lista_eventos, al_get_timer_event_source(timer));
    al_register_event_source(lista_eventos, al_get_timer_event_source(timer2));
    al_register_event_source(lista_eventos, al_get_keyboard_event_source());
    al_register_event_source(lista_eventos, al_get_mouse_event_source());
    al_start_timer(timer);
    al_start_timer(timer2);// Precisa dela para registrar os eventos

    bool arrastando;
    float frame = 0.f;
    int pos_x = 100, pos_y = 100;
    int na_area_central = 0;

    int estadoatual = 9; // Modificado: Inicializei com 0 em vez de 2 (tela inicial)
    bool jogando = true;

    struct Posicao {
        int x;
        int y;
        int largura;
        int altura;
        ALLEGRO_BITMAP* dados;
    };
    Imagem imagens[4];
    struct Posicao linear = { 1030,550,115,40 };
    struct Posicao expo = { 680,550,93,36 };
    struct Posicao quadra = { 80,550,178,38 };
    struct Posicao log = { 400,550,127,35 };
    struct Posicao resp = { 80,420,180,51 };
    imagens[0].bitmap = al_load_bitmap("./res_quad.png");
    imagens[0].x = 80; imagens[0].y = 550; imagens[0].largura = 178; imagens[0].altura = 38;
    imagens[0].ax = 680; imagens[0].ay = 420;

    imagens[1].bitmap = al_load_bitmap("./res_log.png");
    imagens[1].x = 400; imagens[1].y = 550; imagens[1].largura = 127; imagens[1].altura = 35;
    imagens[1].ax = 1030;

    imagens[2].bitmap = al_load_bitmap("./res_expo.png");
    imagens[2].x = 680; imagens[2].y = 550; imagens[2].largura = 93; imagens[2].altura = 36;
    imagens[2].ax = 400;

    imagens[3].bitmap = al_load_bitmap("./res_lin.png");
    imagens[3].x = 1030; imagens[3].y = 550; imagens[3].largura = 115; imagens[3].altura = 40;
    imagens[3].ax = 80;

    int mouseX, mouseY;
    Imagem* imagem_arrastada = NULL;
    ALLEGRO_EVENT evento; // Cria um evento
    int seg = 0, min = 0;
    while (jogando) { // Evento para fechar a janela 
        al_wait_for_event(lista_eventos, &evento); // Espera pelo evento, quando executado executa a linha debaixo 

        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);



        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // Evento de "apertar no xzinho da janela, finaliza o programa
            jogando = false; // Modificado: Usei false em vez de 0 para maior clareza
        }


        int posicao_inicial_x;
        int posicao_inicial_y;
        switch (estadoatual) {

        case 9:
            switch (evento.type) {
                bool imagem_sendo_arrastada = false;
                int indice_imagem_arrastada = -1;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;

                for (int i = 0; i < 4; i++) {
                    if (mouseX >= imagens[i].x && mouseX <= imagens[i].x + imagens[i].largura &&
                        mouseY >= imagens[i].y && mouseY <= imagens[i].y + imagens[i].altura) {
                        imagem_arrastada = &imagens[i];
                        posicao_inicial_x = mouseX;
                        posicao_inicial_y = mouseY;
                        imagem_sendo_arrastada = true;
            indice_imagem_arrastada = i;
            break;

                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (imagem_arrastada != NULL) {
                    int pontos = 0;
                    for (int i = 0; i < 4; i++) {
                        printf("imagem_arrastada: %p\n", imagem_arrastada);
                        // Verifica se a imagem atual é a que está sendo arrastada
                            
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[0].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagem_arrastada->ax + 2;
                                imagem_arrastada->y = imagem_arrastada->ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[1].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[1].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[2].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[2].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[3].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[3].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                
                                
                            }
                            if (pontos >= 4) {
                                estadoatual = 2;
                            }

                    }

                    // Resetar o estado após processar todas as imagens
                    imagem_arrastada = NULL;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                if (imagem_arrastada) {
                    // Atualizar a posição da imagem arrastada
                    imagem_arrastada->x = evento.mouse.x;
                    imagem_arrastada->y = evento.mouse.y;
                }
                break;
            }

            // Desenhar as imagens
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), 500, 25, 0, "Coloque os nomes nas funções corretas");
            al_draw_bitmap(qua_resp, resp.x, resp.y, 0); // linear
            al_draw_bitmap(qua_resp, resp.x + 320, resp.y, 0); // exponencial
            al_draw_bitmap(qua_resp, resp.x + 600, resp.y, 0); // quadratica
            al_draw_bitmap(qua_resp, resp.x + 950, resp.y, 0); // logari
            al_draw_bitmap(g_linear, 20, 50, 0);//300,306
            al_draw_bitmap(g_expo, 330, 50, 0);//311,403
            al_draw_bitmap(g_quadra, 640, 50, 0); //263
            al_draw_bitmap(g_log, 910, 50, 0);
            for (int i = 0; i < 4; i++) {

                al_draw_bitmap(imagens[i].bitmap, imagens[i].x, imagens[i].y, 0);
            }
            al_flip_display();

            break;
        case 0:
            al_draw_bitmap(coracao, 600, 450, 0); //70
            al_draw_bitmap(botaojogar, 530, 520, 0); // 220 + 200, 220 + 80
            al_draw_bitmap(botaosair, 530, 570, 0); // 220 + 200, 270 + 80 

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouseX = evento.mouse.x;
                int mouseY = evento.mouse.y;


                if (mouseX >= 530 && mouseX <= 730 && mouseY >= 520 && mouseY <= 600)
                    estadoatual = 2;
                al_draw_bitmap(fantasma, 530, 510, 0);
                if (mouseX >= 530 && mouseX <= 730 && mouseY >= 570 && mouseY <= 650)
                    jogando = false;

            }

            break;
        case 1://Puzzle 1
            if (evento.type == ALLEGRO_EVENT_TIMER)
            {
                if (evento.timer.source == timer2) {
                    seg++;
                    if (seg == 60)
                    {
                        min++;
                        seg = 0;
                    }
                }
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 100, 230, 0, "Vamos fazer um teste para ver se vc é capaz de entrar para");
            al_draw_text(font, al_map_rgb(255, 255, 255), 110, 240, 0, " para a nossa facilidade e ajudar com a nossa pesquisa.");

            if (seg > 10) {
                al_stop_timer(timer2);
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 10, 0, "Resolva essa palavra cruzada para entrar no programa");

                /*al_draw_bitmap(palavraCruzada, 90, 50, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 400, 0, "1) Exterminio em massa das pessoas"); // 10 - Holocausto
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 410, 0, "2) Movimento Político Alemão"); // 7 - Nazismo
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 420, 0, "3) País derrotado na Guerra"); // 8 - Alemanha
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 430, 0, "4) Vencedora da Guerra I"); // 10 - Inglaterra
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 440, 0, "5) Líder nazista"); // 6 - Hitler
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 450, 0, "6) Conseqência da Guerra"); // 10 - Destruição
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 460, 0, "7) Conseqência da Guerra"); // 6 - Mortes
                al_draw_text(font, al_map_rgb(0, 0, 0), 100, 470, 0, "8) Perseguidos pelos nazistas"); // 6 - Judeus
                */
            }

            break;
        case 2: //RADIO

            al_draw_bitmap(cenarioRadio, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }
            //640 480 1280 900
            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 825; // -75
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

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
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
                break;
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

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
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

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
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
            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
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

            if (pos_x > LARGURA_TELA - 90 && pos_y < ALTURA_TELA - 250 && pos_y > ALTURA_TELA - 300)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = -50; pos_y = ALTURA_TELA / 2 - 50;
                        estadoatual = 8;
                    }
                }
            }

            break;



        case 7: //GARAGEM
            al_draw_bitmap(cenarioGaragem, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
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

        case 8:

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "Fim!");


            break;
        }







        // Colorimos o bitmap correspondente ao ret�ngulo central,
        // com a cor condicionada ao conte�do da flag na_area_central
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
    al_destroy_timer(timer);


    return 0;
}