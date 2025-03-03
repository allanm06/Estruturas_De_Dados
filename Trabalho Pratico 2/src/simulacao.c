#include "simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função para salvar saída dos eventos
void salvar_saida(Evento *eventos, int num_eventos) {
    for (int i = 0; i < num_eventos; i++) {
        Evento *evento = &eventos[i];

        // Converter horários para string
        char inicio[64], fim[64];
        strftime(inicio, sizeof(inicio), "%a %b %d %H:%M:%S %Y", &evento->hora_inicio);
        strftime(fim, sizeof(fim), "%a %b %d %H:%M:%S %Y", &evento->hora_fim);

        // Printar a saída no terminal
        printf("%d %s %s %.2f %.2f %.2f\n",
               evento->paciente->id % 1000000, inicio, fim,
               evento->consumo_total, evento->consumo_efetivo, evento->consumo_perda);
    }
}

// Função para simular o processamento dos eventos no escalonador
void simular(Escalonador *escalonador, Fila *filas, Procedimento *procedimentos, int numProcedimentos) {
    printf("Iniciando a simulação...\n");

    while (escalonador->tamanho > 0) {
        // Retira o próximo evento do escalonador
        Evento *evento = retirarProximoEvento(escalonador);

        // Processando o evento
        if (evento->tipo == 1) { // Exemplo: Chegada
            enfileirar(&filas[evento->paciente->grau_urgencia], evento->paciente);
        } else if (evento->tipo == 2) { 
        }

        // Libere o evento após o processamento
        free(evento);
    }
}

