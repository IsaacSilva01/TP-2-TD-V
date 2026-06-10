#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class GAPInstance {
public:
   
    int getm() { return m;}
    int getn() { return n;}
    float getcosto(int i, int j){return costo[i][j];}
    float getdemanda(int i, int j){return demanda[i][j];}
    float getcapacidad(int i){return capacidad[i];}


    void read(istream& in);
    void readFromFile(const std::string& filename);



    int m; // depositos
    int n; // vendedores

    vector<vector<float>> costo;     // cost[i][j]: costo de asignar job j al agente i
    vector<vector<float>> demanda; // resource[i][j]: recurso consumido
    vector<float> capacidad;              // capacity[i]: capacidad del agente i

    GAPInstance() : m(0), n(0) {}

    
};
