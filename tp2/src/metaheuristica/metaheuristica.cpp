#include "instance.h"
#include "solucion.h"
#include "heuristicas.h"
#include "busqueda_local.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <random>

using namespace std;

GAPSolution grasp(const GAPInstance& inst, int k) {
    
    GAPSolution res = GAPSolution();

    // Cantidad máxima de iteraciones de GRASP.
    // Se escala linealmente con la cantidad de vendedores para explorar
    // más soluciones en instancias grandes, manteniendo un límite superior
    // para evitar tiempos de ejecución excesivos.
    int max = min(500, 10 * inst.getn());
    
    int mejor = numeric_limits<int>::max();

    for (int it = 0; it < max; it++) {

        GAPSolution s = greedy_randomizado(inst, k);

        swap_busqueda_local(s, inst);
        relocate_busqueda_local(s, inst);

        if (s.costo_total < mejor) {
            mejor = s.costo_total;
            GAPSolution res = s;
        }
    }

    return res;
}