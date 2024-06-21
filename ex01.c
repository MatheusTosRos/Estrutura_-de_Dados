
Copiar código
#include <stdio.h>

#define MAX 100  // Definindo o tamanho máximo da matriz de adjacências

void inicializarMatriz(int matriz[MAX][MAX], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }
}

void adicionarRua(int matriz[MAX][MAX], int n1, int n2) {
    matriz[n1][n2] = 1;
    matriz[n2][n1] = 1; 
}

void imprimirMatriz(int matriz[MAX][MAX], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, opcao, intersecao1, intersecao2;
    int matriz[MAX][MAX];

    printf("Digite o numero de intersecoes: ");
    scanf("%d", &n);

    inicializarMatriz(matriz, n);

    while(1) {
        printf("\nMenu:\n");
        printf("1. Adicionar nova rua\n");
        printf("2. Exibir matriz de adjacencias\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite as intersecoes para conectar (0 a %d): ", n-1);
                scanf("%d %d", &intersecao1, &intersecao2);
                if(intersecao1 >= 0 && intersecao1 < n && intersecao2 >= 0 && intersecao2 < n) {
                    adicionarRua(matriz, intersecao1, intersecao2);
                    printf("Rua adicionada entre intersecao %d e intersecao %d.\n", intersecao1, intersecao2);
                } else {
                    printf("Intersecoes invalidas.\n");
                }
                break;
            case 2:
                printf("Matriz de adjacencias:\n");
                imprimirMatriz(matriz, n);
                break;
            case 3:
                return 0;
            default:
                printf("Opcao invalida.\n");
        }
    }
    
    return 0;
}
