#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/timer.h>
#include <string.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <ctype.h>
#define ALLEGRO_BPS_TO_SECS(x) (1.0 / (x))
#define GRID_SIZE 13
#define GRID_SIZE2 10// Tamanho do grid 5x5
#define CELL_SIZE 30 // Tamanho de cada célula

void gearscreen(ALLEGRO_FONT* fonte, int engrenagens, int x, int y) {
    al_draw_filled_circle(x + 25, y - 6, 10, al_map_rgb(238, 173, 45)); 
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), x + 20 + 1, y - 9, 0, "%d", engrenagens); // Exibe o número de engrenagens
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), x + 20, y - 10, 0, "%d", engrenagens); // Exibe o número de engrenagens
}




char palavras_respostas[GRID_SIZE2][GRID_SIZE] = {
    {'X', 'X', 'N', 'A', 'Z', 'I', 'S', 'M', 'O', 'X', 'X', 'D', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'N', 'X', 'X', 'X', 'X', 'X', 'E', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'G', 'X', 'X', 'X', 'J', 'X', 'S', 'X'},
    {'X', 'X', 'X', 'H', 'O', 'L', 'O', 'C', 'A', 'U', 'S', 'T', 'O'},
    {'X', 'X', 'X', 'X', 'X', 'A', 'X', 'X', 'X', 'D', 'X', 'R', 'X'},
    {'X', 'X', 'M', 'O', 'R', 'T', 'E', 'S', 'X', 'E', 'X', 'U', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'E', 'X', 'X', 'X', 'U', 'X', 'I', 'X'},
    {'H', 'I', 'T', 'L', 'E', 'R', 'X', 'X', 'X', 'S', 'X', 'C', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'R', 'X', 'X', 'X', 'X', 'X', 'A', 'X'},
    {'X', 'A', 'L', 'E', 'M', 'A', 'N', 'H', 'A', 'X', 'X', 'O', 'X'}
};
// 1 - Holocausto, 2 - nazismo, 3 - alemanha, 4 - inglaterra, 5 - hitler, 6 - destruicao , 7 - mortes, 8 - judeus 
// 
// 1 - Extermínio em massa de pessoas, 2 - Movimento Político, 3 - País derrotada na Guerra, 4 - Vencedor da Guerra I
// 5 - Lider Nazista, 6 - Consequência da Guerra, 7 - Consequência da Guerra, 8 - Perseguidos pelos Nazistas

char resposta_usuario[GRID_SIZE2][GRID_SIZE] = { 0 }; // Respostas do jogador

int posicao_atual_row = 0;  // Linha da célula ativa
int posicao_atual_col = 0;  // Coluna da célula ativa

