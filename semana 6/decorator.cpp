#include <iostream>
#include <memory>
#include <cmath>
using namespace std;

// Componente base
class FuncionMatematica {
public:
    virtual double calcular(double x) = 0;
    virtual ~FuncionMatematica() = default;
};

// Componente concreto
class RaizCuadrada : public FuncionMatematica {
public:
    double calcular(double x) override {
        return sqrt(x);
    }
};

// Decorator base
class ValidadorDecorator : public FuncionMatematica {
protected:
    shared_ptr<FuncionMatematica> funcion;

public:
    ValidadorDecorator(shared_ptr<FuncionMatematica> f)
        : funcion(f) {}

    double calcular(double x) override {
        return funcion->calcular(x);
    }
};

// Decorador concreto: validación
class ValidadorPositivos : public ValidadorDecorator {
public:
    ValidadorPositivos(shared_ptr<FuncionMatematica> f)
        : ValidadorDecorator(f) {}

    double calcular(double x) override {
        if (x <= 0) {
            throw invalid_argument("La funcion requiere valores positivos");
        }

        cout << "[Validador] Entrada valida: " << x << endl;
        return funcion->calcular(x);
    }
};

// Decorador concreto: logging
class LoggerDecorator : public ValidadorDecorator {
public:
    LoggerDecorator(shared_ptr<FuncionMatematica> f)
        : ValidadorDecorator(f) {}

    double calcular(double x) override {
        cout << "[Logger] Calculando para x = " << x << endl;
        double resultado = funcion->calcular(x);
        cout << "[Logger] Resultado: " << resultado << endl;
        return resultado;
    }
};

int main() {
    cout << "=== Decorator Pattern ===" << endl;

    try {
        // Componente base
        auto raiz = make_shared<RaizCuadrada>();

        // Decorar con validación
        auto validada = make_shared<ValidadorPositivos>(raiz);

        // Decorar con logging
        auto con_log = make_shared<LoggerDecorator>(validada);

        cout << "\nPrueba con valor valido (25):" << endl;
        cout << "Resultado: " << con_log->calcular(25) << endl;

        cout << "\nPrueba con valor invalido (-4):" << endl;
        cout << "Resultado: " << con_log->calcular(-4) << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
