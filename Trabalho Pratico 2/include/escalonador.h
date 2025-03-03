
#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "paciente.h"

typedef struct Evento {
    double tempo_execucao;   // Tempo de execução do evento
    int tipo;                // Tipo do evento
    Paciente *paciente;      // Ponteiro para o paciente associado
    struct tm hora_inicio;   // Hora de início do evento
    struct tm hora_fim;      // Hora de término do evento
    double consumo_total;    // Tempo total de atendimento
    double consumo_efetivo;  // Tempo efetivo de atendimento
    double consumo_perda;    // Tempo perdido em espera
} Evento;

typedef struct {
    Evento **eventos; // Array de ponteiros para eventos (MinHeap)
    int capacidade;   // Tamanho máximo do heap
    int tamanho;      // Quantidade de elementos no heap
} Escalonador;

// Funções para manipular o escalonador
Escalonador* criarEscalonador(int capacidade);
void adicionarEvento(Escalonador *esc, Evento *evento);
Evento* retirarProximoEvento(Escalonador *esc);
int compararEventos(Evento *a, Evento *b);
void finalizarEscalonador(Escalonador *esc);

#endif
