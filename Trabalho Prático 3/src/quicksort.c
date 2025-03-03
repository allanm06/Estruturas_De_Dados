#include "../include/quicksort.h"  

// Função auxiliar para trocar dois elementos de lugar no vetor
static void swap(Voo* a, Voo* b) {
    Voo temp = *a;
    *a = *b;
    *b = temp;
}

// Função que realiza a partição do vetor para o QuickSort
int particionar(Voo* vetor, int inicio, int fim, ComparadorVoos cmp) {
    Voo pivo = vetor[fim];  // Define o pivô como o último elemento
    int i = inicio - 1;  // Índice do menor elemento encontrado

    for (int j = inicio; j < fim; j++) {
        // Se o elemento atual for menor ou igual ao pivô, troca de posição
        if (cmp(&vetor[j], &pivo) <= 0) {
            i++;
            swap(&vetor[i], &vetor[j]);  // Troca elementos
        }
    }

    // Coloca o pivô na posição correta no vetor ordenado
    swap(&vetor[i + 1], &vetor[fim]);

    return i + 1;  // Retorna a posição final do pivô
}

// Implementação recursiva do algoritmo QuickSort
void quick_sort(Voo* vetor, int inicio, int fim, ComparadorVoos cmp) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim, cmp);  // Obtém a posição do pivô
        quick_sort(vetor, inicio, p - 1, cmp);  // Ordena a parte esquerda
        quick_sort(vetor, p + 1, fim, cmp);  // Ordena a parte direita
    }
}
