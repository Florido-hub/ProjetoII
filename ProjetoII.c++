#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <climits>

#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define ORANGE "\033[33m"
#define RED     "\033[31m"
#define PURPLE "\033[38;2;128;0;128m"
#define RESET   "\033[0m"

using namespace std;

const int TAM = 8;
const int BOMBAS = 12;
bool VER_BOMBAS = false;
bool continuar_jogando = false;

// structs

struct Tabuleiro {
    char posicao;
};

struct noPilha {
    Tabuleiro matriz[TAM][TAM];
    noPilha *prox;
};

// funções auxiliares

void limpar_tela() {
    system("cls");
}

void pular(int quant){
    for(int l=0;l<quant;l++){
        cout<< "\n";
    }
}

void Minefield(){
    cout << "##############################################################\n";
    cout << "  __  __   _                  _____   _          _       _ " << endl;
    cout << " |  \\/  | (_)  _ __     ___  |  ___| (_)   ___  | |   __| |" << endl;
    cout << " | |\\/| | | | | '_ \\   / _ \\ | |_    | |  / _ \\ | |  / _` |" << endl;
    cout << " | |  | | | | | | | | |  __/ |  _|   | | |  __/ | | | (_| |" << endl;
    cout << " |_|  |_| |_| |_| |_|  \\___| |_|     |_|  \\___| |_|  \\__,_|" << endl;
    cout << "\n";
    cout << "##############################################################\n";
    cout << "\n";
    cout << "\n";
}

void tela_vitoria() {
    cout << "           _________  _________   _______    _______   _________   _______    _ \n";
    cout << "|\\     /|  \\__   __/  \\__   __/  (  ___  )  (  ____ )  \\__   __/  (  ___  )  ( )\n";
    cout << "| )   ( |     ) (        ) (     | (   ) |  | (    )|     ) (     | (   ) |  | |\n";
    cout << "| |   | |     | |        | |     | |   | |  | (____)|     | |     | (___) |  | |\n";
    cout << "( (   ) )     | |        | |     | |   | |  |     __)     | |     |  ___  |  | |\n";
    cout << " \\ \\_/ /      | |        | |     | |   | |  | (\\ (        | |     | (   ) |  (_)\n";
    cout << "  \\   /    ___) (___     | |     | (___) |  | ) \\ \\__  ___) (___  | )   ( |   _ \n";
    cout << "   \\_/     \\_______/     )_(     (_______)  |/   \\__/  \\_______/  |/     \\|  (_)\n"";                                                      " << endl;
    cout << endl;
}

void tela_derrota() {
    cout << " _______   _________   _______                 \n";
    cout << "(  ____ \\  \\__   __/  (       )                \n";
    cout << "| (    \\/     ) (     | () () |                \n";
    cout << "| (__         | |     | || || |                \n";
    cout << "|  __)        | |     | |(_)| |                \n";
    cout << "| (           | |     | |   | |                \n";
    cout << "| )        ___) (___  | )   ( |                \n";
    cout << "|/         \\_______/  |/     \\|                \n";
    cout << "                                                \n";
    cout << " ______     _______                            \n";
    cout << "(  __  \\   (  ____ \\                           \n";
    cout << "| (  \\  )  | (    \\/                           \n";
    cout << "| |   ) |  | (__                               \n";
    cout << "| |   | |  |  __)                              \n";
    cout << "| |   ) |  | (                                 \n";
    cout << "| (__/  )  | (____/\\                           \n";
    cout << "(______/   (_______/                           \n";
    cout << "                                                \n";
    cout << "_________   _______    _______    _______    _ \n";
    cout << "\\__    _/  (  ___  )  (  ____ \\  (  ___  )  ( )\n";
    cout << "   )  (    | (   ) |  | (    \\/  | (   ) |  | |\n";
    cout << "   |  |    | |   | |  | |        | |   | |  | |\n";
    cout << "   |  |    | |   | |  | | ____   | |   | |  | |\n";
    cout << "   |  |    | |   | |  | | \\_  )  | |   | |  (_)\n";
    cout << " |\\_)  )    | (___) |  | (___) |  | (___) |   _ \n";
    cout << " (____/     (_______)  (_______)  (_______)  (_)\n";
    cout << endl;

}

