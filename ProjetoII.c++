#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define ORANGE "\033[33m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

using namespace std;

const int TAM = 8;
const int BOMBAS = 8;
const bool VER_BOMBAS = true;

struct Tabuleiro {
    char posicao;
};

struct noPilha {
    int matriz[TAM][TAM];
    noPilha *prox;
};

noPilha* criar_pilha() {
    return NULL;
}

void limpar_tela() {
    system("cls");
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
        cout << i << " | ";
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
                        cout << ORANGE << tabuleiro[i][j].posicao << " "<< RESET;
                    if (bombs_near == 4)
                        cout << RED << tabuleiro[i][j].posicao << " "<< RESET;
                } else {
                    cout << tabuleiro[i][j].posicao<< " ";
                }
            }
        }
        cout << "|" << endl;
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


void sortear_bombas(Tabuleiro tabuleiro[TAM][TAM]) {
    srand(time(0));

    for (int i = 0; i < BOMBAS; i++) {
        int p1, p2;

        p1 = rand() % TAM;
        p2 = rand() % TAM;

        tabuleiro[p1][p2].posicao = 'B';
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

void pular(int quant){
    for(int l=0;l<quant;l++){
        cout<< "\n";
    }
}

bool jogada(Tabuleiro tabuleiro[TAM][TAM]) {
    int p1, p2;
    limpar_tela();
    Minefield();
    imprimir_tabuleiro(tabuleiro);
    cout<<" "<<endl;
    pular(2);

    cout << "digite a linha e a coluna:"<<endl;
    cin >> p1;
    cin >> p2;
    achar_bomba(tabuleiro, p1, p2);

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
        Tabuleiro tabuleiro[TAM][TAM];
        criar_tabuleiro(tabuleiro);
        sortear_bombas(tabuleiro);
        bool partida = jogada(tabuleiro);

        while(partida && !tabuleiro_preenchido(tabuleiro)) {
            partida = jogada(tabuleiro);
        }

        if(partida && tabuleiro_preenchido(tabuleiro)) {
            cout << "parabens voce ganhou! :)";
        } else {
            cout << "voce perdeu ;(";
        }
    }else{
        cout << "Quem sabe podemos jogar na proxima vez ;(";
        for(int i=0;i<5;i++){
            cout<<endl;
        }
    }

    return 0;
}
