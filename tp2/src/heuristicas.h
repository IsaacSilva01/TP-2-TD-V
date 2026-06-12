#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "instance.h"
#include "solucion.h"
using namespace std;

class GAPheuristicas{
public: 
    
    // Atributos modificables por la búsqueda local
    vector<int> asignacion; 
    vector<float> capacidad_residual; 
    float costo_total;

    // constructor
    GAPheuristicas(const GAPSolution& inst);

    // métodos auxiliares
    GAPSolution greedy_por_vendedores(const GAPInstance& inst); 
    GAPSolution greedy_por_deposito(const GAPInstance& inst);
    GAPSolution greedy_randomizado(const GAPInstance& inst);
};