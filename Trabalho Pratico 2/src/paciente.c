#include "paciente.h"
#include <string.h>

// Função para inicializar um paciente
void inicializarPaciente(Paciente *p, int id, int alta, struct tm chegada, int grau_urgencia, int *procedimentos) {
    // Inicializa os campos do paciente com os valores passados
    p->id = id; 
    p->alta = alta;  // Atribui o status de alta (se o paciente teve alta ou não)
    p->chegada = chegada;  // Atribui a data e hora de chegada (estrutura tm)
    p->grau_urgencia = grau_urgencia;  // Atribui o grau de urgência do paciente
    
    // Copia os dados dos procedimentos para o campo 'procedimentos' do paciente
    memcpy(p->procedimentos, procedimentos, 4 * sizeof(int));
    
    // Inicializa os tempos de atendimento, espera e total como 0
    p->tempo_total = 0; 
    p->tempo_atendimento = 0;  
    p->tempo_espera = 0;  
}
