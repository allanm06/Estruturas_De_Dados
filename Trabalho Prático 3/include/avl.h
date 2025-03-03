#ifndef AVL_H
#define AVL_H

typedef struct NoAVL {
    char chave[20];
    int* indices;
    int tamanho;
    struct NoAVL* esq;
    struct NoAVL* dir;
    int altura;
} NoAVL;

NoAVL* inserir_avl(NoAVL* raiz, const char* chave, int indice);
NoAVL* buscar_avl(NoAVL* raiz, const char* chave);
void liberar_avl(NoAVL* raiz);

#endif