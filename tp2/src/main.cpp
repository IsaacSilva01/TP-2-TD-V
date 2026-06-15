#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

#include "instance.h"
#include "solucion.h"
#include "heuristicas.h"
#include "busqueda_local.h"



using chrono::high_resolution_clock;
using chrono::duration;
using chrono::duration_cast;
using chrono::milliseconds;

struct InstanciaSeleccionada {
    string nombre_corto;
    string ruta;
};

InstanciaSeleccionada seleccionar_instancia() {

    vector<pair<string,string>> instancias = {

        {"ga5x100", "instances/gap/gap_a/a05100"},
        {"ga5x200", "instances/gap/gap_a/a05200"},
        {"ga10x100", "instances/gap/gap_a/a10100"},
        {"ga10x200", "instances/gap/gap_a/a10200"},
        {"ga20x100", "instances/gap/gap_a/a20100"},
        {"ga20x200", "instances/gap/gap_a/a20200"},

        {"gb5x100", "instances/gap/gap_b/b05100"},
        {"gb5x200", "instances/gap/gap_b/b05200"},
        {"gb10x100", "instances/gap/gap_b/b10100"},
        {"gb10x200", "instances/gap/gap_b/b10200"},
        {"gb20x100", "instances/gap/gap_b/b20100"},
        {"gb20x200", "instances/gap/gap_b/b20200"},

        {"ge5x100", "instances/gap/gap_e/e05100"},
        {"ge5x200", "instances/gap/gap_e/e05200"},
        {"ge10x100", "instances/gap/gap_e/e10100"},
        {"ge10x200", "instances/gap/gap_e/e10200"},
        {"ge10x400", "instances/gap/gap_e/e10400"},
        {"ge15x900", "instances/gap/gap_e/e15900"},
        {"ge20x100", "instances/gap/gap_e/e20100"},
        {"ge20x200", "instances/gap/gap_e/e20200"},
        {"ge20x400", "instances/gap/gap_e/e20400"},
        {"ge30x900", "instances/gap/gap_e/e30900"},
        {"ge40x400", "instances/gap/gap_e/e40400"},
        {"ge60x900", "instances/gap/gap_e/e60900"},
        {"ge20x1600", "instances/gap/gap_e/e201600"},
        {"ge40x1600", "instances/gap/gap_e/e401600"},
        {"ge80x1600", "instances/gap/gap_e/e801600"},

        {"real1100x310", "instances/real/real_instance"}
    };

    cout << endl;
    cout << "==================================" << endl;
    cout << "      SELECCIONAR INSTANCIA       " << endl;
    cout << "==================================" << endl;

    for (int i = 0; i < instancias.size(); i++) {
        cout << i + 1 << ". " << instancias[i].first << endl;
    }

    int opcion;
    cout << endl;
    cout << "Seleccione una instancia: ";
    cin >> opcion;

    return {instancias[opcion - 1].first, instancias[opcion - 1].second};
}

int contar_deposito_ficticio(const GAPSolution& sol) {
    int cantidad = 0;
    for (int vendedor = 0; vendedor < (int)sol.asignacion.size(); ++vendedor) {
        if (sol.asignacion[vendedor] == -1) {
            ++cantidad;
        }
    }
    return cantidad;
}

void imprimir_resultado(const string& nombre_instancia,
                        const string& nombre_metodo,
                        float costo_total,
                        double tiempo_ms,
                        int vendedores_ficticios) {
    cout << fixed << setprecision(2);
    cout << "Instancia: " << nombre_instancia << endl;
    cout << "Metodo: " << nombre_metodo << endl;
    cout << "Costo total: " << costo_total << endl;
    cout << "Vendedores asignados a deposito -1: " << vendedores_ficticios << endl;
    cout << "Tiempo: " << tiempo_ms << " ms" << endl;
    cout << "----------------------------------" << endl;
}

string nombre_heuristica(int opcion) {
    switch (opcion) {
        case 1: return "Costo mínimo (greedy por vendedores)";
        case 2: return "Costo mínimo + flexibilidad (greedy por depósitos)";
        case 3: return "Greedy aleatorizado (top-k random)";
        default: return "Heuristica";
    }
}

string nombre_busqueda_local(int opcion) {
    return opcion == 1 ? "Relocate" : "Swap";
}

GAPInstance leer_instancia(const string& input_file) {

    GAPInstance inst;
    inst.readFromFile(input_file);

    return inst;
}

