#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "instance.h"
using namespace std;

class GAPSolution {
public: 
    
    // Atributos modificables por la búsqueda local
    vector<int> asignacion; 
    vector<float> capacidad_residual; 
    float costo_total;

    // constructor vacío
    GAPSolution()
        : costo_total(0.0f) {}

    // constructor a partir de una instancia
    GAPSolution(const GAPInstance& inst);

    // métodos auxiliares
    bool es_factible_asignar(int vendedor, int deposito, const GAPInstance& inst);
    void asignar(int vendedor, int deposito, const GAPInstance& inst);
    void relocate (int vendedor, int deposito, const GAPInstance& inst);
    void swap(int vendedor1, int vendedor2, const GAPInstance& inst); 
    void escribir_solucion(const string& filename, const GAPInstance& inst) const;

};