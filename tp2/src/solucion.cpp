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
    float dem = inst.getdemanda(deposito, vendedor);
    return capacidad_residual[deposito] >= dem;
}

// Definición del método para aplicar una asignación
void GAPSolution::asignar(int vendedor, int deposito, const GAPInstance& inst) {
    asignacion[vendedor] = deposito;
    capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
    costo_total += inst.getcosto(deposito, vendedor);
}

void GAPSolution::relocate(int vendedor, int deposito, const GAPInstance& inst){
    if ( asignacion[vendedor]!=deposito && es_factible_asignar(vendedor, deposito, inst)){ 
        int deposito_anterior = asignacion[vendedor];
        asignacion[vendedor] = deposito;
        capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
        costo_total += inst.getcosto(deposito, vendedor);

        if (deposito_anterior != -1) { // si no estaba asignado a ningún depósito
            capacidad_residual[deposito_anterior] += inst.getdemanda(deposito_anterior, vendedor); // al deposito anterior le sumo la capacidad que el vendedor le restaba
           
            costo_total -= inst.getcosto(deposito_anterior, vendedor); // ya no tengo en cuenta el costo del vendedor con el deposito anterior para calcular el costo total
        }
    }
}