#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "instance.h"
using namespace std;

class GAPSolution {
public:
    
    vector<int> asignacion; // asignacion[j] guarda el indice del depósito 'i' asignado al vendedor 'j'
    // si vale -1, significa que el vendedor está sin asignar (solución parcial)
    
    vector<float> capacidad_residual; // capacidad_residual[i] guarda cuánta capacidad le queda disponible al depósito i 
    
    float costo_total;

    // Constructor que inicializa todo vacío usando los datos de la instancia
    GAPSolution(const GAPInstance& inst) {
        asignacion.assign(inst.getn(), -1); 
        capacidad_residual.resize(inst.getm());
        for(int i = 0; i < inst.getm(); i++) {
            capacidad_residual[i] = inst.getcapacidad(i);
        }
        costo_total = 0.0;
    }

    // Método útil para que la búsqueda local verifique si un cambio es factible
    bool es_factible_asignar(int vendedor, int deposito, const GAPInstance& inst) {
        float dem = inst.getdemanda(deposito, vendedor);
        return capacidad_residual[deposito] >= dem;
    }

    // Método para realizar la asignación y actualizar capacidades
    void asignar(int vendedor, int deposito, const GAPInstance& inst) {
        asignacion[vendedor] = deposito;
        capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
        costo_total += inst.getcosto(deposito, vendedor);
    }
};