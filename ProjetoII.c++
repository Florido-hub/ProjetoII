#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

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
const bool VER_BOMBAS = true;

// structs


struct Tabuleiro {
    char posicao;
};

struct noPilha {
    Tabuleiro matriz[TAM][TAM];
    noPilha *prox;
};

// funções do campo minado

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
                    cout << tabuleiro[i][j].posicao<<" ";
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

// funções da pilha

noPilha* criar_pilha() {
    return NULL;
}


void limpar_tela() {
    system("cls");
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

bool vazia(noPilha *topo) {
    return topo == NULL;
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


void pular(int quant){
    for(int l=0;l<quant;l++){
        cout<< "\n";
    }
}


void imprimir_pilha(noPilha *pilha) {
    if (pilha != NULL) {
        cout << endl;
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                cout << pilha->matriz[i][j].posicao << " ";
            }
            cout << endl;  // Print a new line after each row
        }
        cout << endl;
        imprimir_pilha(pilha->prox);
    }
}


void desfazer_movimento(Tabuleiro tabuleiro[TAM][TAM], noPilha* pilha, int &vidas) {
    noPilha *p = desempilhar(pilha);

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].posicao = pilha->matriz[i][j].posicao;
        }
    }

    vidas--;
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
            vidas = 2;
            break;
        case 2:
            vidas = 1;
            break;
        case 3:
            vidas = 0;
            break;
        default:
            cout << "ERRO" << endl;
            break;
    }
}

bool jogada(Tabuleiro tabuleiro[TAM][TAM], noPilha* pilha) {
    int p1, p2;
    limpar_tela();
    Minefield();
    imprimir_tabuleiro(tabuleiro);
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

int main()
{

    char welcome;
    Minefield();
    cout << "Bem-vindo ao Minefield! Pressione ESPACO para comecar: ";
    welcome = _getch();

    if (welcome == ' '){
        int vidas = 0;
        noPilha* topo_pilha = criar_pilha();

        Tabuleiro tabuleiro[TAM][TAM];
        criar_tabuleiro(tabuleiro);
        escolher_dificuldade(vidas);
        imprimir_tabuleiro(tabuleiro);
        sortear_bombas(tabuleiro);

        bool partida;

        do {
            partida = jogada(tabuleiro, topo_pilha);
            empilhar(topo_pilha, tabuleiro);

            if (!partida && vidas > 0) {
                cout << "Vidas restantes = " << vidas << endl;
                cout << "Ha uma bomba na posicao escolhida, deseja refazer a jogada? (S/N) ";
                char c;
                cin >> c;

                c = toupper('c'); // transformar minúsculo para maiúsculo

                if (c == 'S') {
                    desfazer_movimento(tabuleiro, topo_pilha, vidas);
                    partida = jogada(tabuleiro, topo_pilha);
                }

            }
        } while (partida && !tabuleiro_preenchido(tabuleiro));

        if(partida && tabuleiro_preenchido(tabuleiro)) {
            cout << "parabens voce ganhou!" << endl;
        } else {
            cout << "voce perdeu!" << endl;
        }

        cout << "pilha com a matriz de jogadas do usuario:" << endl;
        imprimir_pilha(topo_pilha);
        return 0;
    }
}

