#include <string>
#include <iostream>
using namespace std;
#include "instance.h"


int main(int argc, char** argv) {
    // validamos que el usuario haya pasado los dos archivos requeridos
    if (argc < 3) {
        cout << "Uso incorrecto del programa." << endl;
        cout << "Ejecución requerida: " << argv[0] << " <archivo_entrada> <archivo_output>" << endl;
        return 1; 
    }
    string input_file = argv[1];
    string output_file = argv[2];

    cout << "Leyendo archivo de instancia: " << input_file << endl;
    GAPInstance inst;
    // instanciamos la clase y leemos los datos
    inst.readFromFile(input_file);

    cout << "Instancia cargada con exito!" << endl;
    cout << "Cantidad de depositos (m): " << inst.getm() << endl;
    cout << "Cantidad de vendedores (n): " << inst.getn() << endl;
    // próximo paso: pasarle 'inst' a tus funciones de heurísticas, por ejemplo:

    // GAPSolution sol = heuristica_constructiva_1(inst);
    return 0;
} 

