#include "instance.h"

void GAPInstance::read(istream& in){
   if (!(in >> m >> n))
            cout<<("Error leyendo m y n")<< endl;

        costo.assign(m, vector<float>(n));
        demanda.assign(m, vector<float>(n));
        capacidad.resize(m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(in >> costo[i][j])) {
                cout << "Error leyendo costos en posicion " << i << "," << j << endl;
            }
        }
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(in >> demanda[i][j])) {
                cout << "Error leyendo demandas en posicion " << i << "," << j << endl;
            }
        }
    }
   
    for (int i = 0; i < m; ++i) {
        if (!(in >> capacidad[i])) {
            cout << "Error leyendo capacidad del deposito " << i << endl; 
        }
    }
}  

void GAPInstance::readFromFile(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "No se pudo abrir el archivo: " << filename << endl;
        return;
    }
    read(f);
    f.close();
}