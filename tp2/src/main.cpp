#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "instance.h"
#include "solucion.h"
#include "heuristicas.h"
#include "busqueda_local.h"



string seleccionar_instancia() {

    vector<pair<string,string>> instancias = {

        {"ga5x100", "src/instances/gap/gap_a/a05100"},
        {"ga5x200", "src/instances/gap/gap_a/a05200"},
        {"ga10x100", "src/instances/gap/gap_a/a10100"},
        {"ga10x200", "src/instances/gap/gap_a/a10200"},
        {"ga20x100", "src/instances/gap/gap_a/a20100"},
        {"ga20x200", "src/instances/gap/gap_a/a20200"},

        {"gb5x100", "src/instances/gap/gap_b/b05100"},
        {"gb5x200", "src/instances/gap/gap_b/b05200"},
        {"gb10x100", "src/instances/gap/gap_b/b10100"},
        {"gb10x200", "src/instances/gap/gap_b/b10200"},
        {"gb20x100", "src/instances/gap/gap_b/b20100"},
        {"gb20x200", "src/instances/gap/gap_b/b20200"},

        {"ge5x100", "src/instances/gap/gap_e/e05100"},
        {"ge5x200", "src/instances/gap/gap_e/e05200"},
        {"ge10x100", "src/instances/gap/gap_e/e10100"},
        {"ge10x200", "src/instances/gap/gap_e/e10200"},
        {"ge10x400", "src/instances/gap/gap_e/e10400"},
        {"ge15x900", "src/instances/gap/gap_e/e15900"},
        {"ge20x100", "src/instances/gap/gap_e/e20100"},
        {"ge20x200", "src/instances/gap/gap_e/e20200"},
        {"ge20x400", "src/instances/gap/gap_e/e20400"},
        {"ge30x900", "src/instances/gap/gap_e/e30900"},
        {"ge40x400", "src/instances/gap/gap_e/e40400"},
        {"ge60x900", "src/instances/gap/gap_e/e60900"},
        {"ge20x1600", "src/instances/gap/gap_e/e201600"},
        {"ge40x1600", "src/instances/gap/gap_e/e401600"},
        {"ge80x1600", "src/instances/gap/gap_e/e801600"},

        {"real1100x310", "src/instances/real/real_instance"}
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

    return instancias[opcion - 1].second;
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

    string input_file = seleccionar_instancia();
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
                cout << "Seleccione una opcion: ";

                cin >> heuristica;

                if (heuristica == 1) {

                    cout << endl;
                    cout << "Ejecutando heuristica costo minimo..." << endl;

                    GAPSolution sol = greedy_por_vendedores(inst);

                    sol.escribir_solucion(
                        pedir_archivo_salida(),
                        inst
                    );
                }
                else if (heuristica == 2) {

                    cout << endl;
                    cout << "Ejecutando heuristica costo + flexibilidad..." << endl;

                    GAPSolution sol = greedy_por_deposito(inst);

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
                cin >> heuristica_inicial;

                cout << endl;
                cout << "Operador:" << endl;
                cout << "1. Relocate" << endl;
                cout << "2. Swap" << endl;
                cin >> operador;

                cout << endl;
                cout << "Ejecutando busqueda local..." << endl;

                
                GAPSolution sol_inicial;

                if (heuristica_inicial == 1)
                    sol_inicial = greedy_por_vendedores(inst);
                else
                    sol_inicial = greedy_por_deposito(inst);

                GAPSolution sol_final;

                if (operador == 1)
                    relocate_busqueda_local(sol_inicial, inst);
                else
                    swap_busqueda_local(sol_inicial, inst);

                sol_final.escribir_solucion(
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

                GAPSolution sol = grasp(inst, k);

                sol.escribir_solucion(
                    pedir_archivo_salida(),
                    inst
                );

                break;
            }
            
            case 4: {

                input_file = seleccionar_instancia();
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