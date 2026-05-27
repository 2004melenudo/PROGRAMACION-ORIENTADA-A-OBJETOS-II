#include <iostream>
#include <string>
using namespace std;

// Producto complejo
class ComboFastFood {
private:
    string hamburguesa;
    string bebida;
    string papas;

public:
    void setHamburguesa(const string& h) {
        hamburguesa = h;
    }

    void setBebida(const string& b) {
        bebida = b;
    }

    void setPapas(const string& p) {
        papas = p;
    }

    void mostrar() const {
        cout << "\n=== Combo Fast Food ===" << endl;
        cout << "Hamburguesa: " << hamburguesa << endl;
        cout << "Bebida: " << bebida << endl;
        cout << "Papas: " << papas << endl;
    }
};

// Builder
class ComboBuilder {
private:
    ComboFastFood combo;

public:
    ComboBuilder& agregarHamburguesa(const string& h) {
        combo.setHamburguesa(h);
        return *this;
    }

    ComboBuilder& agregarBebida(const string& b) {
        combo.setBebida(b);
        return *this;
    }

    ComboBuilder& agregarPapas(const string& p) {
        combo.setPapas(p);
        return *this;
    }

    ComboFastFood construir() {
        return combo;
    }
};

int main() {
    cout << "=== Builder Pattern ===" << endl;

    // Construcción paso a paso con Fluent Interface
    ComboFastFood combo1 = ComboBuilder()
        .agregarHamburguesa("Doble Queso")
        .agregarBebida("Coca-Cola 500ml")
        .agregarPapas("Medianas")
        .construir();

    combo1.mostrar();

    ComboFastFood combo2 = ComboBuilder()
        .agregarHamburguesa("Pollo Crispy")
        .agregarBebida("Sprite")
        .agregarPapas("Grandes")
        .construir();

    combo2.mostrar();

    return 0;
}
