#include "fila.h" 
#include <stdlib.h>
#include <stdio.h>  

// Função para inicializar a fila
void inicializarFila(Fila *fila) {
    fila->inicio = NULL;  // Define o início da fila como nulo (vazia)
    fila->fim = NULL;     // Define o fim da fila como nulo (vazia)
    fila->tamanho = 0;    // Define o tamanho da fila como zero
}

// Função que vai adicionar um paciente na fila
void enfileirar(Fila *fila, Paciente *paciente) {
    // Alocando memória para um novo nó na fila
    NoFila *novo_no = (NoFila *)malloc(sizeof(NoFila));
    if (!novo_no) { // Verifica se a alocação falhou
        fprintf(stderr, "Erro ao alocar memória para nó da fila.\n");
        exit(EXIT_FAILURE); // Finaliza o programa em caso de erro
    }

    novo_no->paciente = paciente; // Associa o paciente ao nó
    novo_no->prox = NULL;         // O próximo nó do novo nó é nulo (último elemento)

    if (fila->fim) { // Se a fila já tem elementos
        fila->fim->prox = novo_no; // O último nó atual aponta para o novo nó
    } else { // Se a fila está vazia
        fila->inicio = novo_no; // O novo nó passa a ser o início da fila
    }

    fila->fim = novo_no; // Atualiza o ponteiro do fim da fila para o novo nó
    fila->tamanho++;     // Incrementa o tamanho da fila
}

// Função que remove/desenfileira um paciente da fila 
Paciente* desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) { // Verifica se a fila está vazia
        fprintf(stderr, "Erro: Tentativa de remover de uma fila vazia.\n");
        exit(EXIT_FAILURE); // Finaliza o programa em caso de erro
    }

    NoFila *removido = fila->inicio;   // Guarda o nó a ser removido
    Paciente *paciente = removido->paciente; // Guarda o paciente associado ao nó
    fila->inicio = removido->prox;    // Atualiza o início da fila para o próximo nó

    if (fila->inicio == NULL) { // Se a fila ficou vazia após a remoção
        fila->fim = NULL; // Atualiza o fim da fila para nulo
    }

    free(removido);       // Libera a memória do nó removido
    fila->tamanho--;      // Decrementa o tamanho da fila

    return paciente; // Retorna o paciente removido
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) {
    return (fila->inicio == NULL); 
}

// Função para finalizar a fila, liberando todos os nós
void finalizarFila(Fila *fila) {
    while (!filaVazia(fila)) {    
        desenfileirar(fila);      
    }
}
