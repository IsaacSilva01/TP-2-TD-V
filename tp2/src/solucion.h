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

    // constructor
    GAPSolution(const GAPInstance& inst);

    // métodos auxiliares
    bool es_factible_asignar(int vendedor, int deposito, const GAPInstance& inst);
    void asignar(int vendedor, int deposito, const GAPInstance& inst);
    void relocate (int vendedor, int deposito, const GAPInstance& inst);

};