// Função para desenhar o grid
void desenhar_grid(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font) {
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpa a tela com cor branca
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 300, ALLEGRO_ALIGN_CENTRE, "1 - Extermínio em massa de pessoas (10 - Hor)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 310, ALLEGRO_ALIGN_CENTRE, "2 - Movimento Político (7 - Hor)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 320, ALLEGRO_ALIGN_CENTRE, "3 - País derrotada na Guerra (8 - Hor)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 330, ALLEGRO_ALIGN_CENTRE, "4 - Vencedor da Guerra I (10 - Vert)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 340, ALLEGRO_ALIGN_CENTRE, "5 - Lider Nazista (6 - Hor)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 350, ALLEGRO_ALIGN_CENTRE, "6 - Consequência da Guerra (10 - Vert)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1030, 360, ALLEGRO_ALIGN_CENTRE, "7 - Consequência da Guerra (6 - Hor)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1050, 370, ALLEGRO_ALIGN_CENTRE, "8 - Perseguidos pelos Nazistas (6 - Vert - Começa 3 )");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 650, 50, ALLEGRO_ALIGN_CENTRE, "Complete essa palavra cruzada para entrar no programa");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 650, 70, ALLEGRO_ALIGN_CENTRE, "Coloque um X nas posições que não possuem letras");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 340, 255, ALLEGRO_ALIGN_CENTRE, "1 - (Começa no 4 quadrado)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 340, 165, ALLEGRO_ALIGN_CENTRE, "2 - (Começa no 3 quadrado)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 340, 435, ALLEGRO_ALIGN_CENTRE, "3 - (Começa no 2 quadrado)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 610, 140, ALLEGRO_ALIGN_CENTRE, "4");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 430, 375, ALLEGRO_ALIGN_CENTRE, "5 - ");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 790, 140, ALLEGRO_ALIGN_CENTRE, "6");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 340, 315, ALLEGRO_ALIGN_CENTRE, "7 - (Começa no 3 quadrado)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 730, 140, ALLEGRO_ALIGN_CENTRE, "8");
    
    

    // Calcular o deslocamento para centralizar o grid
    int largura_tela = al_get_display_width(display);
    int altura_tela = al_get_display_height(display);

    int largura_grid = GRID_SIZE * CELL_SIZE;  // Largura total do grid
    int altura_grid = GRID_SIZE * CELL_SIZE;   // Altura total do grid

    // Calcular as coordenadas para o canto superior esquerdo do grid
    int x_inicio = (largura_tela - largura_grid) / 2;
    int y_inicio = (altura_tela - altura_grid) / 2;

    // Desenha o grid 5x5
    for (int i = 0; i < GRID_SIZE2; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            // Verifica se a célula é a ativa
            ALLEGRO_COLOR cor = (i == posicao_atual_row && j == posicao_atual_col) ? al_map_rgb(200, 200, 255) : al_map_rgb(255, 255, 255);

            // Destaca a célula ativa com uma cor diferente (azul claro)
            if (i == posicao_atual_row && j == posicao_atual_col) {
                cor = al_map_rgb(200, 200, 255); // Célula ativa (azul claro)
            }
            // Verifica se a célula está correta ou incorreta
            else if (resposta_usuario[i][j] == '\0') {
                cor = al_map_rgb(255, 255, 255); // Célula vazia (branca)
            }
            else if (resposta_usuario[i][j] == palavras_respostas[i][j]) {
                cor = al_map_rgb(200, 255, 200); // Célula correta (verde clara)
            }
            else {
                cor = al_map_rgb(255, 200, 200); // Célula errada (vermelha)
            }

            // Desenha o retângulo da célula
            
            al_draw_filled_rectangle(x_inicio + j * CELL_SIZE, y_inicio + i * CELL_SIZE, x_inicio + (j + 1) * CELL_SIZE, y_inicio + (i + 1) * CELL_SIZE, cor);
            al_draw_rectangle(x_inicio + j * CELL_SIZE, y_inicio + i * CELL_SIZE, x_inicio + (j + 1) * CELL_SIZE, y_inicio + (i + 1) * CELL_SIZE, al_map_rgb(0, 0, 0), 2);

            // Exibe as letras digitadas
            if (resposta_usuario[i][j] != 0) {
                al_draw_textf(font, al_map_rgb(0, 0, 0), x_inicio + j * CELL_SIZE + CELL_SIZE / 2, y_inicio + i * CELL_SIZE + CELL_SIZE / 2, ALLEGRO_ALIGN_CENTRE, "%c", resposta_usuario[i][j]);
            }
        }
    }

    al_flip_display(); // Atualiza a tela
}

// Função para processar os inputs do teclado
void processar_input(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        // Se pressionou tecla de seta (movimentação)
        if (event.keyboard.keycode == ALLEGRO_KEY_UP && posicao_atual_row > 0) {
            posicao_atual_row--;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && posicao_atual_row < GRID_SIZE2 - 1) {
            posicao_atual_row++;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && posicao_atual_col > 0) {
            posicao_atual_col--;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && posicao_atual_col < GRID_SIZE - 1) {
            posicao_atual_col++;
        }

        // Se pressionou uma tecla de A-Z (entrada de letras)
        if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
            // Converte o código da tecla para o caractere correspondente
            char letra = (char)(event.keyboard.keycode - ALLEGRO_KEY_A + 'A');

            // Armazena a letra na matriz de respostas
            resposta_usuario[posicao_atual_row][posicao_atual_col] = letra;
        }

        // Se pressionou backspace (para apagar)
        else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
            resposta_usuario[posicao_atual_row][posicao_atual_col] = '\0'; // Apaga a letra
        }
    }
}

