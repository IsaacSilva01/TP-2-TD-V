#include "solucion.h"

// Definición del Constructor de la clase
GAPSolution::GAPSolution(const GAPInstance& inst) {
    asignacion.assign(inst.getn(), -1); 
    capacidad_residual.resize(inst.getm());
    for(int i = 0; i < inst.getm(); i++) {
        capacidad_residual[i] = inst.getcapacidad(i);
    }
    costo_total = 0.0;
}

// Definición del método para verificar espacio libre
bool GAPSolution::es_factible_asignar(int vendedor, int deposito, const GAPInstance& inst) {

    // si el destino es la posición 'm' (no asignados), no consume capacidad
    if (deposito == inst.getm()) return true;

    float dem = inst.getdemanda(deposito, vendedor);
    return capacidad_residual[deposito] >= dem;
}

// método para aplicar una asignación
void GAPSolution::asignar(int vendedor, int deposito, const GAPInstance& inst) {
    // asigna el depósito al vendedor
    asignacion[vendedor] = deposito;

    // si no es el depósito ficticio que nos creamos, le restamos la capacidad y sumamos el costo
    if (deposito < inst.getm()) {
        capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
        costo_total += inst.getcosto(deposito, vendedor);
}   
    else{
        // va al depósito ficticio (deposito ficticio = m): se queda en -1 y no altera costos ni capacidades reales
        asignacion[vendedor] = -1;
    }
}

void GAPSolution::relocate(int vendedor, int deposito, const GAPInstance& inst){
    if ( asignacion[vendedor]!=deposito && es_factible_asignar(vendedor, deposito, inst)){ 
        int deposito_anterior = asignacion[vendedor];
        asignacion[vendedor]= deposito;
        capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
        costo_total += inst.getcosto(deposito, vendedor);

        if (deposito_anterior != -1) { // si no estaba asignado a ningún depósito
            capacidad_residual[deposito_anterior] += inst.getdemanda(deposito_anterior, vendedor); // al deposito anterior le sumo la capacidad que el vendedor le restaba
            
            costo_total -= inst.getcosto(deposito_anterior, vendedor); // ya no tengo en cuenta el costo del vendedor con el deposito anterior para calcular el costo total
        }
    }
}

void GAPSolution::swap(int vendedor1, int vendedor2, const GAPInstance& inst) {
    int dep1 = asignacion[vendedor1];
    int dep2 = asignacion[vendedor2];

    // libero ambos
    if (dep1 != -1) {
        capacidad_residual[dep1] += inst.getdemanda(dep1, vendedor1);
        costo_total -= inst.getcosto(dep1, vendedor1);
    }
    if (dep2 != -1) {
        capacidad_residual[dep2] += inst.getdemanda(dep2, vendedor2);
        costo_total -= inst.getcosto(dep2, vendedor2);
    }

    // reasigno cruzado
    asignacion[vendedor1] = dep2;
    asignacion[vendedor2] = dep1;

    if (dep2 != -1) {
        capacidad_residual[dep2] -= inst.getdemanda(dep2, vendedor1);
        costo_total += inst.getcosto(dep2, vendedor1);
    }
    if (dep1 != -1) {
        capacidad_residual[dep1] -= inst.getdemanda(dep1, vendedor2);
        costo_total += inst.getcosto(dep1, vendedor2);
    }
}

