#ifndef LEITOR_DE_CSV_H
#define LEITOR_DE_CSV_H

#include "procedimento.h"
#include "paciente.h"

void lerEntrada(const char *arquivo, Procedimento **procedimentos, int *num_pacientes, Paciente **pacientes);

#endif
