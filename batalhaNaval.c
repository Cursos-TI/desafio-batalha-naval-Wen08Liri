#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_HABILIDADE 5
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // Representa água
        }
    }
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < NAVIO; i++) {
        if (orientacao == 0) coluna += i; // Horizontal
        else if (orientacao == 1) linha += i; // Vertical
        else if (orientacao == 2) { linha += i; coluna += i; } // Diagonal ↘
        else if (orientacao == 3) { linha += i; coluna -= i; } // Diagonal ↙

        if (linha < TAMANHO && coluna < TAMANHO && coluna >= 0) {
            tabuleiro[linha][coluna] = 3; // Representa navio
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int l = linha + i - TAMANHO_HABILIDADE / 2;
            int c = coluna + j - TAMANHO_HABILIDADE / 2;

            if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO) {
                if (tipo == 0 && j <= i) {
                    tabuleiro[l][c] = HABILIDADE; // Cone
                }
                if (tipo == 1 && (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)) {
                    tabuleiro[l][c] = HABILIDADE; // Cruz
                }
                if (tipo == 2 && abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                    tabuleiro[l][c] = HABILIDADE; // Octaedro
                }
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");   // Água
            else if (tabuleiro[i][j] == 3) printf("N "); // Navio
            else if (tabuleiro[i][j] == 5) printf("* "); // Habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    inicializarTabuleiro(tabuleiro);

    // Posicionando navios
    posicionarNavio(tabuleiro, 2, 2, 0); // Horizontal
    posicionarNavio(tabuleiro, 5, 5, 1); // Vertical
    posicionarNavio(tabuleiro, 0, 0, 2); // Diagonal ↘
    posicionarNavio(tabuleiro, 0, 9, 3); // Diagonal ↙

    // Aplicando habilidades
    aplicarHabilidade(tabuleiro, 7, 4, 0); // Cone
    aplicarHabilidade(tabuleiro, 3, 3, 1); // Cruz
    aplicarHabilidade(tabuleiro, 6, 6, 2); // Octaedro

    exibirTabuleiro(tabuleiro);

    return 0;
}
