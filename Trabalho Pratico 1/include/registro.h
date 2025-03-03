#ifndef REGISTRO_H
#define REGISTRO_H

//Definindo os tamanhos máximos para os campos em um registro
#define MAX_NOME 50
#define MAX_CPF 20
#define MAX_ENDERECO 100
#define MAX_OUTROS 100
#define MAX_LINHAS 100

//estrutura que vai armazenar os dados de um registro
typedef struct {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char endereco[MAX_ENDERECO];
    char outros[MAX_OUTROS];
} Registro;

//Estrutura para armazenar indices indiretos para ordenação
typedef struct{
    int indice;
    int posicao;
} IndicePosicao;

//Estrutura principal para armazenar registros e indices para ordenar
typedef struct {
    Registro *registros; //Array dinamico de registros
    int total_registros;
    int capacidade;

    //Arrays dinamicos de indices
    IndicePosicao *indice_por_nome;
    IndicePosicao *indice_por_cpf;
    IndicePosicao *indice_por_endereco;
} MatrizRegistros;

//Funções para manipular MatrizRegistros
MatrizRegistros *criar_matriz_registros(int capacidade_inicial);
IndicePosicao *criar_indices_estaveis(MatrizRegistros *mat);
void expandir_registros_matriz(MatrizRegistros *mat);
void liberar_registros_matriz(MatrizRegistros *mat);
int carregar_arquivo(MatrizRegistros *mat, const char *nome_arquivo);
void inicializar_indices(MatrizRegistros *mat);
void exibir_matriz_registros(MatrizRegistros *mat);
void exibir_ordenado_por_nome(MatrizRegistros *mat);
void exibir_ordenado_por_cpf(MatrizRegistros *mat);
void exibir_ordenado_por_endereco(MatrizRegistros *mat);


#endif 