// funções do campo minado

void tela_inicial() {
    char welcome;
    Minefield();
    cout << "Bem-vindo ao Minefield! Pressione ESPACO para comecar";
    welcome = _getch();

    if (welcome == ' ') {
        continuar_jogando = true;
    } else {
        continuar_jogando = false;
    }
}

void criar_tabuleiro(Tabuleiro tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].posicao = '-';
        }
    }
}

void imprimir_tabuleiro(Tabuleiro tabuleiro[TAM][TAM]) {
    cout << "    ";
    for (int k = 0; k < TAM; k++) {
        cout << k << " ";
    }
    cout << endl;

    for (int i = 0; i < TAM; i++) {
        cout << i << " | " ;
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].posicao == 'B') {
                if (VER_BOMBAS) {
                    cout << tabuleiro[i][j].posicao << " "<< RESET;
                } else {
                    cout << "- ";
                }
            } else {
                int bombs_near = tabuleiro[i][j].posicao - '0';
                if (bombs_near >= 0) {
                    if (bombs_near == 0)
                        cout << GREEN << tabuleiro[i][j].posicao << " "<< RESET;
                    if (bombs_near == 1)
                        cout << CYAN << tabuleiro[i][j].posicao << " "<< RESET;
                    if (bombs_near == 2)
                        cout << YELLOW << tabuleiro[i][j].posicao << " "<< RESET;
                    if(bombs_near == 3)
                        cout << RED << tabuleiro[i][j].posicao << " "<< RESET;
                    if (bombs_near == 4)
                        cout << PURPLE << tabuleiro[i][j].posicao << " "<< RESET;
                } else {
                    cout << tabuleiro[i][j].posicao<< " ";
                }
            }
        }
        cout << "|" << endl;
    }
}

bool tabuleiro_preenchido(Tabuleiro tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].posicao == '-') {
                return false;
            }
        }
    }

    return true;
}

bool posicao_existe(int p1, int p2) {
    return p1 >= 0 && p1 < TAM && p2 >= 0 && p2 < TAM;
}

void preencher_redor(Tabuleiro tabuleiro[TAM][TAM], int p1, int p2) {
    int qtdBombas = 0;

    if(tabuleiro[p1][p2 - 1].posicao == 'B' && posicao_existe(p1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2 - 1].posicao == 'B' && posicao_existe(p1 + 1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2].posicao == 'B' && posicao_existe(p1 + 1, p2)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2 + 1].posicao == 'B' && posicao_existe(p1 - 1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1][p2 + 1].posicao == 'B' && posicao_existe(p1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2 + 1].posicao == 'B' && posicao_existe(p1 + 1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2].posicao == 'B' && posicao_existe(p1 - 1, p2)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2 - 1].posicao == 'B' && posicao_existe(p1 - 1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1][p2].posicao != 'B' && posicao_existe(p1, p2)) {
        char aux = qtdBombas + '0'; // converter int para char
        tabuleiro[p1][p2].posicao = aux;
    }
}

void achar_bomba(Tabuleiro tabuleiro[TAM][TAM], int p1, int p2) {
    int qtdBombas = 0;

    if(tabuleiro[p1][p2 - 1].posicao == 'B' && posicao_existe(p1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2 - 1].posicao == 'B' && posicao_existe(p1 + 1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2].posicao == 'B' && posicao_existe(p1 + 1, p2)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2 + 1].posicao == 'B' && posicao_existe(p1 - 1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1][p2 + 1].posicao == 'B' && posicao_existe(p1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 + 1][p2 + 1].posicao == 'B' && posicao_existe(p1 + 1, p2 + 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2].posicao == 'B' && posicao_existe(p1 - 1, p2)) {
        qtdBombas++;
    }

    if(tabuleiro[p1 - 1][p2 - 1].posicao == 'B' && posicao_existe(p1 - 1, p2 - 1)) {
        qtdBombas++;
    }

    if(tabuleiro[p1][p2].posicao != 'B') {
        char aux = qtdBombas + '0'; // converter int para char
        tabuleiro[p1][p2].posicao = aux;

        if (aux == '0') {
            preencher_redor(tabuleiro, p1, p2 - 1);
            preencher_redor(tabuleiro, p1 + 1, p2 - 1);
            preencher_redor(tabuleiro, p1 + 1, p2);
            preencher_redor(tabuleiro, p1 - 1, p2 + 1);
            preencher_redor(tabuleiro, p1, p2 + 1);
            preencher_redor(tabuleiro, p1 + 1, p2 + 1);
            preencher_redor(tabuleiro, p1 - 1, p2);
            preencher_redor(tabuleiro, p1 - 1, p2 - 1);
        }
    }
}

