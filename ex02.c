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

void removerAresta(Grafo* grafo, int origem, int destino) {
    No* atual = grafo->lista[origem].cabeca;
    No* anterior = NULL;

    while (atual != NULL && atual->vertice != destino) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL) {
        if (anterior == NULL) {
            grafo->lista[origem].cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    }

    atual = grafo->lista[destino].cabeca;
    anterior = NULL;
    while (atual != NULL && atual->vertice != origem) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL) {
        if (anterior == NULL) {
            grafo->lista[destino].cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    }
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
    int numVertices, opcao, origem, destino;

    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);

    Grafo* grafo = criarGrafo(numVertices);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar aresta\n");
        printf("2. Remover aresta\n");
        printf("3. Exibir grafo\n");
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
                printf("Digite a origem e o destino da aresta a remover (0 a %d): ", numVertices - 1);
                scanf("%d %d", &origem, &destino);
                if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices) {
                    removerAresta(grafo, origem, destino);
                    printf("Aresta removida entre %d e %d.\n", origem, destino);
                } else {
                    printf("Vértices inválidos.\n");
                }
                break;
            case 3:
                imprimirGrafo(grafo);
                break;
            case 4:
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
