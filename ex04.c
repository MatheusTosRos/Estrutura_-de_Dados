#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define o tamanho máximo da fila

typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct ListaAdj {
    No* cabeca;
} ListaAdj;

typedef struct Grafo {
    int numVertices;
    ListaAdj* lista;
} Grafo;

typedef struct Fila {
    int itens[MAX];
    int frente, traseira;
} Fila;

No* criarNo(int v) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->proximo = NULL;
    return novoNo;
}

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;

    grafo->lista = (ListaAdj*)malloc(vertices * sizeof(ListaAdj));

    for (int i = 0; i < vertices; i++) {
        grafo->lista[i].cabeca = NULL;
    }

    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    No* novoNo = criarNo(destino);
    novoNo->proximo = grafo->lista[origem].cabeca;
    grafo->lista[origem].cabeca = novoNo;

    novoNo = criarNo(origem);
    novoNo->proximo = grafo->lista[destino].cabeca;
    grafo->lista[destino].cabeca = novoNo;
}

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = -1;
    fila->traseira = -1;
    return fila;
}

int filaVazia(Fila* fila) {
    if (fila->frente == -1)
        return 1;
    else
        return 0;
}

void enfileirar(Fila* fila, int valor) {
    if (fila->traseira == MAX - 1)
        printf("\nFila cheia\n");
    else {
        if (fila->frente == -1)
            fila->frente = 0;
        fila->traseira++;
        fila->itens[fila->traseira] = valor;
    }
}

int desenfileirar(Fila* fila) {
    int item;
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
        item = -1;
    } else {
        item = fila->itens[fila->frente];
        fila->frente++;
        if (fila->frente > fila->traseira) {
            fila->frente = fila->traseira = -1;
        }
    }
    return item;
}

void BFS(Grafo* grafo, int verticeInicial) {
    int visitado[grafo->numVertices];
    for (int i = 0; i < grafo->numVertices; i++) {
        visitado[i] = 0;
    }

    Fila* fila = criarFila();

    visitado[verticeInicial] = 1;
    enfileirar(fila, verticeInicial);

    while (!filaVazia(fila)) {
        int vertice = desenfileirar(fila);
        printf("%d ", vertice);

        No* temp = grafo->lista[vertice].cabeca;
        while (temp) {
            int adjVertice = temp->vertice;

            if (!visitado[adjVertice]) {
                visitado[adjVertice] = 1;
                enfileirar(fila, adjVertice);
            }
            temp = temp->proximo;
        }
    }
    free(fila);
}

void imprimirGrafo(Grafo* grafo) {
    for (int v = 0; v < grafo->numVertices; v++) {
        No* temp = grafo->lista[v].cabeca;
        printf("\n Lista de adjacências do vértice %d\n ", v);
        while (temp) {
            printf("-> %d", temp->vertice);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

int main() {
    int numVertices, opcao, origem, destino, verticeInicial;

    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);

    Grafo* grafo = criarGrafo(numVertices);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar aresta\n");
        printf("2. Exibir grafo\n");
        printf("3. Executar BFS\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a origem e o destino da aresta (0 a %d): ", numVertices - 1);
                scanf("%d %d", &origem, &destino);
                if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices) {
                    adicionarAresta(grafo, origem, destino);
                    printf("Aresta adicionada entre %d e %d.\n", origem, destino);
                } else {
                    printf("Vértices inválidos.\n");
                }
                break;
            case 2:
                imprimirGrafo(grafo);
                break;
            case 3:
                printf("Digite o vértice inicial para BFS (0 a %d): ", numVertices - 1);
                scanf("%d", &verticeInicial);
                if (verticeInicial >= 0 && verticeInicial < numVertices) {
                    printf("Resultado da BFS a partir do vértice %d: ", verticeInicial);
                    BFS(grafo, verticeInicial);
                    printf("\n");
                } else {
                    printf("Vértice inválido.\n");
                }
                break;
            case 4:
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
