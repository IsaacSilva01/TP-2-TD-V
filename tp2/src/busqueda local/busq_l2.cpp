#include "instance.h"
#include "solucion.h"
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

                if(i != -1 && q != -1 && q != i && // me fijo que q e i sean depositos factibles y que sean distintos entre si 
                    inst.getdemanda(q, j) <= sol.capacidad_residual[q] + inst.getdemanda(q, h) && // busco la demanda de j en q y me fijo si es menor a la capacidad restante de q (sacando el lugar que ocupa h en q)
                    inst.getdemanda(i, h) <= sol.capacidad_residual[i] + inst.getdemanda(i, j) && // busco la demanda de h en i y me fijo si es menor a la capacidad restante de i (sacando el lugar que ocupa j en i)
                    inst.getcosto(q, j) + inst.getcosto(i, h) < inst.getcosto(i, j) + inst.getcosto(q, h)){ // calculo los nuevos costos y me fijo si son menores a los anteriores

                        sol.swap(j, h, inst); // ejecuto el swap
                        mejoro = true;
                }
            }
        }
    }
}