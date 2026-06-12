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
    
    GAPSolution best = greedy_randomizado(inst, k);
    swap_busqueda_local(best, inst);
    relocate_busqueda_local(best, inst);

    int max = 7;
    int mejor = numeric_limits<int>::max();

    for (int it = 0; it < max; it++) {

        GAPSolution s = greedy_randomizado(inst, k);

        swap_busqueda_local(s, inst);
        relocate_busqueda_local(s, inst);

        if (s.costo_total < mejor) {
            mejor = s.costo_total;
            GAPSolution best = s;
        }
    }

    return best;
}