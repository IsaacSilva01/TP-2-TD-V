#include "instance.h"
#include <vector>
#include <algorithm>

using namespace std;

// puse los gets para resolver el error del private
// y copie las capacidades usando el get en un for
vector<vector<int>> ratio(const GAPInstance& inst) {

    int m = inst.getm();
    int n = inst.getn();

    // creo una copia de las capacidades de los vectores para poder ir restando después
    vector<float> cap_restante = {}; 
    for(int i; i < m; i++) {
        cap_restante[i] = inst.getcapacidad(i);
    }    

    vector<vector<int>> asignacion(m + 1);      // ultima posicion = vendedores no asignados

    for (int j = 0; j < n; j++) { // para cada vendedor

        vector<pair<float,int>> ratios;

        // calculo el ratio costo/demanda para cada deposito
        for (int i = 0; i < m; i++) {

            float ratio;
            if (inst.getdemanda(i,j) == 0) {
                ratio = inst.getcosto(i, j);
            } else {
                ratio = inst.getcosto(i, j) / inst.getdemanda(i, j);
            }

            ratios.push_back({ratio, i});
        }

        // ordeno de menor ratio a mayor
        sort(ratios.begin(), ratios.end());

        int mejor_dep = -1; // deposito elegido

        // busco el primer deposito factible siguiendo el orden de ratios
        for (int k = 0; k < (int)ratios.size(); k++) {
            int dep = ratios[k].second;
            if (inst.getdemanda(dep, j) <= cap_restante[dep]) {
                mejor_dep = dep;
                break;
            }
        }

        if (mejor_dep == -1) { // no encontre deposito factible
            asignacion[m].push_back(j);
        } else {
            asignacion[mejor_dep].push_back(j); // asigno vendedor
            cap_restante[mejor_dep] -= inst.getdemanda(mejor_dep, j); // actualizo capacidad
        }
    }

    return asignacion;
}