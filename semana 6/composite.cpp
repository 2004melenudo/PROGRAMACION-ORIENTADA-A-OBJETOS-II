#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Componente base
class Componente {
protected:
    string nombre;

public:
    Componente(string n) : nombre(n) {}

    virtual void mostrar(int nivel = 0) = 0;
    virtual ~Componente() = default;

    string getNombre() const {
        return nombre;
    }
};

// Hoja (Leaf)
class Archivo : public Componente {
public:
    Archivo(string n) : Componente(n) {}

    void mostrar(int nivel = 0) override {
        cout << string(nivel * 4, ' ') << "- " << nombre << endl;
    }
};

// Compuesto (Composite)
class Carpeta : public Componente {
private:
    vector<shared_ptr<Componente>> hijos;

public:
    Carpeta(string n) : Componente(n) {}

    void agregar(shared_ptr<Componente> c) {
        hijos.push_back(c);
    }

    void mostrar(int nivel = 0) override {
        cout << string(nivel * 4, ' ') << "+ " << nombre << endl;

        for (auto& hijo : hijos) {
            hijo->mostrar(nivel + 1);
        }
    }
};

int main() {
    cout << "=== Composite Pattern ===" << endl;

    // Crear estructura jerarquica
    auto raiz = make_shared<Carpeta>("Documentos");

    auto archivo1 = make_shared<Archivo>("reporte.pdf");
    auto archivo2 = make_shared<Archivo>("datos.xlsx");

    auto subcarpeta = make_shared<Carpeta>("Imagenes");
    auto img1 = make_shared<Archivo>("logo.png");
    auto img2 = make_shared<Archivo>("foto.jpg");

    // Construir arbol
    subcarpeta->agregar(img1);
    subcarpeta->agregar(img2);

    raiz->agregar(archivo1);
    raiz->agregar(archivo2);
    raiz->agregar(subcarpeta);

    // Mostrar estructura completa
    cout << "\nEstructura de archivos:" << endl;
    raiz->mostrar();

    cout << "\n[Nota] Composite trata hojas y compuestos uniformemente."
         << endl;

    return 0;
}
