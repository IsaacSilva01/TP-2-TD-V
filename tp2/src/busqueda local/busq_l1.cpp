#include "instance.h"
#include <vector>
using namespace std;



vector<vector<int>> relocate(const GAPInstance& inst, vector<vector<int>> asignacion){
    int m = inst.m;
    int n = inst.n;

    vector<float> cap_restante(inst.capacidad);
    for (int i = 0; i < m; i++)
        for (int j : asignacion[i])
            cap_restante[i] = cap_restante[i]-inst.demanda[i][j];
        
    bool mejoro = true;
    while (mejoro) {
        mejoro = false;

        for (int i = 0; i < m && !mejoro; i++) {          // agente origen
            for (int idx = 0; idx < asignacion[i].size() && !mejoro; idx++) {
                int j = asignacion[i][idx];                // job a mover

                for (int k = 0; k < m && !mejoro; k++) {  // agente destino
                    if (k == i) continue;

                    if (inst.demanda[k][j] <= cap_restante[k] &&
                        inst.costo[k][j] < inst.costo[i][j]) {

                        // hacer el movimiento
                        asignacion[i].erase(asignacion[i].begin() + idx);
                        asignacion[k].push_back(j);
                        cap_restante[i] += inst.demanda[i][j];
                        cap_restante[k] -= inst.demanda[k][j];

                        mejoro = true;
                    }
                }
            }
        }
    }

    return asignacion;
}

    


}