int quantidade_bombas(Tabuleiro tabuleiro[TAM][TAM]) {
    int qtdBombas = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].posicao == 'B') {
                qtdBombas++;
            }
        }
    }

    return qtdBombas;
}

void sortear_bombas(Tabuleiro tabuleiro[TAM][TAM]) {
    srand(time(0));
    int qtdBombas = quantidade_bombas(tabuleiro);

    while (qtdBombas < BOMBAS) {
        int p1, p2;

        p1 = rand() % TAM;
        p2 = rand() % TAM;

        tabuleiro[p1][p2].posicao = 'B';

        qtdBombas = quantidade_bombas(tabuleiro);
    }
}

void escolher_dificuldade(int &vidas) {
    limpar_tela();
    Minefield();
    cout << "Escolha a dificuldade do jogo: " << endl;
    cout << "1. Facil" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Dificil" << endl;
    cout << "4. Modo desenvolvedor" << endl;

    int dificuldade;
    cin >> dificuldade;

    while (dificuldade < 0 || dificuldade > 4) {
        cout << "Escolha uma opcao valida: ";
        cin >> dificuldade;
    }

    switch (dificuldade) {
        case 1:
            VER_BOMBAS = false;
            vidas = 2;
            break;
        case 2:
            VER_BOMBAS = false;
            vidas = 1;
            break;
        case 3:
            VER_BOMBAS = false;
            vidas = 0;
            break;
        case 4:
            VER_BOMBAS = true;
            vidas = INT_MAX;
            break;
        default:
            cout << "ERRO" << endl;
            break;
    }
}

void status_partida(int vidas,string dificuldade){
    if (dificuldade == "Modo desenvolvedor") {
        cout << "VIDAS: Infinitas   -  DIFICULDADE: " << dificuldade << endl;
    } else {
        cout<< "VIDAS: " << vidas << "  -  DIFICULDADE: " << dificuldade << endl;
    }
}

bool jogada(Tabuleiro tabuleiro[TAM][TAM], noPilha* pilha,int vidas, string dificuldade) {
    int p1, p2;
    limpar_tela();
    Minefield();
    imprimir_tabuleiro(tabuleiro);
    status_partida(vidas,dificuldade);
    cout<<" "<<endl;
    pular(2);

    cout << "Digite a linha e a coluna:" << endl;
    cin >> p1;
    cin >> p2;
    cout << endl;

    while (p1 < 0 || p1 > TAM || p2 < 0 || p2 > TAM) {
        cout << "Valores invalidos, digite a linha e a coluna novamente:" << endl;
        cin >> p1;
        cin >> p2;
        cout << endl;
    }

    achar_bomba(tabuleiro, p1, p2);
    imprimir_tabuleiro(tabuleiro);

    if (tabuleiro[p1][p2].posicao == 'B') {
        return false;
    } else {
        return true;
    }
}

// funções da pilha

noPilha* criar_pilha() {
    return NULL;
}

bool vazia(noPilha *topo) {
    return topo == NULL;
}

void empilhar(noPilha *&topo, Tabuleiro matriz[TAM][TAM]) {
    noPilha *novo = new noPilha;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            novo->matriz[i][j] = matriz[i][j];
        }
    }

    novo->prox = topo;
    topo = novo;
}

noPilha *desempilhar(noPilha *&topo) {
    if(vazia(topo)) {
        return NULL;
    } else {
        noPilha *p = topo;
        topo = topo->prox;
        return p;
    }
}

