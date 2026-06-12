#pragma once // Evita que este archivo .h sea incluido más de una vez

#include "instance.h"
#include "solucion.h"

// Búsqueda local por intercambio de asignaciones
void swap_busqueda_local(GAPSolution& sol, const GAPInstance& inst);

// Búsqueda local por reasignación de un cliente
void relocate_busqueda_local(GAPSolution& sol, const GAPInstance& inst);