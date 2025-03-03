#ifndef FILA_H
#define FILA_H

#include "paciente.h"

typedef struct NoFila {
    Paciente *paciente;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *fila);
void enfileirar(Fila *fila, Paciente *paciente);
Paciente* desenfileirar(Fila *fila);
int filaVazia(Fila *fila);
void finalizarFila(Fila *fila);

#endif
