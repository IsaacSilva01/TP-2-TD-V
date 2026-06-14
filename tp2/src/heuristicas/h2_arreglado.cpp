#include "instance.h"
#include "solucion.h"
#include <vector>
#include <limits>
#include <algorithm> // Para usar max

using namespace std;

GAPSolution greedy_por_deposito(const GAPInstance& inst) {
    // CORREGIDO: Usando getM() y getN() si es que llevan mayúsculas en tu clase
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

        // evitamos división por cero
        cantidad_depositos_factibles[vendedor] = max(1, contador);
    }

    // iteramos por cada depósito:
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

                // CORREGIDO: getCosto con C mayúscula
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

    // --- CÁLCULO DE PENALIZACIÓN ---
    int vendedores_sin_asignar = 0;

    // vendedores no asignados → depósito ficticio (-1)
    for (int vendedor = 0; vendedor < n; vendedor++) {
        if (!asignado[vendedor]) {
            solucion.asignar(vendedor, -1, inst); // Asignamos al ficticio de forma segura
            vendedores_sin_asignar++;
        }
    }

    // Si hubo vendedores infactibles que quedaron afuera, aplicamos la penalización gigante
    if (vendedores_sin_asignar > 0) {
        int cmax = inst.obtener_costo_maximo();
        int penalizacion = 3.0 * cmax * vendedores_sin_asignar;
        
        // Si costo_total es privado, recordá cambiar esta línea por un método público de tu solución
        solucion.costo_total += penalizacion; 
    }

    return solucion;
}