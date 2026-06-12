#include "instance.h"
#include "solucion.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
using namespace std;

GAPSolution greedy_randomizado(const GAPInstance& inst, int k) {
    int m = inst.getm();
    int n = inst.getn();

    GAPSolution sol(inst);

    for (int j = 0; j < n; j++) {// recorro por vendedor
        vector<pair<float, int>> candidatos; // creo un vector de pairs donde voy a guardar los posibles candidtaos
        for( int i = 0; i < m ; i++){ // recorro los depositos
            if(sol.es_factible_asignar(j, i, inst)){ // me fijo si la demanda del vendedor es compatible con la capacidad del deposito
                candidatos.push_back({inst.getcosto(i, j), i}); // agrego en la lista de posibles candidatos
            }

        }
        if(candidatos.empty()){ // si no hay posibles candidatos
            sol.asignar(j, m, inst); // lo mando al final del vector asignar ya que no entra en ningun deposito
        }
        else{
            sort(candidatos.begin(), candidatos.end()); // ordeno los candidatos de menor costo a mayor costo
            int minimo = min(k, (int)candidatos.size()); // me guardo el minimo entre k y el tamaño de candidatos
            vector<int>top_k; 
            for (int t = 0; t < minimo; t++) { // recorro candidatos hasta el minimo qu eguarde anteriormente
                top_k.push_back(candidatos[t].second); // me guardo en el vector top k los numeros de los mejores depositos en orden
            }
            int elegido = top_k[rand() % top_k.size()]; // entre los depositos que hay en top k elijo uno random
            sol.asignar(j, elegido, inst); // asigno al vendedor j al deposito elegido
        }

    }
    return sol;

}


