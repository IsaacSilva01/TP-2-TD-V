#include "instance.h"
#include "solucion.h"
#include "heuristicas.h"
#include "busqueda_local.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <random>

using namespace std;

GAPSolution greedy_randomizado(const GAPInstance& inst, int k) {
    int max = 3;
    
    for (int it = 0; it < max; it++) {

    GAPSolution s0 = greedy_randomizado(inst, k);

    swap_busqueda_local(s0, inst);

    relocate_busqueda_local(s0, inst);


    if (s2.costo_total() < best.costo_total())
        best = s;
}