#include "instance.h"
#include "solucion.h"
#include "heuristicas.h"
#include <vector>
#include <limits>

using namespace std;

// Intuición: itero sobre los depósitos, y para cada depósito le asigno
// la mayor cantidad de vendedores posibles tal que
// esos vendedores tengan el menor costo posible
// con la particularidad de que además se prioriza
// a los vendedores que tienen pocos depósitos factibles
// disponibles para ser asignados

// ambas condiciones se ven reflejadas en la variable puntaje
// A cada depósito, se asinan los vendedores de menor puntaje:
// puntaje = costo ij + (1 +  1 / cantidad de depositos factibles(i))
GAPSolution greedy_por_deposito(const GAPInstance& inst) {
    int m = inst.getm();
    int n = inst.getn();

    // creamos el objeto solución usando su constructor en base a nuestra instancia
    GAPSolution solucion(inst);

    // vector donde marcamos los vendedores ya asignados
    vector<bool> asignado(n, false);

    // cantidad de depósitos factibles para cada vendedor
    vector<int> cantidad_depositos_factibles(n, 0);
    
    for (int vendedor = 0; vendedor < n; vendedor++) {
        int contador = 0;

        for (int deposito = 0; deposito < m; deposito++) {
            if (solucion.es_factible_asignar(vendedor, deposito, inst)) {
                contador++;
            }
        }

        // evitamos división por cero haciendo que todos los vendedores
        // son asignables a al menos un depósito.
        // Siempre es posible asignarlo a un déposito imaginario
        // que representa no asignarlo a ninguno
        cantidad_depositos_factibles[vendedor] = max(1, contador);
    }

    // iteramos por cada depósito:
    // por cada depósito, le asigno la mayor cantidad de vendedores posibles
    // tal que esos vendedores tengan el mayor puntaje entre los vendedore no asignados
    for (int deposito = 0; deposito < m; deposito++) {

        while (true) {

            float mejor_puntaje = numeric_limits<float>::infinity();
            int mejor_vendedor = -1;

            for (int vendedor = 0; vendedor < n; vendedor++) {

                if (asignado[vendedor]) continue;
                
                // chequeo que sea factible asignar el vendedor actual al depósito actual
                if (!solucion.es_factible_asignar(vendedor, deposito, inst)) {
                    continue;
                }

                float costo = inst.getcosto(deposito, vendedor);

                float puntaje = costo * (1.0f + 1.0f / cantidad_depositos_factibles[vendedor]);

                if (puntaje < mejor_puntaje) {
                    mejor_puntaje = puntaje;
                    mejor_vendedor = vendedor;
                }
            }

            if (mejor_vendedor == -1) break;

            solucion.asignar(mejor_vendedor, deposito, inst);
            asignado[mejor_vendedor] = true;
        }
    }

    // vendedores no asignados → depósito ficticio
    for (int vendedor = 0; vendedor < n; vendedor++) {
        if (!asignado[vendedor]) {
            solucion.asignar(vendedor, m, inst);
        }
    }

    return solucion;
}