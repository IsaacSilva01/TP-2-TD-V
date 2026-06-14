#include "solucion.h"
#include <fstream>

// Definición del Constructor de la clase
GAPSolution::GAPSolution(const GAPInstance& inst) {
    asignacion.assign(inst.getn(), -1); 
    capacidad_residual.resize(inst.getm());
    for(int i = 0; i < inst.getm(); i++) {
        capacidad_residual[i] = inst.getcapacidad(i);
    }
    costo_total = 0.0;
}

// Definición del método para verificar espacio libre
bool GAPSolution::es_factible_asignar(int vendedor, int deposito, const GAPInstance& inst) {

    // si el destino es la posición 'm' (no asignados), no consume capacidad
    if (deposito == -1) return true;

    float dem = inst.getdemanda(deposito, vendedor);
    return capacidad_residual[deposito] >= dem;
}

// método para aplicar una asignación
void GAPSolution::asignar(int vendedor, int deposito, const GAPInstance& inst) {
    // asigna el depósito al vendedor
    asignacion[vendedor] = deposito;

    // si no es el depósito ficticio que nos creamos, le restamos la capacidad y sumamos el costo
    if (deposito != -1) {
        capacidad_residual[deposito] -= inst.getdemanda(deposito, vendedor);
        costo_total += inst.getcosto(deposito, vendedor);
}   
    else{
        // va al depósito ficticio (deposito ficticio = -1): se queda en -1 y no altera costos ni capacidades reales
        asignacion[vendedor] = -1;
        costo_total += inst.getcosto_maximo()*3.0;
    }
}

void GAPSolution::relocate(int vendedor, int deposito_nuevo,
                           const GAPInstance& inst) {

    int deposito_anterior = asignacion[vendedor];

    if (deposito_anterior == deposito_nuevo) return;

    if (!es_factible_asignar(vendedor, deposito_nuevo, inst))
        return;

    // --- DESHACER LA ASIGNACIÓN ANTERIOR ---

    if (deposito_anterior == -1) {
        // estaba penalizado
        costo_total -= 3.0 * inst.getcosto_maximo();
    }
    else {
        capacidad_residual[deposito_anterior] +=
            inst.getdemanda(deposito_anterior, vendedor);

        costo_total -=
            inst.getcosto(deposito_anterior, vendedor);
    }

    // --- APLICAR LA NUEVA ASIGNACIÓN ---

    asignacion[vendedor] = deposito_nuevo;

    if (deposito_nuevo == -1) {
        costo_total += 3.0 * inst.getcosto_maximo();
    }
    else {
        capacidad_residual[deposito_nuevo] -=
            inst.getdemanda(deposito_nuevo, vendedor);

        costo_total +=
            inst.getcosto(deposito_nuevo, vendedor);
    }
}

void GAPSolution::swap(int vendedor1, int vendedor2, const GAPInstance& inst) {
    // Si son el mismo vendedor o ya comparten el mismo depósito, no hay nada que intercambiar
    if (vendedor1 == vendedor2 || asignacion[vendedor1] == asignacion[vendedor2]) return;

    int dep1 = asignacion[vendedor1];
    int dep2 = asignacion[vendedor2];

    // --- PASO 1: Verificar si el intercambio es factible ---

    // Si dep1 no es el ficticio, verificamos que el vendedor2 entre al liberar al vendedor1
    if (dep1 != -1) {
        float espacio_neto_dep1 = capacidad_residual[dep1] + inst.getdemanda(dep1, vendedor1) - inst.getdemanda(dep1, vendedor2);
        if (espacio_neto_dep1 < 0) return; // No hay capacidad suficiente en dep1
    }

    // Si dep2 no es el ficticio, verificamos que el vendedor1 entre al liberar al vendedor2
    if (dep2 != -1) {
        float espacio_neto_dep2 = capacidad_residual[dep2] + inst.getdemanda(dep2, vendedor2) - inst.getdemanda(dep2, vendedor1);
        if (espacio_neto_dep2 < 0) return; // No hay capacidad suficiente en dep2
    }


    // --- PASO 2: Si pasó el control, aplicamos los cambios en la solución ---

    // 1. Liberamos los recursos consumidos por la asignación vieja
    if (dep1 != -1) {
        capacidad_residual[dep1] += inst.getdemanda(dep1, vendedor1);
        costo_total -= inst.getcosto(dep1, vendedor1);
    }
    if (dep2 != -1) {
        capacidad_residual[dep2] += inst.getdemanda(dep2, vendedor2);
        costo_total -= inst.getcosto(dep2, vendedor2);
    }

    // 2. Efectuamos el intercambio cruzado en el vector de asignación
    asignacion[vendedor1] = dep2;
    asignacion[vendedor2] = dep1;

    // 3. Impactamos el consumo de recursos y costos de la nueva asignación
    if (dep2 != -1) {
        capacidad_residual[dep2] -= inst.getdemanda(dep2, vendedor1);
        costo_total += inst.getcosto(dep2, vendedor1);
    }
    if (dep1 != -1) {
        capacidad_residual[dep1] -= inst.getdemanda(dep1, vendedor2);
        costo_total += inst.getcosto(dep1, vendedor2);
    }
}


void GAPSolution::escribir_solucion(const string& filename,
                                    const GAPInstance& inst) const {

    ofstream out(filename);

    if (!out.is_open()) {
        cout << "No se pudo abrir el archivo de salida: "
             << filename << endl;
        return;
    }

    int m = inst.getm();
    int n = inst.getn();

    for (int deposito = 0; deposito < m; deposito++) {

        for (int vendedor = 0; vendedor < n; vendedor++) {

            if (asignacion[vendedor] == deposito) {
                out << vendedor << " ";
            }

        }

        out << endl;
    }

    out.close();

    cout << "Solucion guardada en " << filename << endl;
}