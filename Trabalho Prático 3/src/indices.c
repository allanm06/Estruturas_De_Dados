#include "../include/indices.h"
#include "../include/avl.h"
#include "../include/voos.h"
#include "../include/quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//  -----Funções auxiliares para manipulação de strings------


// Remove caracteres específicos indesejados de uma string
void remover_caracteres_especiais(char* str, const char* indesejados) {
    char* destino = str;
    while (*str) {
        if (!strchr(indesejados, *str)) {
            *destino++ = *str;
        }
        str++;
    }
    *destino = '\0';
}

// Extrai condições de uma expressão lógica no formato "((cond1)&&(cond2))
void extrair_condicoes(const char* filtro, char condicoes[][50], int* total) {
    char expressao[200];
    strcpy(expressao, filtro);
    *total = 0;

    remover_caracteres_especiais(expressao, " "); // Remove espaços desnecessários

    char* inicio = expressao;
    char* fim;
    while ((fim = strstr(inicio, "&&")) != NULL && *total < 4) {
        *fim = '\0';
        strcpy(condicoes[(*total)++], inicio);
        inicio = fim + 2;
    }
    if (*inicio != '\0' && *total < 4) {
        strcpy(condicoes[(*total)++], inicio);
    }
}


// ----Função de verificação de condições em voos ----

// Verifica se um voo atende a uma determinada condição de filtragem
bool verificar_condicao(Voo* voo, const char* condicao) {
    
    char campo[10], operador[3] = "", valor[50];
    char cond_limpa[100];
    
    strcpy(cond_limpa, condicao);
    remover_caracteres_especiais(cond_limpa, "() ");
    
    // Identifica a posição do operador na condição
    char* pos_operador = strpbrk(cond_limpa, "<>!=");
    if (!pos_operador) return false;

    // Extrair campo
    strncpy(campo, cond_limpa, pos_operador - cond_limpa);
    campo[pos_operador - cond_limpa] = '\0';

    // Extrair operador
    if (*(pos_operador + 1) == '=' || *(pos_operador + 1) == '>') {
        strncpy(operador, pos_operador, 2);
        operador[2] = '\0';
        strcpy(valor, pos_operador + 2);
    } else {
        strncpy(operador, pos_operador, 1);
        operador[1] = '\0';
        strcpy(valor, pos_operador + 1);
    }

    // Verificação da condição para diferentes campos
    if (strcmp(campo, "org") == 0){ 
        if (strcmp(operador, "!=") == 0) return strcmp(voo->org, valor) != 0;
        if (strcmp(operador, "==") != 0) return false; 
        return strcmp(voo->org, valor) == 0;
    }
    
    if (strcmp(campo, "dst") == 0){
        if (strcmp(operador, "!=") == 0) return strcmp(voo->dst, valor) != 0; 
        if (strcmp(operador, "==") != 0) return false; 
        return strcmp(voo->dst, valor) == 0;
    }
    
    if (strcmp(campo, "prc") == 0) {
        double prc_voo = voo->prc;
        double prc_valor = atof(valor);
        if (strcmp(operador, ">=") == 0) return prc_voo >= prc_valor;
        if (strcmp(operador, "<=") == 0) return prc_voo <= prc_valor;
    }
    if (strcmp(campo, "sea") == 0) {
        int valor_num = atoi(valor);
        if (strcmp(operador, ">=") == 0) return voo->sea >= valor_num;
        if (strcmp(operador, "==") == 0) return voo->sea == valor_num;
    }
    if (strcmp(campo, "sto") == 0) {
        int valor_num = atoi(valor);
        if (strcmp(operador, "<=") == 0) return voo->sto <= valor_num;
        if (strcmp(operador, ">=") == 0) return voo->sto >= valor_num;
    }
    if (strcmp(campo, "dur") == 0) {
        double valor_num = atof(valor);
        if (strcmp(operador, ">=") == 0) return voo->dur >= valor_num;
        if (strcmp(operador, "<=") == 0) return voo->dur <= valor_num;
    }

    return false;
}


// -----Funções de comparação para ordenação-------


int comparar_pds(const Voo* a, const Voo* b) {
    int cmp = (a->prc > b->prc) - (a->prc < b->prc);
    if (cmp != 0) return cmp;
    cmp = (a->dur > b->dur) - (a->dur < b->dur);
    if (cmp != 0) return cmp;
    return (a->sto > b->sto) - (a->sto < b->sto);
}

int comparar_dps(const Voo* a, const Voo* b) {
    int cmp = (a->dur > b->dur) - (a->dur < b->dur);
    if (cmp != 0) return cmp;
    cmp = (a->prc > b->prc) - (a->prc < b->prc);
    if (cmp != 0) return cmp;
    return (a->sto > b->sto) - (a->sto < b->sto);
}

int comparar_psd(const Voo* a, const Voo* b) {
    int cmp = (a->prc > b->prc) - (a->prc < b->prc);
    if (cmp != 0) return cmp;
    cmp = (a->sto > b->sto) - (a->sto < b->sto);
    if (cmp != 0) return cmp;
    return (a->dur > b->dur) - (a->dur < b->dur);
}

