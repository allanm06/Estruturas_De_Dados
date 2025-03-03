#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "voos.h"

typedef int (*ComparadorVoos)(const Voo*, const Voo*);
void quick_sort(Voo* vetor, int inicio, int fim, ComparadorVoos cmp);

#endif