//registro.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/registro.h"

//Função para Criar a Matriz de Registros, O(1)
MatrizRegistros *criar_matriz_registros(int capacidade_inicial) {
    //Alocando memória para a estrutura
    MatrizRegistros *mat = (MatrizRegistros *)malloc(sizeof(MatrizRegistros));
    if (mat == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para MatrizRegistros.\n");
        exit(1);
    }

    //Alocando memória para o array dos registros
    mat->registros = (Registro*)malloc(capacidade_inicial*sizeof(Registro));
    if(mat == NULL){
        fprintf(stderr, "Erro ao alocar memória para Registros!!\n");
        free(mat);
        exit(1);
    }

    //Alocando memória para os indices de ordenação
    mat->indice_por_nome = (IndicePosicao*)malloc(capacidade_inicial*sizeof(IndicePosicao));
    mat->indice_por_cpf = (IndicePosicao*)malloc(capacidade_inicial*sizeof(IndicePosicao));
    mat->indice_por_endereco = (IndicePosicao*)malloc(capacidade_inicial*sizeof(IndicePosicao));
    if(mat->indice_por_nome == NULL || mat->indice_por_cpf == NULL || 
        mat->indice_por_endereco == NULL){
            fprintf(stderr, "Falha ao alocar memória para os indices!!\n");
            free(mat->indice_por_nome);
            free(mat->indice_por_cpf);
            free(mat->indice_por_endereco);
            free(mat);
            exit(1);
        }

    //Inicializando registros e capacidade
    mat->total_registros = 0;
    mat->capacidade = capacidade_inicial;
    
    return (mat);
}

//Função que cria indices estáveis para a ordenação, O(n)
IndicePosicao *criar_indices_estaveis(MatrizRegistros *mat){
    IndicePosicao *indices = (IndicePosicao *)malloc(mat->total_registros * sizeof(IndicePosicao));
    if (!indices) {
        fprintf(stderr, "Erro ao alocar memória para índices.\n");
        exit(EXIT_FAILURE);
    }

    //Inicializando os indices com os valores padrão.
    for (int i = 0; i < mat->total_registros; i++) {
        indices[i].indice = i;    // Índice do registro no array original
        indices[i].posicao = i;   // Posição original
    }

    return (indices);
}

//Função que expandirá a capacidade da matriz de registros (Se necessário) O(n)
void expandir_registros_matriz(MatrizRegistros *mat){
    int capacidade_reajustada = mat->capacidade*2;

    //Realocando a memória para indices e registros
    mat->registros = (Registro*)realloc(mat->registros, capacidade_reajustada*sizeof(Registro));
    mat->indice_por_cpf = (IndicePosicao*)realloc(mat->indice_por_cpf, capacidade_reajustada*sizeof(IndicePosicao));
    mat->indice_por_nome = (IndicePosicao*)realloc(mat->indice_por_nome, capacidade_reajustada*sizeof(IndicePosicao));
    mat->indice_por_endereco = (IndicePosicao*)realloc(mat->indice_por_endereco, capacidade_reajustada*sizeof(IndicePosicao));

    if(mat->registros == NULL || mat->indice_por_cpf == NULL ||
        mat-> indice_por_endereco == NULL || mat->indice_por_endereco == NULL){
            fprintf(stderr, "Falha ao reajustar(expandir) a memória alocada!!\n");
            exit(EXIT_FAILURE);
        }

    //Atualização da capacidade da matriz
    mat->capacidade = capacidade_reajustada;

    
}

//Função que libera (Desaloca) a memória alocada para a matriz O(n)
void liberar_registros_matriz(MatrizRegistros *mat){
    if(mat){
        free(mat->registros);
        free(mat->indice_por_endereco);
        free(mat->indice_por_cpf);
        free(mat->indice_por_nome);
        free(mat);
    }
}


