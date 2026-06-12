#include "instance.h"
#include "solucion.h"
#include <vector>
#include <limits>

using namespace std;

GAPSolution greedy_por_vendedor(const GAPInstance& inst) {
    int m = inst.getm();
    int n = inst.getn();

    // creamos el objeto solución usando su constructor en base a nuestra instancia
    GAPSolution sol(inst); 

    // iteramos por cada vendedor
    for (int j = 0; j < n; j++) {
        float mejor_costo = numeric_limits<float>::infinity(); 
        int mejor_dep = -1; 

        // iteramos todos los depósitos para encontrar la opción más barata
        for (int i = 0; i < m; i++) { 
            
            // verificamos si el vendedor entra en el depósito
            if (sol.es_factible_asignar(j, i, inst)) { 
                // si la distancia es menor a la mejor que teníamos, la guardamos
                if (inst.getcosto(i, j) < mejor_costo) { 
                    mejor_costo = inst.getcosto(i, j); 
                    mejor_dep = i; 
                }
            }
        }

        // asignamos deposito a vendedor
        if (mejor_dep != -1) {
            // si encontramos un depósito real factible para j, le asignamos al deposito mejor_dep,
            // restamos la capacidad y sumamos el costo al costo total
            sol.asignar(j, mejor_dep, inst);
        } else {
            // si no encontramos ningún depósito real, lo asignamos 
            // al depósito ficticio (índice m). O sea que se quedará con valor -1
            sol.asignar(j, m, inst);
        }
    }

    return sol;
}