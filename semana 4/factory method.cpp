#include <iostream>
#include <memory>
#include <string>
using namespace std;
// Producto base
class Transporte {
public:
    virtual void entregar() = 0;
    virtual ~Transporte() = default;
};

// Productos concretos
class Camion : public Transporte {
public:
    void entregar() override {
        cout << "Entrega por carretera (12 horas)" << endl;
    }
};

class Barco : public Transporte {
public:
    void entregar() override {
        cout << "Entrega maritima (15 dias)" << endl;
    }
};

class Avion : public Transporte {
public:
    void entregar() override {
        cout << "Entrega aerea (2 horas)" << endl;
    }
};

// Factory
class FactoryTransporte {
public:
    static unique_ptr<Transporte> crear(const string& tipo) {
        if (tipo == "camion") {
            return make_unique<Camion>();
        } else if (tipo == "barco") {
            return make_unique<Barco>();
        } else if (tipo == "avion") {
            return make_unique<Avion>();
        }

        throw invalid_argument("Tipo no soportado: " + tipo);
    }
};

int main() {
    cout << "=== Factory Method ===" << endl;

    auto t1 = FactoryTransporte::crear("camion");
    auto t2 = FactoryTransporte::crear("barco");
    auto t3 = FactoryTransporte::crear("avion");

    cout << "Transporte 1: ";
    t1->entregar();

    cout << "Transporte 2: ";
    t2->entregar();

    cout << "Transporte 3: ";
    t3->entregar();

    // No necesita delete: unique_ptr gestiona automaticamente
    return 0;
}