// Função para carregar dados de um arquivo CSV para a matriz, O(n)
int carregar_arquivo(MatrizRegistros *mat, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return (-1);
    }

    char linha[8192];  // Buffer para leitura de uma linha do arquivo

    // Ignorar as primeiras 5 linhas
   for (int i = 0; i < 6; i++) {
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            fprintf(stderr, "Erro ao ignorar as linhas de metadados.\n");
            fclose(arquivo);
            return -1;
        }
    }

    // Lê os dados a partir da sexta linha
    int linha_atual = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (mat->total_registros == mat->capacidade) {
            expandir_registros_matriz(mat);
        }

        Registro *reg = &mat->registros[mat->total_registros];

        // Lê os dados separados por vírgula
        if (sscanf(linha, "%49[^,],%19[^,],%99[^,],%99[^\n]",
                   reg->nome, reg->cpf, reg->endereco, reg->outros) != 4) {
            fprintf(stderr, "Erro ao ler a linha %d: formato inválido.\n", linha_atual + 6);
            fclose(arquivo);
            return -1;
        }


        mat->total_registros++;
        linha_atual++;

        if (mat->total_registros == mat->capacidade) {
        expandir_registros_matriz(mat);
        }

    }

    fclose(arquivo);
    return (0);
}

//Função que faz a inicialização dis indices para a ordenação O(n)
void inicializar_indices(MatrizRegistros *mat){
    mat->indice_por_nome = (IndicePosicao *)malloc(mat->total_registros * sizeof(IndicePosicao));
    mat->indice_por_cpf = (IndicePosicao *)malloc(mat->total_registros * sizeof(IndicePosicao));
    mat->indice_por_endereco = (IndicePosicao *)malloc(mat->total_registros * sizeof(IndicePosicao));

    for(int i = 0; i < mat->total_registros; i++){
        mat->indice_por_nome[i].indice = i;
        mat->indice_por_nome[i].posicao = i;
        mat->indice_por_cpf[i].indice = i;
        mat->indice_por_cpf[i].posicao = i;
        mat->indice_por_endereco[i].indice = i;
        mat->indice_por_endereco[i].posicao = i;
    }
}

// Função para exibir os registros O(n)
void exibir_matriz_registros(MatrizRegistros *mat) {
    printf("Nome\tCPF\tEndereço\tOutros\n");
    for (int i = 0; i < mat->total_registros; i++) {
        printf("%s\t%s\t%s\t%s\n", 
               mat->registros[i].nome,
               mat->registros[i].cpf,
               mat->registros[i].endereco,
               mat->registros[i].outros);
    }
}


//Função para exibir quando ordenado por nome O(n)
void exibir_ordenado_por_nome(MatrizRegistros *mat) {
    printf("4\nname,s\nid,s\naddress,s\npayload,s\n%d\n", mat->total_registros);
    for (int i = 0; i < mat->total_registros; i++) {
        int indice = mat->indice_por_nome[i].indice;
        Registro *reg = &mat->registros[indice];
         printf("%s,%s,%s,%s\n", reg->nome, reg->cpf, reg->endereco, reg->outros);
    }
}

//Função para exibir quando ordenado pelo CPF, O(n)
void exibir_ordenado_por_cpf(MatrizRegistros *mat) {
    printf("4\nname,s\nid,s\naddress,s\npayload,s\n%d\n", mat->total_registros);
    for (int i = 0; i < mat->total_registros; i++) {
        int indice = mat->indice_por_cpf[i].indice;
        Registro *reg = &mat->registros[indice];
        printf("%s,%s,%s,%s\n", reg->nome, reg->cpf, reg->endereco, reg->outros);
    }
}

//Função para exibir quando ordenado pelo Endereço, O(n)
void exibir_ordenado_por_endereco(MatrizRegistros *mat) {
    printf("4\nname,s\nid,s\naddress,s\npayload,s\n%d\n", mat->total_registros);
    for (int i = 0; i < mat->total_registros; i++) {
        int indice = mat->indice_por_endereco[i].indice;
        Registro *reg = &mat->registros[indice];
        printf("%s,%s,%s,%s\n", reg->nome, reg->cpf, reg->endereco, reg->outros);
    }
}



