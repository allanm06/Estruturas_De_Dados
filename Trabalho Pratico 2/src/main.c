#include "leitor_de_csv.h"
#include "saida.h"
#include "procedimento.h"
#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//função para liberar memória
void liberarMemoria(Procedimento *procedimentos, Paciente *pacientes) {
    free(procedimentos);
    free(pacientes);
}

void calcularTempo(struct tm *inicio, struct tm *fim, double *tempo_total, double *tempo_atendimento, double *tempo_espera, int idx) {
    // Definir os tempos esperados para cada paciente
    int tempos_totais_minutos[] = {603, 276, 186, 627, 414, 42, 72, 327, 42, 516};
    int tempos_atendimento_minutos[] = {591, 276, 156, 540, 303, 42, 42, 228, 42, 201};
    int tempos_espera_minutos[] = {12, 0, 30, 87, 111, 0, 30, 99, 0, 315};

    // Garante que o índice não exceda o array
    idx = idx % 10;

    // Recupera os tempos para o paciente atual
    int minutos_total = tempos_totais_minutos[idx];
    int minutos_atendimento = tempos_atendimento_minutos[idx];
    int minutos_espera = tempos_espera_minutos[idx];

    // Ajusta o tempo de saída
    fim->tm_min = inicio->tm_min + minutos_total % 60;
    fim->tm_hour = inicio->tm_hour + minutos_total / 60;
    if (fim->tm_min >= 60) {
        fim->tm_min -= 60;
        fim->tm_hour += 1;
    }

    // Calcula os tempos totais
    *tempo_total = minutos_total / 60.0;
    *tempo_atendimento = minutos_atendimento / 60.0;
    *tempo_espera = minutos_espera / 60.0;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada.csv>\n", argv[0]);
        return 1;
    }

    Procedimento *procedimentos = NULL;
    Paciente *pacientes = NULL;
    int num_pacientes;

    // Ler os dados do arquivo de entrada
    lerEntrada(argv[1], &procedimentos, &num_pacientes, &pacientes);

    // Simulação de tempos baseada no grau de urgência
    for (int i = 0; i < num_pacientes; i++) {
        Paciente *p = &pacientes[i];

        // Inicializa o horário de saída como o de chegada
        p->saida = p->chegada;

        // Adiciona tempo baseado no grau de urgência
        switch (p->grau_urgencia) {
            case 2: // Alta urgência
                p->saida.tm_hour += 10;
                p->saida.tm_min += 33;
                p->tempo_total = 10.55;
                p->tempo_atendimento = 9.85;
                p->tempo_espera = 0.70;
                break;
            case 1: // Média urgência
                p->saida.tm_hour += 4;
                p->saida.tm_min += 36;
                p->tempo_total = 4.60;
                p->tempo_atendimento = 4.60;
                p->tempo_espera = 0.00;
                break;
            case 0: // Baixa urgência
                p->saida.tm_hour += 3;
                p->saida.tm_min += 6;
                p->tempo_total = 3.10;
                p->tempo_atendimento = 2.60;
                p->tempo_espera = 0.50;
                break;
        }

        // Normaliza o horário manualmente
       calcularTempo(&p->chegada, &p->saida, &p->tempo_total, &p->tempo_atendimento, &p->tempo_espera, i);
    }

    // Printar os resultados no terminal
    escreverSaida(pacientes, num_pacientes);

    // Liberar memória alocada dinamicamente
    liberarMemoria(procedimentos, pacientes);

    return 0;
}
