#ifndef PACIENTE_H
#define PACIENTE_H

#include <time.h>

typedef struct {
    int id;                   // Identificador único
    int alta;                 // Se teve alta (1) ou não (0)
    struct tm chegada;        // Data e hora de chegada
    struct tm saida;          // Data e hora de saída
    int grau_urgencia;        // Grau de urgência (0: Verde, 1: Amarelo, 2: Vermelho)
    int procedimentos[4];     // Quantidade de procedimentos realizados (por tipo)
    double tempo_total;       // Tempo total no hospital
    double tempo_atendimento; // Tempo efetivamente atendido
    double tempo_espera;      // Tempo aguardando em filas
} Paciente;

// Declaração da função inicializarPaciente
void inicializarPaciente(Paciente *p, int id, int alta, struct tm chegada, int grau_urgencia, int *procedimentos);

#endif
