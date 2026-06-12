#include "instance.h"
#include "solucion.h"
#include <vector>
using namespace std;

void swap_busqueda_local(GAPSolution& sol, const GAPInstance& inst){
    int n = inst.getn();

    bool mejoro = true;
    while(mejoro){
        mejoro = false;

        for (int j = 0; j < n && !mejoro; j++) {
            int i = sol.asignacion[j];

            for(int h = 0; h < n && !mejoro; h++){
                int q = sol.asignacion[h];

                if(i != -1 && q != -1 && q != i &&
                    inst.getdemanda(q, j) <= sol.capacidad_residual[q] + inst.getdemanda(q, h) &&
                    inst.getdemanda(i, h) <= sol.capacidad_residual[i] + inst.getdemanda(i, j) &&
                    inst.getcosto(q, j) + inst.getcosto(i, h) < inst.getcosto(i, j) + inst.getcosto(q, h)){

                        sol.swap(j, h, inst);
                        mejoro = true;
                }
            }
        }
    }
}