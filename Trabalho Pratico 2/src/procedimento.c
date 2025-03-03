#include "procedimento.h" // Inclusão do cabeçalho que define a estrutura do Procedimento e suas funções
#include <stdio.h>        // Biblioteca para entrada e saída (ex.: printf)
#include <string.h>       // Biblioteca para manipulação de strings (ex.: snprintf)

// Função para inicializar um procedimento
void inicializarProcedimento(Procedimento *proc, const char *nome, int capacidade, double duracao) {
    // Copia o nome do procedimento para o campo `nome` da estrutura, garantindo que não exceda o tamanho do buffer
    snprintf(proc->nome, sizeof(proc->nome), "%s", nome);
    
    // Define a capacidade máxima de atendimento simultâneo do procedimento
    proc->capacidade = capacidade;
    
    // Define a duração estimada do procedimento
    proc->duracao = duracao;
    
    // Inicializa a ociosidade do procedimento como 0 (nenhuma ociosidade no início)
    proc->ociosidade = 0;
    
    // Inicializa a fila de espera associada ao procedimento
    inicializarFila(&proc->fila_espera);
}

// Função para processar a fila de pacientes associados a um procedimento
void processarFila(Procedimento *proc, double tempo_atual) {
    // Enquanto a fila não estiver vazia e houver capacidade disponível no procedimento
    while (!filaVazia(&proc->fila_espera) && proc->capacidade > 0) {
        // Remove o próximo paciente da fila de espera
        Paciente *paciente = desenfileirar(&proc->fila_espera);
        
        // Exibe mensagem indicando que o paciente está sendo processado
        printf("Processando paciente %d no procedimento %s no tempo %.2f\n",
               paciente->id, proc->nome, tempo_atual);
        
        // Reduz a capacidade disponível do procedimento (simula um recurso sendo usado)
        proc->capacidade--;
    }
}