int comparar_spd(const Voo* a, const Voo* b) {
    int cmp = (a->sto > b->sto) - (a->sto < b->sto);
    if (cmp != 0) return cmp;
    cmp = (a->prc > b->prc) - (a->prc < b->prc);
    if (cmp != 0) return cmp;
    return (a->dur > b->dur) - (a->dur < b->dur);
}

int comparar_sdp(const Voo* a, const Voo* b) {
    int cmp = (a->sto > b->sto) - (a->sto < b->sto);
    if (cmp != 0) return cmp;
    cmp = (a->dur > b->dur) - (a->dur < b->dur);
    if (cmp != 0) return cmp;
    return (a->prc > b->prc) - (a->prc < b->prc);
}

int comparar_dsp(const Voo* a, const Voo* b) {
    int cmp = (a->dur > b->dur) - (a->dur < b->dur);
    if (cmp != 0) return cmp;
    cmp = (a->sto > b->sto) - (a->sto < b->sto);
    if (cmp != 0) return cmp;
    return (a->prc > b->prc) - (a->prc < b->prc);
}

ComparadorVoos criar_comparador(const char* criterio) {
    if (strcmp(criterio, "pds") == 0) return comparar_pds;
    if (strcmp(criterio, "dps") == 0) return comparar_dps;
    if (strcmp(criterio, "psd") == 0) return comparar_psd;
    if (strcmp(criterio, "spd") == 0) return comparar_spd;
    if (strcmp(criterio, "sdp") == 0) return comparar_sdp;
    if (strcmp(criterio, "dsp") == 0) return comparar_dsp;
    return comparar_pds;
}

Indices criar_indices(Voo* voos, int n_voos) {
    Indices indices = {NULL};
    for (int i = 0; i < n_voos; i++) {
        char chave[20];
        // Org
        indices.org = inserir_avl(indices.org, voos[i].org, i);
        // Dst
        indices.dst = inserir_avl(indices.dst, voos[i].dst, i);
        // Prc
        snprintf(chave, 20, "%.2f", voos[i].prc);
        indices.prc = inserir_avl(indices.prc, chave, i);
        // Sea
        snprintf(chave, 20, "%d", voos[i].sea);
        indices.sea = inserir_avl(indices.sea, chave, i);
        // Dep/Arr
        indices.dep = inserir_avl(indices.dep, voos[i].dep, i);
        indices.arr = inserir_avl(indices.arr, voos[i].arr, i);
        // Sto
        snprintf(chave, 20, "%d", voos[i].sto);
        indices.sto = inserir_avl(indices.sto, chave, i);
    }
    return indices;
}

//Liberar indices
void liberar_indices(Indices indices) {
    liberar_avl(indices.org);
    liberar_avl(indices.dst);
    liberar_avl(indices.prc);
    liberar_avl(indices.sea);
    liberar_avl(indices.dep);
    liberar_avl(indices.arr);
    liberar_avl(indices.sto);
}



void processar_consulta(Indices* indice, Voo* voos, int n_voos, int max_voos,
                       const char* criterio_ordenacao, const char* expressao_filtro) {
    char condicoes[4][50];
    int total_condicoes;
    extrair_condicoes(expressao_filtro, condicoes, &total_condicoes);

    Voo* voos_filtrados = malloc(n_voos * sizeof(Voo));
    int contador = 0;

    // Filtragem
    for (int i = 0; i < n_voos; i++) {
        bool atende = true;
        for (int j = 0; j < total_condicoes; j++) {
            if (!verificar_condicao(&voos[i], condicoes[j])) {
                atende = false;
                break;
            }
        }
        if (atende) voos_filtrados[contador++] = voos[i];
    }

    // Ordenação
    if (strlen(criterio_ordenacao) == 3) {
        ComparadorVoos cmp = criar_comparador(criterio_ordenacao);
        quick_sort(voos_filtrados, 0, contador-1, cmp);
    }

    // Saída formatada
    printf("%d %s %s\n", max_voos, criterio_ordenacao, expressao_filtro);
    for (int i = 0; i < contador && i < max_voos; i++) {
        Voo v = voos_filtrados[i];
        
        // Formatação do preço sem zeros desnecessários
        char prc_str[20];
        snprintf(prc_str, sizeof(prc_str), "%.2f", v.prc);
        char* dot = strchr(prc_str, '.');
        if (dot != NULL) {
            while (prc_str[strlen(prc_str)-1] == '0') {
                prc_str[strlen(prc_str)-1] = '\0';
            }
            if (prc_str[strlen(prc_str)-1] == '.') {
                prc_str[strlen(prc_str)-1] = '\0';
            }
        }
        
        printf("%s %s %s %d %s %s %d\n", 
              v.org, v.dst, prc_str, v.sea, v.dep, v.arr, v.sto);
    }

    free(voos_filtrados);
}


//Liberar AVL
void liberar_indice(NoAVL* no) {
    if (no == NULL) return;
    liberar_indice(no->esq);
    liberar_indice(no->dir);
    free(no->indices);
    free(no);
}