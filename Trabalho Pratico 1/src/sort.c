/*
sort.c
*/

#include <string.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/registro.h"


//Função qie vai comparar os nomes, se baseia nos 9 primeiros caracteres
int comparacao_chave_nome(int indice_a, int indice_b, MatrizRegistros *mat){
    const char *nome_a = mat->registros[indice_a].nome;
    const char *nome_b = mat->registros[indice_b].nome;

    for(int i = 0; i < 10; i++){
        if(nome_a[i] != nome_b[i]){
            return(nome_a[i]-nome_b[i]);
        }
    }

    return (0);
}

//Função que comprara os endereços, também se baseia nos 9 primeiros caracteres
int comparacao_chave_endereco(int indice_a, int indice_b, MatrizRegistros *mat){
    const char *endereco_a = mat->registros[indice_a].endereco;
    const char *endereco_b = mat->registros[indice_b].endereco;

    for (int i = 0; i < 10; i++) {
        if (endereco_a[i] != endereco_b[i]) {
            return endereco_a[i] - endereco_b[i];
        }
    }
    return (0);
}

//Função que vai comparar os CPFS com base nos 8 primeiros caracteres
int comparacao_chave_cpf(int indice_a, int indice_b, MatrizRegistros *mat) {
    // Obtém os CPFs correspondentes aos índices
    const char *cpf_a = mat->registros[indice_a].cpf;
    const char *cpf_b = mat->registros[indice_b].cpf;

    int valor_a = 0, valor_b = 0;

    for (int i = 0; i < 9; i++) {
        valor_a = valor_a * 10 + (cpf_a[i] - '0');
        valor_b = valor_b * 10 + (cpf_b[i] - '0');
    }

    return (valor_a - valor_b);
}

//Função para particionar o array no Quicksort
int particionar(IndicePosicao indices[], int baixo, int alto, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *)){
    IndicePosicao pivo = indices[alto]; //escolhendo o último elemento como pivô
    int i = (baixo - 1);//indice para particionar os menores elementos

    //percorrendo array até chegar no pivô
    for(int j = baixo; j < alto; j++){
        if(comparar(indices[j].indice, pivo.indice, mat) < 0){//comparando com o pivô
            i++;
            //Trocando os elementos para reposicionar o menor antes do pivô
            IndicePosicao aux = indices[i];
            indices[i] = indices[j];
            indices[j] = aux;
        }
    }
    //Colocando o pivô em sua posição final
    IndicePosicao aux = indices[i + 1];
    indices[i + 1] = indices[alto];
    indices[alto] = aux;

    return (i + 1);//retorno da posição final do pivô
}

/*implementação do Quicksort
Pior caso: O(n²)
Melhor caso O(n log n)
*/
void quick_sort(IndicePosicao indices[], int baixo, int alto, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *)){
    if(baixo < alto){//Conferindo se há mais de um elemento pra ordenar
        //Particionando o array
        int pivo = particionar(indices, baixo, alto, mat, comparar);

        //apicando o quicksort a esquerda e a direita do pivo, de forma recursiva
        quick_sort(indices, baixo, pivo-1, mat, comparar);
        quick_sort(indices, pivo+1, alto, mat, comparar);
    }
}

/*implementação do mergesort
Em todos os casos : O(n log n)
*/
void merge_sort(IndicePosicao indices[], int esq, int dir, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *)){
    int meio = 0;
    if(esq < dir){//Verificando se há mais de um elemento pra ordenar
        meio = esq+(dir-esq)/2; 

        //Aplicando recursivamente o Merge nas metades esquerda e direita
        merge_sort(indices, esq, meio, mat, comparar);
        merge_sort(indices, meio + 1, dir, mat, comparar);

        //Junção das metadrs ordenadas
        merge(indices, esq, meio, dir, mat, comparar);
    } 
}

//Função para intercalar no Mergesort
void merge(IndicePosicao indices[], int esq, int meio, int dir, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros*)){
    int nx = meio - esq + 1;
    int ny = dir - meio;

    // Criando arrays temporários
    int L[nx], R[ny];

    // Copiando os dados para os arrays temporários
    for (int i = 0; i < nx; i++){
        L[i] = indices[esq + i].indice;
        }
    for (int j = 0; j < ny; j++){
        R[j] = indices[meio + 1 + j].indice;
        }

    // Intercalando os arrays temporários de volta para registros[]
    int i = 0, j = 0, k = esq;
    while (i < nx && j < ny) {
        if (comparar(L[i], R[j], mat) <= 0) {
            indices[k].indice = L[i];
            i++;
        } else {
            indices[k].indice = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < nx) {
        indices[k].indice = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < ny) {
        indices[k].indice = R[j];
        j++;
        k++;
    }
}

//Função para a construção do heap, (subprocesso do heapsort), O(n)
void heapify(IndicePosicao indices[], int n, int i, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *)){

    int maior = i; // inicializa o maior como raiz
    int esquerda = 2 * i + 1; // Filho esquerda
    int direita = 2 * i + 2; // Filho direita

    // se o filho a esquerda ou a direita é maior que a raiz
    if (esquerda < n && comparar(indices[esquerda].posicao, indices[maior].posicao, mat) > 0) {maior = esquerda;}
    if (direita < n && comparar(indices[direita].posicao, indices[maior].posicao, mat) > 0) {maior = direita;}

    // te o maior não é a raiz
    if (maior != i) {
        // troca a raiz com o maior
        IndicePosicao aux = indices[i];
        indices[i] = indices[maior];
        indices[maior] = aux;

        // aplicando de forma recursiva o heapify na subárvore
        heapify(indices, n, maior, mat, comparar);
    }
}

//implementação do heapsort,  O(n log n) sempre
void heap_sort(IndicePosicao indices[], int n, MatrizRegistros *mat, int (*comparar)(int, int, MatrizRegistros *)){
    // constrói o inicial com base no array
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(indices, n, i, mat, comparar);
    }

    // extraindo elementos do Heap um por um
    for (int i = n - 1; i > 0; i--) {
        //movendo raiz (maior elemento) até o final
        IndicePosicao aux = indices[0];
        indices[0] = indices[i];
        indices[i] = aux;

        // chama heapify no heap reduzido
        heapify(indices, i, 0, mat, comparar);
    }
}

