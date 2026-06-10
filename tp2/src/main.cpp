#include <string>
#include <iostream>
using namespace std;
#include "instance.h"


int main(int argc, char** argv) {
    string filename = "instances/gap/gap_a/a05100";
    cout << "Reading file " << filename << endl;

    GAPInstance inst;
    inst.readFromFile(argv[1]);

    // Aca empieza la magia.

    return 0;
}