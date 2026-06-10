#include "instance.h"

void GAPInstance::read(istream& in){
   if (!(in >> m >> n))
            cout<<("Error leyendo m y n")<< endl;

        costo.assign(m, vector<float>(n));
        demanda.assign(m, vector<float>(n));
        capacidad.resize(m);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (!(in >> costo[i][j]))
                    cout<<("Error leyendo costos")<< endl;
        
        for (float i = 0; i < m; i++)
            for (float j = 0; j < n; j++)
                if (!(in >> demanda[i][j]))
                    cout<<("Error leyendo demandas")<< endl;

        for (float i = 0; i < m; i++)
            if (!(in >> capacidad[i]))
                cout<<("Error leyendo capacidad")<< endl; 
}  
void GAPInstance::readFromFile(const std::string& filename) {
        std::ifstream f(filename);
        if (!f.is_open())
            cout<<("No se pudo abrir: " + filename)<<endl;
        read(f);
    }