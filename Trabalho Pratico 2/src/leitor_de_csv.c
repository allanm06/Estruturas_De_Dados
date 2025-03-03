#include "leitor_de_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função que irá ler o arquivo csv
void lerEntrada(const char *arquivo, Procedimento **procedimentos, int *num_pacientes, Paciente **pacientes) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Alocando dinamicamente a lista de procedimentos
    *procedimentos = (Procedimento *)malloc(6 * sizeof(Procedimento));
    if (*procedimentos == NULL) {
        perror("Erro ao alocar memória para procedimentos");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // Aqui lemos os dados do procedimentos
    for (int i = 0; i < 6; i++) {
        double duracao;
        int capacidade;
        fscanf(fp, "%lf %d", &duracao, &capacidade);
        inicializarProcedimento(&(*procedimentos)[i], "Procedimento", capacidade, duracao);
    }

    // Ler o número de pacientes
    fscanf(fp, "%d", num_pacientes);

    // Alocando dinamicamente a lista de pacientes
    *pacientes = (Paciente *)malloc(*num_pacientes * sizeof(Paciente));
    if (*pacientes == NULL) {
        perror("Erro ao alocar memória para pacientes");
        free(*procedimentos);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // Lendo os dados dos pacientes
    for (int i = 0; i < *num_pacientes; i++) {
        int id, alta, ano, mes, dia, hora, grau_urgencia;
        int procedimentos_array[4];

        fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d",
               &id, &alta, &ano, &mes, &dia, &hora, &grau_urgencia,
               &procedimentos_array[0], &procedimentos_array[1],
               &procedimentos_array[2], &procedimentos_array[3]);

        // Inicializando a estrutura `tm` corretamente
        struct tm chegada = {0};
        chegada.tm_year = ano - 1900; // Ajustar o ano
        chegada.tm_mon = mes - 1;     // Ajustar o mês (0 = janeiro)
        chegada.tm_mday = dia;        // Dia do mês
        chegada.tm_hour = hora;       // Hora
        chegada.tm_min = 0;           // Minutos
        chegada.tm_sec = 0;           // Segundos
        chegada.tm_isdst = -1;        // Ajuste automático de horário de verão

        // Normalizando a data e calcular o dia da semana
        mktime(&chegada);

        // Inicializar o paciente
        inicializarPaciente(&(*pacientes)[i], id, alta, chegada, grau_urgencia, procedimentos_array);
    }

    fclose(fp);
}

