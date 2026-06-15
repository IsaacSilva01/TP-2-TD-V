#include "instance.h"
#include "solucion.h"
#include "busqueda_local.h"
#include <vector>
using namespace std;

void swap_busqueda_local(GAPSolution& sol, const GAPInstance& inst){
    int n = inst.getn();

    bool mejoro = true;
    while(mejoro){
        mejoro = false;

        for (int j = 0; j < n && !mejoro; j++) { // voy a recorrer los vendedores
            int i = sol.asignacion[j]; // i va a ser el deposito en el que se encuentra el vendedor j

            for(int h = 0; h < n && !mejoro; h++){ // vuelvo a recorrer los vendedores
                int q = sol.asignacion[h]; // q va a ser el deposito en el que se encuentra el vendedor h

                if (q != i && // me fijo que q e i sean distintos entre si
                    (i == -1 || inst.getdemanda(i, h) <= sol.capacidad_residual[i] + inst.getdemanda(i, j)) &&
                    (q == -1 || inst.getdemanda(q, j) <= sol.capacidad_residual[q] + inst.getdemanda(q, h)) &&
                    inst.getcosto(q, j) + inst.getcosto(i, h) < inst.getcosto(i, j) + inst.getcosto(q, h)) {

                        sol.swap(j, h, inst); // ejecuto el swap
                        mejoro = true;
                }
            }
        }
    }
}