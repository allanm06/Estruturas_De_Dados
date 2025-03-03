#ifndef SORT_H
#define SORT_H
#include "registro.h"

//Funções para obter caracteres e comparar chaves
int comparacao_chave_nome(int indice_a, int indice_b, MatrizRegistros *mat);
int comparacao_chave_endereco(int indice_a, int indice_b, MatrizRegistros *mat);
int comparacao_chave_cpf(int indice_a, int indice_b, MatrizRegistros *mat);

//Funções de ordenação
void quick_sort(IndicePosicao indices[], int baixo, int alto, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *));
int particionar(IndicePosicao indices[], int baixo, int alto, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *));
void merge_sort(IndicePosicao indices[], int esq, int dir, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *));
void merge(IndicePosicao indices[], int esq, int meio, int dir, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros*));
void heapify(IndicePosicao indices[], int n, int i, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *));
void heap_sort(IndicePosicao indices[], int n, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *));

#endif