string pedir_archivo_salida() {

    string nombre;

    cout << endl;
    cout << "Nombre del archivo de salida (sin .txt): ";
    cin >> nombre;

    return "respuestas/" + nombre + ".txt";
}

int main() {

    InstanciaSeleccionada seleccion = seleccionar_instancia();
    string input_file = seleccion.ruta;
    string nombre_instancia = seleccion.nombre_corto;
    GAPInstance inst = leer_instancia(input_file);

    bool seguir = true;

    while (seguir) {

        int opcion;

        cout << endl;
        cout << "==================================" << endl;
        cout << "           GAP SOLVER             " << endl;
        cout << "==================================" << endl;
        cout << "1. Heuristica constructiva" << endl;
        cout << "2. Busqueda local" << endl;
        cout << "3. Metaheuristica GRASP" << endl;
        cout << "4. Cambiar instancia" << endl;
        cout << "0. Salir" << endl;
        cout << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1: {

                int heuristica;

                cout << endl;
                cout << "Heuristicas disponibles:" << endl;
                cout << "1. Costo mínimo (greedy por vendedores)" << endl;
                cout << "2. Costo mínimo + flexibilidad (greedy por depósitos)" << endl;
                cout << "3. Greedy aleatorizado (top-k random)" << endl;
                cout << "Seleccione una opcion: ";

                cin >> heuristica;

                if (heuristica == 1) {

                    cout << endl;
                    cout << "Ejecutando heuristica costo minimo..." << endl;

                    auto inicio = high_resolution_clock::now();
                    GAPSolution sol = greedy_por_vendedores(inst);
                    auto fin = high_resolution_clock::now();

                    double tiempo_ms = duration<double, milli>(fin - inicio).count();
                    int vendedores_ficticios = contar_deposito_ficticio(sol);

                    imprimir_resultado(nombre_instancia, nombre_heuristica(heuristica), sol.costo_total, tiempo_ms, vendedores_ficticios);

                    sol.escribir_solucion(
                        pedir_archivo_salida(),
                        inst
                    );
                }
                else if (heuristica == 2) {

                    cout << endl;
                    cout << "Ejecutando heuristica costo + flexibilidad..." << endl;

                    auto inicio = high_resolution_clock::now();
                    GAPSolution sol = greedy_por_deposito(inst);
                    auto fin = high_resolution_clock::now();

                    double tiempo_ms = duration<double, milli>(fin - inicio).count();
                    int vendedores_ficticios = contar_deposito_ficticio(sol);

                    imprimir_resultado(nombre_instancia, nombre_heuristica(heuristica), sol.costo_total, tiempo_ms, vendedores_ficticios);

                    sol.escribir_solucion(
                        pedir_archivo_salida(),
                        inst
                    );
                }
                else if (heuristica == 3) {

                    int k;

                    cout << endl;
                    cout << "Ingrese el valor de k: ";
                    cin >> k;

                    if (k <= 0 || k > inst.getm()) {
                        cout << "k debe estar entre 1 y "
                             << inst.getm() << endl;
                        break;
                    }

                    cout << endl;
                    cout << "Ejecutando greedy aleatorizado con k = "
                         << k << "..." << endl;

                    auto inicio = high_resolution_clock::now();
                    GAPSolution sol = greedy_randomizado(inst, k);
                    auto fin = high_resolution_clock::now();

                    double tiempo_ms = duration<double, milli>(fin - inicio).count();
                    int vendedores_ficticios = contar_deposito_ficticio(sol);

                    imprimir_resultado(nombre_instancia, nombre_heuristica(heuristica) + " (k=" + to_string(k) + ")", sol.costo_total, tiempo_ms, vendedores_ficticios);

                    sol.escribir_solucion(
                        pedir_archivo_salida(),
                        inst
                    );
                }
                else {

                    cout << "Opcion invalida." << endl;

                }

                break;
            }

            case 2: {

                int heuristica_inicial;
                int operador;

                cout << endl;
                cout << "Heuristica inicial:" << endl;
                cout << "1. Costo mínimo (greedy por vendedores)" << endl;
                cout << "2. Costo mínimo + flexibilidad (greedy por depósitos)" << endl;
                cout << "3. Greedy aleatorizado (top-k random)" << endl;
                cin >> heuristica_inicial;

                cout << endl;
                cout << "Operador:" << endl;
                cout << "1. Relocate" << endl;
                cout << "2. Swap" << endl;
                cin >> operador;

                cout << endl;
                cout << "Ejecutando busqueda local..." << endl;

                
                GAPSolution sol_inicial;
                string nombre_metodo = nombre_heuristica(heuristica_inicial) + " + " + nombre_busqueda_local(operador);
                double tiempo_heuristica_ms = 0.0;
                double tiempo_busqueda_ms = 0.0;

                if (heuristica_inicial == 1) {
                    auto inicio_heuristica = high_resolution_clock::now();
                    sol_inicial = greedy_por_vendedores(inst);
                    auto fin_heuristica = high_resolution_clock::now();
                    tiempo_heuristica_ms = duration<double, milli>(fin_heuristica - inicio_heuristica).count();
                }
                else if (heuristica_inicial == 2) {
                    auto inicio_heuristica = high_resolution_clock::now();
                    sol_inicial = greedy_por_deposito(inst);
                    auto fin_heuristica = high_resolution_clock::now();
                    tiempo_heuristica_ms = duration<double, milli>(fin_heuristica - inicio_heuristica).count();
                }
                else if (heuristica_inicial == 3) {
                    int k;

                    cout << endl;
                    cout << "Ingrese el valor de k: ";
                    cin >> k;

                    if (k <= 0 || k > inst.getm()) {
                        cout << "k debe estar entre 1 y "
                             << inst.getm() << endl;
                        break;
                    }

                    auto inicio_heuristica = high_resolution_clock::now();
                    sol_inicial = greedy_randomizado(inst, k);
                    auto fin_heuristica = high_resolution_clock::now();
                    tiempo_heuristica_ms = duration<double, milli>(fin_heuristica - inicio_heuristica).count();
                }
                else {
                    cout << "Opcion invalida." << endl;
                    break;
                }

                auto inicio_busqueda = high_resolution_clock::now();
                if (operador == 1)
                    relocate_busqueda_local(sol_inicial, inst);
                else
                    swap_busqueda_local(sol_inicial, inst);
                auto fin_busqueda = high_resolution_clock::now();
                tiempo_busqueda_ms = duration<double, milli>(fin_busqueda - inicio_busqueda).count();

                double tiempo_total_ms = tiempo_heuristica_ms + tiempo_busqueda_ms;

                cout << endl;
                cout << "Tiempo: " << fixed << setprecision(2) << tiempo_heuristica_ms
                     << " ms (" << nombre_heuristica(heuristica_inicial) << ") + "
                     << tiempo_busqueda_ms << " ms (" << nombre_busqueda_local(operador) << ") = "
                     << tiempo_total_ms << " ms" << endl;

                int vendedores_ficticios = contar_deposito_ficticio(sol_inicial);
                imprimir_resultado(nombre_instancia, nombre_metodo, sol_inicial.costo_total, tiempo_total_ms, vendedores_ficticios);

                sol_inicial.escribir_solucion(
                    pedir_archivo_salida(),
                    inst
                );

                break;
            }

            case 3: {

                int k;

                cout << endl;
                cout << "Ejecutando GRASP..." << endl;
                cout << "Ingrese el valor de k: ";
                cin >> k;

                // Aclaro la cantidad de depósitos para que
                // siempre elija sobre una cantdad de depósitos factible
                if (k <= 0 || k > inst.getm()) {
                    cout << "k debe estar entre 1 y "
                        << inst.getm() << endl;
                    break;
                }

                cout << "Corriendo GRASP con k = " << k << "..." << endl;

                auto inicio = high_resolution_clock::now();
                GAPSolution sol = grasp(inst, k);
                auto fin = high_resolution_clock::now();

                double tiempo_ms = duration<double, milli>(fin - inicio).count();
                int vendedores_ficticios = contar_deposito_ficticio(sol);

                imprimir_resultado(nombre_instancia, "GRASP(k=" + to_string(k) + ")", sol.costo_total, tiempo_ms, vendedores_ficticios);

                sol.escribir_solucion(
                    pedir_archivo_salida(),
                    inst
                );

                break;
            }
            
            case 4: {

                seleccion = seleccionar_instancia();
                input_file = seleccion.ruta;
                nombre_instancia = seleccion.nombre_corto;
                inst = leer_instancia(input_file);

                break;
            }

            case 0: {

                seguir = false;
                cout << endl;
                cout << "Saliendo..." << endl;

                break;
            }

            default:

                cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}