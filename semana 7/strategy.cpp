#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Strategy interface
class EstrategiaOrden {
public:
    virtual void ordenar(vector<int>& datos) = 0;
    virtual string getNombre() const = 0;
    virtual ~EstrategiaOrden() = default;
};

// Concrete Strategy: Bubble Sort
class Burbuja : public EstrategiaOrden {
public:
    void ordenar(vector<int>& d) override {
        for (size_t i = 0; i < d.size(); ++i) {
            for (size_t j = 0; j < d.size() - i - 1; ++j) {
                if (d[j] > d[j + 1]) {
                    swap(d[j], d[j + 1]);
                }
            }
        }
    }

    string getNombre() const override {
        return "Bubble Sort";
    }
};

// Concrete Strategy: Quick Sort
class QuickSort : public EstrategiaOrden {
private:
    void quick(vector<int>& d, int left, int right) {
        if (left < right) {
            int pivot = d[(left + right) / 2];
            int i = left;
            int j = right;

            while (i <= j) {
                while (d[i] < pivot) i++;
                while (d[j] > pivot) j--;

                if (i <= j) {
                    swap(d[i], d[j]);
                    i++;
                    j--;
                }
            }

            quick(d, left, j);
            quick(d, i, right);
        }
    }

public:
    void ordenar(vector<int>& d) override {
        quick(d, 0, d.size() - 1);
    }

    string getNombre() const override {
        return "Quick Sort";
    }
};

// Context
class Contexto {
private:
    shared_ptr<EstrategiaOrden> estrategia;

public:
    Contexto(shared_ptr<EstrategiaOrden> e) : estrategia(e) {}

    void cambiarEstrategia(shared_ptr<EstrategiaOrden> e) {
        estrategia = e;
    }

    void ejecutar(vector<int>& datos) {
        cout << "\nUsando " << estrategia->getNombre() << endl;
        estrategia->ordenar(datos);
    }
};

int main() {
    cout << "=== Strategy Pattern ===" << endl;

    vector<int> datos = {64, 34, 25, 12, 22, 11, 90};

    cout << "\nDatos originales: ";
    for (int x : datos) cout << x << " ";

    // Contexto con Bubble Sort
    Contexto ctx(make_shared<Burbuja>());
    vector<int> datos1 = datos;
    ctx.ejecutar(datos1);

    cout << "Ordenado: ";
    for (int x : datos1) cout << x << " ";

    // Cambiar a Quick Sort
    ctx.cambiarEstrategia(make_shared<QuickSort>());
    vector<int> datos2 = datos;
    ctx.ejecutar(datos2);

    cout << "Ordenado: ";
    for (int x : datos2) cout << x << " ";

    cout << "\n\n[Nota] Strategy permite cambiar algoritmo en runtime."
         << endl;

    return 0;
}
