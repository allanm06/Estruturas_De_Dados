#ifndef INDICES_H
#define INDICES_H

#include "avl.h"
#include "voos.h"

typedef struct {
    NoAVL* org;
    NoAVL* dst;
    NoAVL* prc;
    NoAVL* sea;
    NoAVL* dep;
    NoAVL* arr;
    NoAVL* sto;
    NoAVL* dur;
} Indices;

Indices criar_indices(Voo* voos, int n_voos);
void liberar_indices(Indices indices);
void processar_consulta(Indices* indices, Voo* voos, int n_voos, 
                       int max_voos, const char* criterio, const char* filtro);

#endif