void imprimir_pilha(noPilha *pilha) {
    if (pilha != NULL) {
        cout << "    ";
        for (int k = 0; k < TAM; k++) {
            cout << k << " ";
        }
        cout << endl;

        for (int i = 0; i < TAM; i++) {
            cout << i << " | " ;
            for (int j = 0; j < TAM; j++) {
                if (pilha->matriz[i][j].posicao == 'B') {
                    cout << pilha->matriz[i][j].posicao << " "<< RESET;
                } else {
                    int bombs_near = pilha->matriz[i][j].posicao - '0';
                    if (bombs_near >= 0) {
                        if (bombs_near == 0)
                            cout << GREEN << pilha->matriz[i][j].posicao << " "<< RESET;
                        if (bombs_near == 1)
                            cout << CYAN << pilha->matriz[i][j].posicao << " "<< RESET;
                        if (bombs_near == 2)
                            cout << YELLOW << pilha->matriz[i][j].posicao << " "<< RESET;
                        if(bombs_near == 3)
                            cout << RED << pilha->matriz[i][j].posicao << " "<< RESET;
                        if (bombs_near == 4)
                            cout << PURPLE << pilha->matriz[i][j].posicao << " "<< RESET;
                    } else {
                        cout << pilha->matriz[i][j].posicao<< " ";
                    }
                }
            }
            cout << "|" << endl;
            cout << endl;
        }
        imprimir_pilha(pilha->prox);
    }
}

void desfazer_movimento(Tabuleiro tabuleiro[TAM][TAM], noPilha* pilha, int &vidas) {
    noPilha *p = desempilhar(pilha);

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].posicao = p->matriz[i][j].posicao; // Usar a pilha desempilhada
        }
    }

    vidas--;
}

int main()
{
    tela_inicial();

    while (continuar_jogando){
        int vidas = 0;
        noPilha* topo_pilha = criar_pilha();

        Tabuleiro tabuleiro[TAM][TAM];
        criar_tabuleiro(tabuleiro);
        escolher_dificuldade(vidas);
        string dificuldade;
        if (vidas == 0) {
            dificuldade = "DIFICIL";
        } else if (vidas == 1) {
            dificuldade = "MEDIO";
        } else if (vidas == 2) {
            dificuldade = "FACIL";
        } else {
            dificuldade = "Modo desenvolvedor";
        }
        imprimir_tabuleiro(tabuleiro);
        sortear_bombas(tabuleiro);

        bool partida;

        do {
            partida = jogada(tabuleiro, topo_pilha, vidas, dificuldade);
            empilhar(topo_pilha, tabuleiro);

            if (!partida && vidas > 0) {
                limpar_tela();
                Minefield();
                imprimir_tabuleiro(tabuleiro);

                char c;
                cout<<endl;
                cout << "Vidas restantes = " << vidas << endl;
                cout << "Ha uma bomba na posicao escolhida, deseja refazer a jogada? (S/N) ";
                cin >> c;
                c = toupper(c);

                if (c == 'S') {
                    desfazer_movimento(tabuleiro, topo_pilha, vidas);
                    partida = jogada(tabuleiro, topo_pilha,vidas, dificuldade);
                }

            }
        } while (partida && !tabuleiro_preenchido(tabuleiro));

        limpar_tela();
        Minefield();

        if(partida && tabuleiro_preenchido(tabuleiro)) {
            limpar_tela();
            tela_vitoria();
        } else {
            limpar_tela();
            tela_derrota();
        }

        char p;
        cout << "Deseja imprimir a pilha de jogadas? (S/N)";
        cin >> p;
        p = toupper(p);

        if (p == 'S') {
            cout << "pilha com a matriz de jogadas do usuario:" << endl;
            imprimir_pilha(topo_pilha);
        }

        char j;
        cout << "Deseja continuar a jogar? (S/N)";
        cin >> j;
        j = toupper(j);

        if (j == 'S') {
            limpar_tela();
            tela_inicial();
        } else {
            continuar_jogando = false;
        }
    }

    return 0;
}
