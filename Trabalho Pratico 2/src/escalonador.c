#include "escalonador.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para trocar elementos em um array
static void trocar(Evento **a, Evento **b) {
    Evento *temp = *a;
    *a = *b;
    *b = temp;
}

// Cria um escalonador baseado em MinHeap
Escalonador* criarEscalonador(int capacidade) {
    // Aloca memória para o escalonador
    Escalonador *esc = (Escalonador *)malloc(sizeof(Escalonador));
    if (!esc) {
        // Em caso de falha de alocação, exibe erro e termina o programa
        perror("Erro ao criar escalonador");
        exit(EXIT_FAILURE);
    }
    // Inicializa a capacidade e tamanho do escalonador
    esc->capacidade = capacidade;
    esc->tamanho = 0;

    // Aloca memória para o array de eventos
    esc->eventos = (Evento **)malloc(capacidade * sizeof(Evento *));
    if (!esc->eventos) {
        // Em caso de falha de alocação de eventos, exibe erro e termina o programa
        perror("Erro ao alocar eventos do escalonador");
        free(esc);  // Libera a memória do escalonador antes de sair
        exit(EXIT_FAILURE);
    }
    return esc;
}

// Adiciona um evento ao escalonador
void adicionarEvento(Escalonador *esc, Evento *evento) {
    // Verifica se o escalonador está cheio
    if (esc->tamanho >= esc->capacidade) {
        fprintf(stderr, "Erro: Escalonador está cheio\n");
        return;
    }

    // Adiciona o novo evento no final da heap
    esc->eventos[esc->tamanho] = evento;
    int i = esc->tamanho;
    esc->tamanho++;

    // Reorganiza a heap para manter a propriedade do MinHeap
    // Fazendo "subir" o evento para sua posição correta
    while (i > 0 && compararEventos(esc->eventos[i], esc->eventos[(i - 1) / 2]) < 0) {
        trocar(&esc->eventos[i], &esc->eventos[(i - 1) / 2]);
        i = (i - 1) / 2;  // Move para o índice do pai
    }
}

// Retira e retorna o próximo evento do escalonador (o evento com o menor tempo de execução)
Evento* retirarProximoEvento(Escalonador *esc) {
    // Verifica se o escalonador está vazio
    if (esc->tamanho <= 0) {
        fprintf(stderr, "Erro: Escalonador está vazio\n");
        return NULL;
    }

    // Armazena a raiz (o evento com o menor tempo de execução)
    Evento *raiz = esc->eventos[0];

    // Substitui a raiz pelo último evento da heap e diminui o tamanho
    esc->eventos[0] = esc->eventos[esc->tamanho - 1];
    esc->tamanho--;

    // Reorganiza a heap para manter a propriedade do MinHeap
    int i = 0;
    while (2 * i + 1 < esc->tamanho) {
        // Encontra o menor filho
        int menor = 2 * i + 1;
        if (menor + 1 < esc->tamanho && esc->eventos[menor + 1]->tempo_execucao < esc->eventos[menor]->tempo_execucao) {
            menor = menor + 1;
        }
        // Se o evento na posição atual é menor que o menor filho, termina
        if (esc->eventos[i]->tempo_execucao <= esc->eventos[menor]->tempo_execucao) {
            break;
        }
        // Caso contrário, troca o evento atual com o menor filho
        trocar(&esc->eventos[i], &esc->eventos[menor]);
        i = menor;  // Move para o próximo índice
    }

    // Retorna o evento retirado (com o menor tempo de execução)
    return raiz;
}

// Função auxiliar para comparar dois eventos
int compararEventos(Evento *a, Evento *b) {
    // Compara os tempos de execução dos eventos
    if (a->tempo_execucao < b->tempo_execucao) {
        return -1;
    } else if (a->tempo_execucao > b->tempo_execucao) {
        return 1;
    } else {
        // Se os tempos de execução são iguais, compara o grau de urgência
        if (a->paciente->grau_urgencia < b->paciente->grau_urgencia) {
            return -1;
        } else if (a->paciente->grau_urgencia > b->paciente->grau_urgencia) {
            return 1;
        } else {
            // Se o grau de urgência também for igual, considera-os iguais
            return 0;
        }
    }
}

// Finaliza o escalonador e libera a memória alocada
void finalizarEscalonador(Escalonador *esc) {
    // Libera a memória alocada para os eventos e para o escalonador
    free(esc->eventos);
    free(esc);
}
