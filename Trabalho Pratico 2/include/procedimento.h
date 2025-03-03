#ifndef PROCEDIMENTO_H
#define PROCEDIMENTO_H

#include "fila.h"

typedef struct {
    char nome[50];        
    int capacidade;       // Número máximo de atendimentos simultâneos
    double duracao;       
    double ociosidade;    // Tempo ocioso acumulado
    Fila fila_espera;     // Fila de pacientes aguardando
} Procedimento;

void inicializarProcedimento(Procedimento *proc, const char *nome, int capacidade, double duracao);
void processarFila(Procedimento *proc, double tempo_atual);

#endif
