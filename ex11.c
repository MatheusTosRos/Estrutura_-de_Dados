#include <stdio.h>

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arr[], int inicio, int fim) {
    int pivô = arr[fim];    
    int i = (inicio - 1);  

    for (int j = inicio; j <= fim - 1; j++) {
        if (arr[j] <= pivô) {
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[fim]);
    return (i + 1);
}

void quickSort(int arr[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(arr, inicio, fim);

        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
}

void imprimirArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Array original:\n");
    imprimirArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Array ordenado:\n");
    imprimirArray(arr, n);

    return 0;
}
