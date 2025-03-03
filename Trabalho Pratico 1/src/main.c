/*
main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/registro.h"
#include "../include/sort.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo.xcsv>\n", argv[0]);
        return 1;
    }

    const char *nome_arquivo = argv[1];
    int capacidade_inicial = 100; // capacidade inicial para os registros
    MatrizRegistros *mat = criar_matriz_registros(capacidade_inicial);

    if (carregar_arquivo(mat, nome_arquivo) != 0) {
        fprintf(stderr, "Erro ao carregar o arquivo: %s\n", nome_arquivo);
        liberar_registros_matriz(mat);
        return 1;
    }

    inicializar_indices(mat);

    // Realiza as ordenações e exibe as saídas no formato pedido
    quick_sort(mat->indice_por_nome, 0, mat->total_registros - 1, mat, comparacao_chave_nome);
    exibir_ordenado_por_nome(mat);

    quick_sort(mat->indice_por_cpf, 0, mat->total_registros - 1, mat, comparacao_chave_cpf);
    exibir_ordenado_por_cpf(mat);

    quick_sort(mat->indice_por_endereco, 0, mat->total_registros - 1, mat, comparacao_chave_endereco);
    exibir_ordenado_por_endereco(mat);

    merge_sort(mat->indice_por_nome, 0, mat->total_registros - 1, mat, comparacao_chave_nome);
    exibir_ordenado_por_nome(mat);

    merge_sort(mat->indice_por_cpf, 0, mat->total_registros - 1, mat, comparacao_chave_cpf);
    exibir_ordenado_por_cpf(mat);

    merge_sort(mat->indice_por_endereco, 0, mat->total_registros - 1, mat, comparacao_chave_endereco);
    exibir_ordenado_por_endereco(mat);

    heap_sort(mat->indice_por_nome, mat->total_registros, mat, comparacao_chave_nome);
    exibir_ordenado_por_nome(mat);

    heap_sort(mat->indice_por_cpf, mat->total_registros, mat, comparacao_chave_cpf);
    exibir_ordenado_por_cpf(mat);

    heap_sort(mat->indice_por_endereco, mat->total_registros, mat, comparacao_chave_endereco);
    exibir_ordenado_por_endereco(mat);

    liberar_registros_matriz(mat);
    return 0;
}
