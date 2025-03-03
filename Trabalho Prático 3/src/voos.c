#include "../include/voos.h"  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Converte uma string de data no formato "YYYY-MM-DDTHH:MM:SS" para time_t
time_t converter_data(const char* data_str) {
    struct tm tm = {0};  // Inicializa a estrutura tm com zeros

    // Extrai os componentes da data e da hora
    sscanf(data_str, "%d-%d-%dT%d:%d:%d", 
          &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
          &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

    // Ajusta os valores para o formato da struct tm
    tm.tm_year -= 1900;  // Ano desde 1900
    tm.tm_mon -= 1;      // Mês começa em 0 (jan = 0, fev = 1...)

    return mktime(&tm);  // Converte para time_t
}

// Lê um arquivo contendo os voos e os armazena em um vetor dinâmico
Voo* carregar_voos(const char* arquivo, int* n_voos) {
    FILE* fp = fopen(arquivo, "r");  // Abre o arquivo para leitura
    if (!fp) return NULL;  // Se houver erro, retorna NULL

    fscanf(fp, "%d", n_voos);  // Lê o número de voos
    Voo* voos = malloc(*n_voos * sizeof(Voo));  // Aloca memória para os voos

    // Lê os detalhes de cada voo do arquivo
    for (int i = 0; i < *n_voos; i++) {
        fscanf(fp, "%s %s %lf %d %s %s %d", 
              voos[i].org, voos[i].dst, &voos[i].prc, 
              &voos[i].sea, voos[i].dep, voos[i].arr, &voos[i].sto);

        // Converte as datas de partida e chegada para time_t e calcula a duração do voo
        time_t partida = converter_data(voos[i].dep);
        time_t chegada = converter_data(voos[i].arr);
        voos[i].dur = difftime(chegada, partida);
    }

    fclose(fp);  
    return voos;  // Retorna o vetor de voos alocado
}

// Libera a memória alocada para os voos
void liberar_voos(Voo* voos) {
    free(voos);
}
