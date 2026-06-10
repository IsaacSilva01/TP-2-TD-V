#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class GAPInstance {
public:
   
    GAPInstance() : m(0), n(0) {} //constructor de la clase Instance

    // estos getters son para acceder a los datos desde las heurísticas
    int getm() const { return m; }
    int getn() const { return n; }
    float getcosto(int i, int j) const { return costo[i][j]; }
    float getdemanda(int i, int j) const { return demanda[i][j]; }
    float getcapacidad(int i) const { return capacidad[i]; }

    void read(istream& in);
    void readFromFile(const string& filename);

private:

    int m; // número de depósitos
    int n; // número de vendedores

    // costo[i][j]: costo de asignar el vendedor j al depósito i
    vector<vector<float>> costo;     
    // demanda[i][j]: recurso que consume el vendedor j en el depósito i
    vector<vector<float>> demanda;   
    // capacidad[i]: capacidad total del depósito i
    vector<float> capacidad;
    
};
