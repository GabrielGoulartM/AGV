#include <stdio.h>

#define TAMANHO_MATRIZ 4

// Estrutura que representa a partícula
typedef struct {
    int x, y; // Posição atual da partícula na matriz
    char direcao; // Direção atual da partícula ('N', 'S', 'L', 'O' para norte, sul, leste e oeste)
} Particula;

// Função para mover a partícula para a frente
void moverFrente(Particula *particula) {
    switch (particula->direcao) {
        case 'N':
            if (particula->x > 0) {
                particula->x--;
                printf("A partícula se moveu para (%d, %d).\n", particula->x, particula->y);
            } else {
                printf("A partícula não pode se mover para frente.\n");
            }
            break;
        case 'S':
            if (particula->x < TAMANHO_MATRIZ - 1) {
                particula->x++;
                printf("A partícula se moveu para (%d, %d).\n", particula->x, particula->y);
            } else {
                printf("A partícula não pode se mover para frente.\n");
            }
            break;
        case 'L':
            if (particula->y < TAMANHO_MATRIZ - 1) {
                particula->y++;
                printf("A partícula se moveu para (%d, %d).\n", particula->x, particula->y);
            } else {
                printf("A partícula não pode se mover para frente.\n");
            }
            break;
        case 'O':
            if (particula->y > 0) {
                particula->y--;
                printf("A partícula se moveu para (%d, %d).\n", particula->x, particula->y);
            } else {
                printf("A partícula não pode se mover para frente.\n");
            }
            break;
    }
}

// Função para virar a partícula para a direita
void virarDireita(Particula *particula) {
    switch (particula->direcao) {
        case 'N':
            particula->direcao = 'L';
            break;
        case 'S':
            particula->direcao = 'O';
            break;
        case 'L':
            particula->direcao = 'S';
            break;
        case 'O':
            particula->direcao = 'N';
            break;
    }
}

// Função para virar a partícula para a esquerda
void virarEsquerda(Particula *particula) {
    switch (particula->direcao) {
        case 'N':
            particula->direcao = 'O';
            break;
        case 'S':
            particula->direcao = 'L';
            break;
        case 'L':
            particula->direcao = 'N';
            break;
        case 'O':
            particula->direcao = 'S';
            break;
    }
}

int main() {
    Particula minhaParticula = {1, 1, 'N'}; // Posição inicial da partícula (1, 1) voltada para o norte
    int posicaoFinalX = 2;
    int posicaoFinalY = 2;

    // Mover a partícula para a posição final
    while (minhaParticula.x != posicaoFinalX || minhaParticula.y != posicaoFinalY) {
        if (minhaParticula.x < posicaoFinalX) {
            virarDireita(&minhaParticula);
            moverFrente(&minhaParticula);
        } else if (minhaParticula.x > posicaoFinalX) {
            virarEsquerda(&minhaParticula);
            moverFrente(&minhaParticula);
        } else if (minhaParticula.y < posicaoFinalY) {
            moverFrente(&minhaParticula);
        } else if (minhaParticula.y > posicaoFinalY) {
            virarDireita(&minhaParticula);
            virarDireita(&minhaParticula);
            moverFrente(&minhaParticula);
        }
    }

    return 0;
}
