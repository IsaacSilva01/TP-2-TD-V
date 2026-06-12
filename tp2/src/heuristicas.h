#pragma once // Evita que este archivo .h sea incluido más de una vez

#include "instance.h"
#include "solucion.h"

GAPSolution greedy_por_vendedores(const GAPInstance& inst); 

GAPSolution greedy_por_deposito(const GAPInstance& inst);

GAPSolution greedy_randomizado(const GAPInstance& inst, int k);