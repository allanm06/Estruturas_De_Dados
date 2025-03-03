#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "escalonador.h" // Inclui a definição de ListaEventos
#include "fila.h"
#include "procedimento.h"

void simular(Escalonador *escalonador, Fila *filas, Procedimento *procedimentos, int numProcedimentos);

#endif
