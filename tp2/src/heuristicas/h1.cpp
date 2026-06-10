#include "instance.h"
#include <vector>
#include <limits>

using namespace std;

vector<vector<int>> greedy(const GAPInstance& inst) {
    int m = inst.m;
    int n = inst.n;

    vector<float> cap_restante(inst.capacidad); // creo una copia de las capacidades de los vectores para poder ir restando despues
    vector<vector<int>> asignacion(m + 1); // creo mi vec tor de repsuestas y la ultima posicion es los vendedores que no pude asignar

    for (int j = 0; j < n; j++) {
        float mejor_costo = numeric_limits<float>::infinity(); // inicializo el mejor costo en inf
        int mejor_dep = -1; // inicializo como deposito seleccionado a uno inexistente

        for (int i = 0; i < m; i++) { //itero todos los depositos para el i-esimo vendedor
            if (inst.demanda[i][j] <= cap_restante[i]) { // me fijo si la demanda del vendedor entra en el deposito
                if (inst.costo[i][j] < mejor_costo) { // comparo el mejor costo guardado con el de ahora
                    mejor_costo = inst.costo[i][j]; // si es mejor lo guardo
                    mejor_dep = i; // y me guardo el numero de deposito
                }
            }
        }

        if (mejor_dep == -1) { // si no entro en ningun deposito lo mando al fihnal del vector de respuesta
            asignacion[m].push_back(j);
        } else {
            asignacion[mejor_dep].push_back(j);// sino lo pongo al final del vector guardado en la posicion del deposito
            cap_restante[mejor_dep] = cap_restante[mejor_dep] - inst.demanda[mejor_dep][j]; // le resto al deposito seleccionado la demanda del vendedor
        }
    }

    return asignacion;
}