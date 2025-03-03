#include <stdio.h>
#include <stdlib.h>
#include "../include/voos.h"
#include "../include/indices.h"
#include "../include/avl.h"
#include "../include/quicksort.h"


int main(int argc, char *argv[]) {
    // Verifica se o usuário passou o arquivo como argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo.txt>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo indicado na linha de comando
    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int n_voos;
    // Lê o número de voos
    if (fscanf(arquivo, "%d", &n_voos) != 1) {
        fprintf(stderr, "Erro ao ler o número de voos\n");
        fclose(arquivo);
        return 1;
    }

    // Aloca memória para os voos
    Voo* voos = malloc(n_voos * sizeof(Voo));
    if (!voos) {
        fprintf(stderr, "Erro ao alocar memória para os voos\n");
        fclose(arquivo);
        return 1;
    }

    // Carrega os dados de cada voo
    for (int i = 0; i < n_voos; i++) {
        if (fscanf(arquivo, "%s %s %lf %d %s %s %d", 
                   voos[i].org, voos[i].dst, &voos[i].prc, 
                   &voos[i].sea, voos[i].dep, voos[i].arr, &voos[i].sto) != 7) {
            fprintf(stderr, "Erro ao ler os dados do voo %d\n", i);
            fclose(arquivo);
            free(voos);
            return 1;
        }
        // Calcula a duração do voo
        time_t partida = converter_data(voos[i].dep);
        time_t chegada = converter_data(voos[i].arr);
        voos[i].dur = difftime(chegada, partida);
    }

    // Cria os índices a partir dos voos carregados
    Indices indices = criar_indices(voos, n_voos);

    int num_consultas;
    // Lê o número de consultas
    if (fscanf(arquivo, "%d", &num_consultas) != 1) {
        fprintf(stderr, "Erro ao ler o número de consultas\n");
        fclose(arquivo);
        liberar_voos(voos);
        liberar_indices(indices);
        return 1;
    }

    // Processa cada consulta
    for (int i = 0; i < num_consultas; i++) {
        int max_voos;
        char criterio[4];
        char filtro[100];
        
        if (fscanf(arquivo, "%d %3s %[^\n]", &max_voos, criterio, filtro) < 2) {
            fprintf(stderr, "Erro ao ler a consulta %d\n", i);
            continue;  // ou break, dependendo da estratégia de tratamento de erro
        }
        processar_consulta(&indices, voos, n_voos, max_voos, criterio, filtro);
    }

    // Libera os recursos utilizados
    fclose(arquivo);
    liberar_voos(voos);
    liberar_indices(indices);

    return 0;
}