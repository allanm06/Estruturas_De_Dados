#include "../include/avl.h"  
#include <stdlib.h>
#include <string.h>

// Retorna a altura do nó. Se o nó for NULL, retorna 0.
int altura(NoAVL* no) {
    return no ? no->altura : 0;
}

// Retorna o maior entre dois valores inteiros.
int max(int a, int b) {
    return a > b ? a : b;
}

// Cria um novo nó AVL com a chave fornecida e um índice associado.
NoAVL* novo_no(const char* chave, int indice) {
    NoAVL* no = malloc(sizeof(NoAVL));
    strcpy(no->chave, chave);  // Copia a chave para o nó
    no->indices = malloc(sizeof(int));  // Aloca memória para armazenar índices
    no->indices[0] = indice;  // Armazena o primeiro índice
    no->tamanho = 1;  // Inicializa a quantidade de índices
    no->esq = no->dir = NULL;  // Define os filhos como NULL
    no->altura = 1;  // Inicializa a altura como 1
    return no;
}

// Rotação para a direita para balanceamento da AVL
NoAVL* rotacao_direita(NoAVL* y) {
    NoAVL* x = y->esq;
    NoAVL* T2 = x->dir;

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza as alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;  // Retorna o novo nó raiz
}

// Rotação para a esquerda para balanceamento da AVL
NoAVL* rotacao_esquerda(NoAVL* x) {
    NoAVL* y = x->dir;
    NoAVL* T2 = y->esq;

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza as alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;  // Retorna o novo nó raiz
}

// Insere um novo nó na árvore AVL
NoAVL* inserir_avl(NoAVL* no, const char* chave, int indice) {
    // Caso base: se o nó for NULL, cria um novo nó
    if (!no) return novo_no(chave, indice);

    // Compara a chave para decidir para onde inserir
    int cmp = strcmp(chave, no->chave);
    if (cmp < 0) {
        no->esq = inserir_avl(no->esq, chave, indice);
    } else if (cmp > 0) {
        no->dir = inserir_avl(no->dir, chave, indice);
    } else {
        // Chave já existe: adiciona o índice ao vetor de índices do nó
        no->tamanho++;
        no->indices = realloc(no->indices, no->tamanho * sizeof(int));
        no->indices[no->tamanho - 1] = indice;
        return no;  // Retorna o nó sem balancear, pois a estrutura não mudou
    }

    // Atualiza a altura do nó
    no->altura = 1 + max(altura(no->esq), altura(no->dir));

    // Obtém o fator de balanceamento para decidir se é necessário rebalancear
    int balance = altura(no->esq) - altura(no->dir);

    // Rotação Simples Direita (caso de desbalanceamento à esquerda)
    if (balance > 1 && strcmp(chave, no->esq->chave) < 0)
        return rotacao_direita(no);

    // Rotação Simples Esquerda (caso de desbalanceamento à direita)
    if (balance < -1 && strcmp(chave, no->dir->chave) > 0)
        return rotacao_esquerda(no);

    // Rotação Dupla Esquerda-Direita (caso de desbalanceamento à esquerda e à direita)
    if (balance > 1 && strcmp(chave, no->esq->chave) > 0) {
        no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }

    // Rotação Dupla Direita-Esquerda (caso de desbalanceamento à direita e à esquerda)
    if (balance < -1 && strcmp(chave, no->dir->chave) < 0) {
        no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }

    return no;  // Retorna o nó atualizado
}

// Busca um nó na AVL com a chave especificada
NoAVL* buscar_avl(NoAVL* raiz, const char* chave) {
    if (!raiz) return NULL;  // Retorna NULL se a chave não for encontrada

    int cmp = strcmp(chave, raiz->chave);
    if (cmp < 0) return buscar_avl(raiz->esq, chave);
    if (cmp > 0) return buscar_avl(raiz->dir, chave);
    
    return raiz;  // Retorna o nó se a chave foi encontrada
}

// Libera a memória ocupada pela árvore AVL
void liberar_avl(NoAVL* raiz) {
    if (!raiz) return;  // Caso base: árvore vazia

    // Libera os filhos recursivamente
    liberar_avl(raiz->esq);
    liberar_avl(raiz->dir);

    // Libera a memória dos índices e do nó
    free(raiz->indices);
    free(raiz);
}
