#include "saida.h"
#include <stdio.h>
#include <time.h>

void escreverSaida(Paciente pacientes[], int num_pacientes) {
    for (int i = 0; i < num_pacientes; i++) {
        Paciente *p = &pacientes[i];

        // Convertendo horários para string
        char admissao[64], alta[64];
        strftime(admissao, sizeof(admissao), "%a %b %d %H:%M:%S %Y", &p->chegada);
        strftime(alta, sizeof(alta), "%a %b %d %H:%M:%S %Y", &p->saida);
        
        //Printando os dados
        printf("%06d %s %s %.2f %.2f %.2f\n", 
               p->id, admissao, alta, 
               p->tempo_total, p->tempo_atendimento, p->tempo_espera);
    }
}

