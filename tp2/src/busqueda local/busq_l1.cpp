#include "instance.h"
#include "solucion.h"
#include <vector>
using namespace std;



void relocate_busqueda_local(GAPSolution& sol, const GAPInstance& inst) {
    int m = inst.getm();
    int n = inst.getn();

    bool mejoro = true;
    while (mejoro) {
        mejoro = false;

        for (int j = 0; j < n && !mejoro; j++) { // recorro los vendedores con j
            int i = sol.asignacion[j]; // i es el deposito en el que se ubica j

            for (int k = 0; k < m && !mejoro; k++) { // recorro los depositos con k
                if (i != -1 && k != i && // me fijo que i sea un deposito valido y que k e i sean distintos
                    inst.getdemanda(k, j) <= sol.capacidad_residual[k] && // calculo la demanda de j en k y me fijo si entraria en k
                    inst.getcosto(k, j) < inst.getcosto(i, j)) { // calculo el costo de j en k y me fijo si es menor al costo de j en i 

                    sol.relocate(j, k, inst); //. si lo anterior se cumple hago relocate
                    mejoro = true;
                }
            }
        }
    }
}