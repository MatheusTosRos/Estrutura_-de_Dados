#include <stdio.h>
#include <stdlib.h>

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

void dfsRecursiva(Grafo* grafo, int vertice, int* visitado) {
    No* adjacente = grafo->lista[vertice].cabeca;
    visitado[vertice] = 1;
    printf("%d ", vertice);

    while (adjacente != NULL) {
        int adjVertice = adjacente->vertice;
        if (!visitado[adjVertice]) {
            dfsRecursiva(grafo, adjVertice, visitado);
        }
        adjacente = adjacente->proximo;
    }
}

void DFS(Grafo* grafo, int verticeInicial) {
    int* visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++) {
        visitado[i] = 0;
    }

    dfsRecursiva(grafo, verticeInicial, visitado);

    free(visitado);
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
        printf("3. Executar DFS\n");
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
                printf("Digite o vértice inicial para DFS (0 a %d): ", numVertices - 1);
                scanf("%d", &verticeInicial);
                if (verticeInicial >= 0 && verticeInicial < numVertices) {
                    printf("Resultado da DFS a partir do vértice %d: ", verticeInicial);
                    DFS(grafo, verticeInicial);
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
