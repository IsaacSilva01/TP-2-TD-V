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

        for (int j = 0; j < n && !mejoro; j++) {
            int i = sol.asignacion[j];

            for (int k = 0; k < m && !mejoro; k++) {
                if (i != -1 && k != i &&
                    inst.getdemanda(k, j) <= sol.capacidad_residual[k] &&
                    inst.getcosto(k, j) < inst.getcosto(i, j)) {

                    sol.relocate(j, k, inst);
                    mejoro = true;
                }
            }
        }
    }
}