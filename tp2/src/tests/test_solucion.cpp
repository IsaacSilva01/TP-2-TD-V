#include <cassert>
#include <cmath>
#include <sstream>
#include <string>

#include "../instance.h"
#include "../solucion.h"

using namespace std;

namespace {

GAPInstance make_instance(const string& data) {
    stringstream ss(data);
    GAPInstance inst;
    inst.read(ss);
    return inst;
}

void assert_close(float a, float b, float eps = 1e-6f) {
    assert(fabs(a - b) <= eps && "Valor fuera del margen permitido");
}

void assert_invariants(const GAPSolution& sol, const GAPInstance& inst) {
    assert(static_cast<int>(sol.asignacion.size()) == inst.getn());
    assert(static_cast<int>(sol.capacidad_residual.size()) == inst.getm());

    float expected_cost = 0.0f;
    for (int vendedor = 0; vendedor < inst.getn(); ++vendedor) {
        int deposito = sol.asignacion[vendedor];
        if (deposito == -1) {
            expected_cost += 3.0f * inst.getcosto_maximo();
        } else {
            expected_cost += inst.getcosto(deposito, vendedor);
        }
    }

    assert_close(sol.costo_total, expected_cost);

    for (int deposito = 0; deposito < inst.getm(); ++deposito) {
        float demanda_usada = 0.0f;
        for (int vendedor = 0; vendedor < inst.getn(); ++vendedor) {
            if (sol.asignacion[vendedor] == deposito) {
                demanda_usada += inst.getdemanda(deposito, vendedor);
            }
        }

        assert_close(sol.capacidad_residual[deposito], inst.getcapacidad(deposito) - demanda_usada);
        assert(sol.capacidad_residual[deposito] >= -1e-6f);
    }
}

void test_constructor_y_asignacion_basica() {
    GAPInstance inst = make_instance(
        "2 2\n"
        "1 4\n"
        "6 2\n"
        "1 3\n"
        "3 1\n"
        "5 5\n"
    );

    GAPSolution sol(inst);
    assert_close(sol.costo_total, 0.0f);
    assert_close(sol.capacidad_residual[0], 5.0f);
    assert_close(sol.capacidad_residual[1], 5.0f);

    sol.asignar(0, 0, inst);
    assert(sol.asignacion[0] == 0);
    assert_close(sol.capacidad_residual[0], 4.0f);
    assert_close(sol.costo_total, 1.0f);

    sol.asignar(1, -1, inst);
    assert(sol.asignacion[1] == -1);
    assert_close(sol.capacidad_residual[0], 4.0f);
    assert_close(sol.costo_total, 1.0f + 3.0f * inst.getcosto_maximo());

    assert_invariants(sol, inst);
}

void test_relocate_valido_e_invalido() {
    GAPInstance inst_valida = make_instance(
        "2 2\n"
        "1 4\n"
        "6 2\n"
        "1 2\n"
        "2 1\n"
        "5 5\n"
    );

    GAPSolution sol_valida(inst_valida);
    sol_valida.asignar(0, 0, inst_valida);
    sol_valida.asignar(1, 1, inst_valida);

    sol_valida.relocate(0, 1, inst_valida);
    assert(sol_valida.asignacion[0] == 1);
    assert_close(sol_valida.capacidad_residual[0], 5.0f);
    assert_close(sol_valida.capacidad_residual[1], 2.0f);
    assert_close(sol_valida.costo_total, 8.0f);
    assert_invariants(sol_valida, inst_valida);

    GAPInstance inst_invalida = make_instance(
        "2 2\n"
        "1 4\n"
        "6 2\n"
        "1 1\n"
        "10 1\n"
        "5 2\n"
    );

    GAPSolution sol_invalida(inst_invalida);
    sol_invalida.asignar(0, 0, inst_invalida);
    sol_invalida.asignar(1, 1, inst_invalida);
    float costo_antes = sol_invalida.costo_total;
    vector<float> residual_antes = sol_invalida.capacidad_residual;
    vector<int> asignacion_antes = sol_invalida.asignacion;

    sol_invalida.relocate(0, 1, inst_invalida);

    assert(sol_invalida.asignacion == asignacion_antes);
    assert(sol_invalida.capacidad_residual == residual_antes);
    assert_close(sol_invalida.costo_total, costo_antes);
    assert_invariants(sol_invalida, inst_invalida);
}

void test_swap_valido_con_ficticio_y_invalido() {
    GAPInstance inst_swap = make_instance(
        "2 2\n"
        "1 5\n"
        "6 2\n"
        "1 3\n"
        "3 1\n"
        "5 5\n"
    );

    GAPSolution sol(inst_swap);
    sol.asignar(0, 0, inst_swap);
    sol.asignar(1, -1, inst_swap);

    assert_close(sol.costo_total, 1.0f + 3.0f * inst_swap.getcosto_maximo());

    sol.swap(0, 1, inst_swap);

    assert(sol.asignacion[0] == -1);
    assert(sol.asignacion[1] == 0);
    assert_close(sol.capacidad_residual[0], 2.0f);
    assert_close(sol.costo_total, 23.0f);
    assert_invariants(sol, inst_swap);

    GAPInstance inst_invalido = make_instance(
        "2 2\n"
        "1 5\n"
        "6 2\n"
        "1 10\n"
        "10 1\n"
        "11 2\n"
    );

    GAPSolution sol_invalido(inst_invalido);
    sol_invalido.asignar(0, 0, inst_invalido);
    sol_invalido.asignar(1, 1, inst_invalido);
    float costo_antes = sol_invalido.costo_total;
    vector<float> residual_antes = sol_invalido.capacidad_residual;
    vector<int> asignacion_antes = sol_invalido.asignacion;

    sol_invalido.swap(0, 1, inst_invalido);

    assert(sol_invalido.asignacion == asignacion_antes);
    assert(sol_invalido.capacidad_residual == residual_antes);
    assert_close(sol_invalido.costo_total, costo_antes);
    assert_invariants(sol_invalido, inst_invalido);
}

}  // namespace

int main() {
    // Test: constructor y asignación básica
    test_constructor_y_asignacion_basica();

    // Test: relocate válido e inválido
    test_relocate_valido_e_invalido();

    // Test: swap válido con ficticio e inválido
    test_swap_valido_con_ficticio_y_invalido();

    cout << "Todos los tests pasaron: constructor y asignación básica, relocate válido e inválido, swap válido con ficticio e inválido." << endl;
    return 0;
}