// Função para verificar se o jogador preencheu as palavras corretamente
int verificar_respostas() {
    // Verificar se todas as células estão preenchidas corretamente
    for (int i = 0; i < GRID_SIZE2; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            // Se a célula preenchida pelo jogador não corresponder à palavra correta
            if (resposta_usuario[i][j] != palavras_respostas[i][j]) {
                return 0; // Se houver uma letra errada, retorna 0 (falso)
            }
        }
    }
    return 1; // Se todas as letras estiverem corretas, retorna 1 (verdadeiro)
}


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
    al_init_font_addon();
    al_init_ttf_addon();
    al_set_new_window_title("Enigma Game");

    al_install_mouse();
    ALLEGRO_BITMAP* botao_sair = NULL, * area_central = 0;
    int sair = 0;
    if (!al_init_primitives_addon()) {
        printf("Falha na inicialização dos primitives.\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        printf("Falha na inicialização da fonte.\n");
        return -1;
    }

    if (!al_init_ttf_addon()) {
        printf("Falha na inicialização do TTF.\n");
        return -1;
    }



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
    ALLEGRO_BITMAP* seta = al_load_bitmap("./seta.png");
    ALLEGRO_BITMAP* botaoplay = al_load_bitmap("./botaoplay.png");
    ALLEGRO_BITMAP* botaoquit = al_load_bitmap("./botaoquit.png");
    ALLEGRO_BITMAP* titulogame = al_load_bitmap("./titulogame.png");
    ALLEGRO_BITMAP* fundoinicial = al_load_bitmap("./fundoinicial.png");
    ALLEGRO_BITMAP* gearimg = al_load_bitmap("./engrenagem.png");
    ALLEGRO_BITMAP* greg = al_load_bitmap("./greg.png");
    ALLEGRO_BITMAP* grace = al_load_bitmap("./grace.png");
    ALLEGRO_BITMAP* joao = al_load_bitmap("./joao.png");
    ALLEGRO_BITMAP* caixadialogo = al_load_bitmap("./caixadialogo.png");





    al_set_display_icon(tela, gearimg);


    int w_play = al_get_bitmap_width(botaoplay);
    int h_play = al_get_bitmap_height(botaoplay);
    int w_quit = al_get_bitmap_width(botaoquit);
    int h_quit = al_get_bitmap_height(botaoquit);


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

    bool passou_todos = false;
    bool entrou_dir = true;
    bool entrou_esq = false;
    bool arrastando;
    bool passou_1 = false;
    bool passou_2 = false;
    float frame = 0.f;
    int pos_x = -50, pos_y = ALTURA_TELA/2+40;
    int na_area_central = 0;
    
    
    int gears = 0;
    bool jogotabuada = true;
    int dialogojoao = 0;

    srand(time(NULL));

    int rodada = 1;
    int tempo_limite = 10;
    int pontos = 0;
    char entrada[10] = "";
    int posicao_entrada = 0;

    int num1, num2, resposta_correta;
    double tempo_inicial = 0;

    double tempo_restante = tempo_limite - (al_get_time() - tempo_inicial);

    




    int estadoatual = 13; // Modificado: Inicializei com 0 em vez de 2 (tela inicial)
    bool jogando = true;

    struct Posicao {
        int x;
        int y;
        int largura;
        int altura;
        ALLEGRO_BITMAP* dados;
    };
    Imagem imagens[8];
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

    imagens[7].bitmap = al_load_bitmap("./res_quad.png");
    imagens[7].x = 80; imagens[7].y = 550; imagens[7].largura = 178; imagens[7].altura = 38;
    imagens[7].ax = 680; imagens[7].ay = 420;

    imagens[5].bitmap = al_load_bitmap("./res_log.png");
    imagens[5].x = 400; imagens[5].y = 550; imagens[5].largura = 127; imagens[5].altura = 35;
    imagens[5].ax = 1030;

    imagens[4].bitmap = al_load_bitmap("./res_expo.png");
    imagens[4].x = 680; imagens[4].y = 550; imagens[4].largura = 93; imagens[4].altura = 36;
    imagens[4].ax = 400;

    imagens[6].bitmap = al_load_bitmap("./res_lin.png");
    imagens[6].x = 1030; imagens[6].y = 550; imagens[6].largura = 115; imagens[6].altura = 40;
    imagens[6].ax = 80;

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

                for (int i = 4; i < 8; i++) {
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
                    for (int i = 4; i < 8; i++) {
                        printf("imagem_arrastada: %p\n", imagem_arrastada);
                        // Verifica se a imagem atual é a que está sendo arrastada
                            
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[7].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagem_arrastada->ax + 2;
                                imagem_arrastada->y = imagem_arrastada->ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[5].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[5].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[4].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[4].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                break;
                                
                            }
                            if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[6].ax, imagens[0].ay, 20)) {
                                pontos+=1;
                                imagem_arrastada->x = imagens[6].ax + 2;
                                imagem_arrastada->y = imagens[0].ay + 5;
                                printf("%d", pontos);
                                
                                
                            }
                            if (pontos >= 4) {
                                pos_x = LARGURA_TELA - 770;
                                pos_y = ALTURA_TELA - 500;
                                estadoatual = 6;
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
            for (int i = 4; i < 8; i++) {

                al_draw_bitmap(imagens[i].bitmap, imagens[i].x, imagens[i].y, 0);
            }
            al_flip_display();

            break;
        case 10:
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
                            pontos += 1;
                            imagem_arrastada->x = imagem_arrastada->ax + 2;
                            imagem_arrastada->y = imagem_arrastada->ay + 5;
                            printf("%d", pontos);
                            break;

                        }
                        if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[1].ax, imagens[0].ay, 20)) {
                            pontos += 1;
                            imagem_arrastada->x = imagens[1].ax + 2;
                            imagem_arrastada->y = imagens[0].ay + 5;
                            printf("%d", pontos);
                            break;

                        }
                        if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[2].ax, imagens[0].ay, 20)) {
                            pontos += 1;
                            imagem_arrastada->x = imagens[2].ax + 2;
                            imagem_arrastada->y = imagens[0].ay + 5;
                            printf("%d", pontos);
                            break;

                        }
                        if (verificar_posicao(imagem_arrastada->x, imagem_arrastada->y, imagens[3].ax, imagens[0].ay, 20)) {
                            pontos += 1;
                            imagem_arrastada->x = imagens[3].ax + 2;
                            imagem_arrastada->y = imagens[0].ay + 5;
                            printf("%d", pontos);


                        }
                        if (pontos >= 4) {
                            passou_todos = true;
                            pos_x = LARGURA_TELA - 1030;
                            pos_y = ALTURA_TELA - 430;
                            estadoatual = 5;
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
        case 11:
            
            processar_input(evento);
            desenhar_grid(tela, font);

            // Verifica se o jogador preencheu tudo corretamente
            if (verificar_respostas()) {
                al_draw_textf(font, al_map_rgb(0, 0, 0), 650, 500, ALLEGRO_ALIGN_CENTRE, "Parabéns! Você acertou!");
                al_flip_display(); // Atualiza a tela
                al_rest(2.0); // Espera 2 segundos antes de fechar
                estadoatual = 1;
            }



            break;
        case 0:
            al_draw_bitmap(fundoinicial, 0, 0, 0); //70
            al_draw_bitmap(titulogame, 400, 100, 0); // 220 + 200, 220 + 80
            al_draw_bitmap(botaoplay, 493, 395, 0); // 220 + 200, 220 + 80
            al_draw_bitmap(botaoquit, 530, 530, 0); // 220 + 200, 270 + 80 

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouseX = evento.mouse.x;
                int mouseY = evento.mouse.y;


                if (mouseX >= 493 && mouseX <= 493 + w_play && mouseY >= 395 && mouseY <= 395 + h_play)
                    estadoatual = 11;
                if (mouseX >= 530 && mouseX <= 530 + w_quit && mouseY >= 530 && mouseY <= 530 + h_quit)
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
            al_draw_text(font, al_map_rgb(255, 255, 255), 470, 320, 0, "Parabéns por passar no nosso programa");
            al_draw_text(font, al_map_rgb(255, 255, 255), 480, 330, 0, "seja bem vindo a nossa facilidade.");

            if (seg > 10) 
                estadoatual = 3;

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
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;

            //direita
            if (pos_x > LARGURA_TELA - 90 && pos_y < ALTURA_TELA - 400 && pos_y > ALTURA_TELA - 450)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = -50; pos_y = ALTURA_TELA / 2 + 40;
                        estadoatual = 3;
                    }
                }
            }

            break;


        case 3: //PARTE DE FORA

            al_draw_bitmap(cenarioFora, 0, 0, 0);
            al_draw_bitmap(joao, 200, 300, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);

            if (dialogojoao == 0 && pos_x >= 120 && pos_x <= 254 && pos_y >= 250 && pos_y <= 405) {
                al_draw_filled_rectangle(148, 262, 306, 281, al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), 150, 270, ALLEGRO_ALIGN_LEFT, "Aperte E para falar");


                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_E) {

                    estadoatual = 12;
                    
                }
            }

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;

            
           
            //ENTRA para cima casa  meio
            if(passou_todos){
                al_draw_bitmap(seta, LARGURA_TELA - 595, ALTURA_TELA - 710, 0);
                if (pos_x < LARGURA_TELA - 600 && pos_x > LARGURA_TELA - 650 && pos_y < ALTURA_TELA - 690)
                {
                    al_draw_filled_rectangle(LARGURA_TELA - 600, ALTURA_TELA - 670, LARGURA_TELA - 720, ALTURA_TELA - 710,al_map_rgb(0,0,0));
                    al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA - 655, ALTURA_TELA - 685, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                    if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                        if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                            al_clear_to_color(al_map_rgb(0, 0, 0));
                            pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 50;
                            estadoatual = 8;
                        }
                    }
                }
            }
            //ENTRA para cima casa  direita
            if(!entrou_dir){
                al_draw_bitmap(seta, LARGURA_TELA - 275, ALTURA_TELA - 690, 0);
            }
            if (pos_x < LARGURA_TELA - 270 && pos_x > LARGURA_TELA - 320 && pos_y < ALTURA_TELA - 640 && pos_y > ALTURA_TELA - 680)
            {
                al_draw_filled_rectangle(LARGURA_TELA - 290, ALTURA_TELA - 660, LARGURA_TELA - 400, ALTURA_TELA - 690, al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA - 345, ALTURA_TELA - 675, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 280; pos_y = ALTURA_TELA - 120;
                        entrou_dir = true;
                        estadoatual = 5;
                    }
                }
            }

            //ENTRA para cima casa  esq
            if (!entrou_esq) {
                al_draw_bitmap(seta, LARGURA_TELA - 935, ALTURA_TELA - 590, 0);
            }
            if (pos_x < LARGURA_TELA - 940 && pos_x > LARGURA_TELA - 990 && pos_y < ALTURA_TELA - 540 && pos_y > ALTURA_TELA - 580)
            {//110, 25
                al_draw_filled_rectangle(LARGURA_TELA - 940, ALTURA_TELA - 540, LARGURA_TELA - 1120, ALTURA_TELA - 575, al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA - 1050, ALTURA_TELA - 565, ALLEGRO_ALIGN_CENTRE, "E para entrar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 300; pos_y = ALTURA_TELA - 125;
                        entrou_esq = true;
                        estadoatual = 6;
                    }
                }
            }

            break;


        case 4: //DORMITORIO
            al_draw_bitmap(cenarioDormitorio, 0, 0, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;

            //Entrar para baixo                                                    480 - 50
            if (pos_x < LARGURA_TELA - 700 && pos_x > LARGURA_TELA - 750 && pos_y > ALTURA_TELA - 90)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para sair");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA / 2 - 50; pos_y = ALTURA_TELA - 530;
                        estadoatual = 5;
                    }
                }
            }
            break;
        case 5: //BAR
            al_draw_bitmap(cenarioBar, 0, 0, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;

            if (!passou_2)
                al_draw_bitmap(seta, LARGURA_TELA - 1000, ALTURA_TELA - 460, 0);
            if (pos_x < LARGURA_TELA - 1000 && pos_x > LARGURA_TELA - 1050 && pos_y > ALTURA_TELA - 450 && pos_y < ALTURA_TELA - 400)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para consertar");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 300; pos_y = ALTURA_TELA - 630;
                        passou_todos = true;
                        passou_2 = true;
                        estadoatual = 10;
                        gears += 1;
                    }
                }
            }
            //Entrar para baixo                                                    480 - 50
            if (pos_x < LARGURA_TELA - 250 && pos_x > LARGURA_TELA - 300 && pos_y > ALTURA_TELA - 120)
            {
                al_draw_filled_rectangle(LARGURA_TELA - 270, ALTURA_TELA - 110, LARGURA_TELA - 460, ALTURA_TELA - 145, al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA - 410, ALTURA_TELA - 135, ALLEGRO_ALIGN_CENTRE, "E para sair");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 300; pos_y = ALTURA_TELA - 630;
                        estadoatual = 3;
                    }
                }
            }
            break;
        case 6: //ESCRITORIO
            al_draw_bitmap(cenarioEscritorio, 0, 0, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;


            //Entrar para baixo                                                    480 - 50
            if (pos_x < LARGURA_TELA - 280 && pos_x > LARGURA_TELA - 320 && pos_y > ALTURA_TELA - 120)
            {
                al_draw_filled_rectangle(LARGURA_TELA - 300, ALTURA_TELA - 110, LARGURA_TELA - 480, ALTURA_TELA - 145, al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA - 410, ALTURA_TELA - 135, ALLEGRO_ALIGN_CENTRE, "E para sair");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 960; pos_y = ALTURA_TELA - 530;
                        estadoatual = 3;
                    }
                }
            }

            //teste
            if (!passou_1)
                al_draw_bitmap(seta, LARGURA_TELA - 760, ALTURA_TELA - 560, 0);
            if (pos_x < LARGURA_TELA - 750 && pos_x > LARGURA_TELA - 800 && pos_y > ALTURA_TELA - 550 && pos_y < ALTURA_TELA - 500)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "E para resolver");
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (evento.keyboard.keycode == ALLEGRO_KEY_E) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        pos_x = LARGURA_TELA - 960; pos_y = ALTURA_TELA - 530;
                        passou_1 = true;
                        entrou_dir = false;
                        estadoatual = 9;
                        gears += 1;
                    }
                }
            }

            break;



        case 7: //GARAGEM
            al_draw_bitmap(cenarioGaragem, 0, 0, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);

            if (evento.type != ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) pos_x += 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) pos_x -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) pos_y -= 10;
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) pos_y += 10;

            }

            if (pos_x >= 1205) pos_x = 1205;// - 75
            if (pos_x <= -30) pos_x = -30;
            if (pos_y >= 825) pos_y = 625; // -75
            if (pos_y <= -20) pos_y = -20;


            //ENTRA para cima
            if (pos_x < LARGURA_TELA - 700 && pos_x > LARGURA_TELA - 750 && pos_y < ALTURA_TELA - 720)
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



            break;

        case 8:

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 600, 320, ALLEGRO_ALIGN_CENTRE, "Fim! Obrigado por jogar nosso jogo");
            
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
            if (seg >= 10) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 200, ALLEGRO_ALIGN_CENTRE, "Créditos");
                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 220, ALLEGRO_ALIGN_CENTRE, "Danilo!");
                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 240, ALLEGRO_ALIGN_CENTRE, "Leonardo Faccioli!");
                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 260, ALLEGRO_ALIGN_CENTRE, "Pedro Henrique!");

                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 320, ALLEGRO_ALIGN_CENTRE, "Menção Honrosa");
                al_draw_text(font, al_map_rgb(255, 255, 255), 600, 340, ALLEGRO_ALIGN_CENTRE, "Matheus Paixão");
            }
            
            break;
        case 12:
            al_draw_bitmap(cenarioFora, 0, 0, 0);
            al_draw_bitmap(joao, 200, 300, 0);
            al_draw_bitmap(fantasma, pos_x, pos_y, 0);
            al_draw_bitmap(gearimg, 27, 10, 0);
            gearscreen(font, gears, 50, 50);

            if (dialogojoao == 0) {
                al_draw_bitmap(caixadialogo, 264, 498, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 270, 505, ALLEGRO_ALIGN_LEFT, "João:");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 580, ALLEGRO_ALIGN_LEFT, "Pode me ajudar a recuperar algumas engrenagens?");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 590, ALLEGRO_ALIGN_LEFT, "Estou tentando refazer a Máquina de Turing!");
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 640, ALLEGRO_ALIGN_LEFT, "Pressione [ESPAÇO] para continuar");
                
            }

            bool tecla_espaco_pressionada;
 
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_SPACE && !tecla_espaco_pressionada) {
                dialogojoao++;  
                tecla_espaco_pressionada = true;  
            }

            if (evento.type == ALLEGRO_EVENT_KEY_UP && evento.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                tecla_espaco_pressionada = false;  
            }

            if (dialogojoao == 1) {
                al_draw_bitmap(cenarioFora, 0, 0, 0);
                al_draw_bitmap(joao, 200, 300, 0);
                al_draw_bitmap(fantasma, pos_x, pos_y, 0);
                al_draw_bitmap(gearimg, 27, 10, 0);
                gearscreen(font, gears, 50, 50);
                al_draw_bitmap(caixadialogo, 264, 498, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 270, 505, ALLEGRO_ALIGN_LEFT, "João:");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 590, ALLEGRO_ALIGN_LEFT, "É um presente para o meu neto que ama criptografia.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 640, ALLEGRO_ALIGN_LEFT, "Pressione [ESPAÇO] para continuar");
            }


            if (dialogojoao == 2) {
                al_draw_bitmap(cenarioFora, 0, 0, 0);
                al_draw_bitmap(joao, 200, 300, 0);
                al_draw_bitmap(fantasma, pos_x, pos_y, 0);
                al_draw_bitmap(gearimg, 27, 10, 0);
                gearscreen(font, gears, 50, 50);
                al_draw_bitmap(caixadialogo, 264, 498, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 270, 505, ALLEGRO_ALIGN_LEFT, "João:");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 580, ALLEGRO_ALIGN_LEFT, "Acabei perdendo por aí... Me lembro de ter passado na escola.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 590, ALLEGRO_ALIGN_LEFT, "Talvez ainda esteja lá. É nessa casa vermelha.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 640, ALLEGRO_ALIGN_LEFT, "Pressione [ESPAÇO] para continuar");
               
            }

            if (dialogojoao == 3) {
                al_draw_bitmap(cenarioFora, 0, 0, 0);
                al_draw_bitmap(joao, 200, 300, 0);
                al_draw_bitmap(fantasma, pos_x, pos_y, 0);
                al_draw_bitmap(gearimg, 27, 10, 0);
                gearscreen(font, gears, 50, 50);
                al_draw_bitmap(caixadialogo, 264, 498, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 270, 505, ALLEGRO_ALIGN_LEFT, "João:");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 580, ALLEGRO_ALIGN_LEFT, "Eu sei que você deve estar pensando que eu poderia pegar por mim mesmo.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 590, ALLEGRO_ALIGN_LEFT, "Mas minhas costas doem tanto.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 640, ALLEGRO_ALIGN_LEFT, "Pressione [ESPAÇO] para continuar");

            }

            if (dialogojoao == 4) {
                al_draw_bitmap(cenarioFora, 0, 0, 0);
                al_draw_bitmap(joao, 200, 300, 0);
                al_draw_bitmap(fantasma, pos_x, pos_y, 0);
                al_draw_bitmap(gearimg, 27, 10, 0);
                gearscreen(font, gears, 50, 50);
                al_draw_bitmap(caixadialogo, 264, 498, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 270, 505, ALLEGRO_ALIGN_LEFT, "João:");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 580, ALLEGRO_ALIGN_LEFT, "Quando recuperar as 4 me encontre na casa do meio.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 290, 590, ALLEGRO_ALIGN_LEFT, "Prometo te dar uns trocados.");
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 640, ALLEGRO_ALIGN_LEFT, "Pressione [ESPAÇO] para continuar");

            }

            if (dialogojoao == 5) {
                estadoatual = 3;
            }

            break;
        case 13:
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 1280 / 2, 700 / 2 - 50, ALLEGRO_ALIGN_CENTER,
                "Pressione ENTER para começar!");
            al_flip_display();

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                num1 = rand() % 10 + 1;
                num2 = rand() % 10 + 1;
                resposta_correta = num1 * num2;
                tempo_inicial = al_get_time();
                estadoatual = 14;  
            }
            break;

        case 14: 
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 1280 / 2, 100, ALLEGRO_ALIGN_CENTER,
                "Rodada: %d", rodada);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 1280 / 2, 150, ALLEGRO_ALIGN_CENTER,
                "Tempo restante: %.2f", tempo_restante);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 1280 / 2, 200, ALLEGRO_ALIGN_CENTER,
                "Resolva: %d x %d", num1, num2);
            al_draw_text(font, al_map_rgb(255, 255, 255), 1280 / 2, 300, ALLEGRO_ALIGN_CENTER,
                entrada);
            al_flip_display();

                if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                    char c = evento.keyboard.unichar;
                    if (c >= '0' && c <= '9') { 
                        entrada[posicao_entrada++] = c;
                        entrada[posicao_entrada] = '\0';
                    }
                    else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && posicao_entrada > 0) {
                        entrada[--posicao_entrada] = '\0';
                    }
                }
            

        
            if (atoi(entrada) == resposta_correta) {
                pontos++;
                rodada++;

                if (rodada > 5) {
                    jogotabudada = false;
                    gears++;
                    estadoatual = 15;  
                }
                else {
                    num1 = rand() % 10 + 1;
                    num2 = rand() % 10 + 1;
                    resposta_correta = num1 * num2;
                    tempo_limite -= 1;
                    posicao_entrada = 0;
                    entrada[0] = '\0';
                    tempo_inicial = al_get_time();
                }
            }

            // Verifica se o tempo acabou
            if (tempo_restante <= 0) {
                estadoatual = 15;  // Derrota ou fim de jogo
            }
            break;

        case 15:
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (rodada > 5) {
                al_draw_text(font, al_map_rgb(0, 255, 0), 1280 / 2, 1280 / 2 - 50, ALLEGRO_ALIGN_CENTER,
                "Você venceu!");
        
            }
            else {
                al_draw_text(font, al_map_rgb(255, 0, 0), 1280 / 2, 1280 / 2 - 50, ALLEGRO_ALIGN_CENTER,
                    "Você perdeu!");
            }
            al_draw_text(font, al_map_rgb(255, 255, 255), 1280 / 2, 1280 / 2 + 50, ALLEGRO_ALIGN_CENTER,
                "Pressione ESC para sair.");
            al_flip_display();

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                estadoatual = 6;
            }
            break;

        case 16:

           

        }

       


        al_flip_display();
    }

    al_destroy_bitmap(palavraCruzada);
    al_destroy_bitmap(g_linear);
    al_destroy_bitmap(g_expo);
    al_destroy_bitmap(g_quadra);
    al_destroy_bitmap(g_log);
    al_destroy_bitmap(res_lin);
    al_destroy_bitmap(res_expo);
    al_destroy_bitmap(res_quad);
    al_destroy_bitmap(res_log);
    al_destroy_bitmap(qua_resp);
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
    al_destroy_bitmap(botaoplay);
    al_destroy_bitmap(botaoquit);
    al_destroy_bitmap(titulogame);
    al_destroy_bitmap(fundoinicial);
    al_destroy_bitmap(gearimg);

    al_destroy_timer(timer);


    return 0;
}