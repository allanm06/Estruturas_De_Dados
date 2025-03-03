#ifndef VOOS_H
#define VOOS_H

#include <time.h>

typedef struct {
    char org[4];    // Origem (3 letras)
    char dst[4];    // Destino
    double prc;     // Preço
    int sea;        // Assentos disponíveis
    char dep[20];   // Partida (ISO 8601)
    char arr[20];   // Chegada
    int sto;        // Número de escalas
    time_t dur;     // Duração em segundos
} Voo;

Voo* carregar_voos(const char* arquivo, int* n_voos);
void liberar_voos(Voo* voos);
time_t converter_data(const char* data_str);

#endif