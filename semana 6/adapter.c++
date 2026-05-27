#include <iostream>
#include <string>
using namespace std;

// Interfaz existente incompatible
class PasarelaUSD {
public:
    string procesar_pago(double monto_usd) {
        return "Cobrado " + to_string(monto_usd) + " USD";
    }
};

// Interfaz que el cliente necesita
class PagosSoles {
public:
    virtual string procesar_pago_soles(double monto_pen) = 0;
    virtual ~PagosSoles() = default;
};

// Adapter: convierte Soles a USD
class AdaptadorSoles : public PagosSoles {
private:
    PasarelaUSD* pasarela;
    double tasa; // Tipo de cambio

public:
    AdaptadorSoles(PasarelaUSD* p, double t = 3.70)
        : pasarela(p), tasa(t) {}

    string procesar_pago_soles(double monto_pen) override {
        double usd = monto_pen / tasa;
        return pasarela->procesar_pago(usd);
    }
};

int main() {
    cout << "=== Adapter Pattern ===" << endl;

    PasarelaUSD api_usd;
    AdaptadorSoles adapter(&api_usd, 3.70);

    cout << "Pago en soles (100 PEN): "
         << adapter.procesar_pago_soles(100.0) << endl;

    cout << "\n[Nota] El adapter permite usar PasarelaUSD "
         << "sin modificar su código, solo adaptando la interfaz." << endl;

    return 0;
}
