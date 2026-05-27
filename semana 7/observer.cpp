#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Observer interface
class Observador {
public:
    virtual void notificar(const string& remitente, const string& mensaje) = 0;
    virtual ~Observador() = default;
};

// Subject
class SalaChat {
private:
    vector<shared_ptr<Observador>> usuarios;

public:
    void unir(shared_ptr<Observador> obs) {
        usuarios.push_back(obs);
        cout << "[Sala] Usuario unido" << endl;
    }

    void enviar(const string& remitente, const string& mensaje) {
        cout << "\n--- Nuevo mensaje ---" << endl;

        for (auto& usuario : usuarios) {
            usuario->notificar(remitente, mensaje);
        }
    }
};

// Concrete Observer
class Usuario : public Observador {
private:
    string nombre;

public:
    Usuario(string n) : nombre(n) {}

    void notificar(const string& remitente, const string& mensaje) override {
        if (remitente != nombre) { // No notificar al propio emisor
            cout << "[" << nombre << "] " << remitente << ": "
                 << mensaje << endl;
        }
    }

    string getNombre() const {
        return nombre;
    }
};

int main() {
    cout << "=== Observer Pattern ===" << endl;

    auto sala = make_shared<SalaChat>();
    auto ana = make_shared<Usuario>("Ana");
    auto luis = make_shared<Usuario>("Luis");
    auto marta = make_shared<Usuario>("Marta");

    sala->unir(ana);
    sala->unir(luis);
    sala->unir(marta);

    cout << "\n--- Enviando mensajes ---" << endl;
    sala->enviar("Ana", "Hola equipo!");
    sala->enviar("Luis", "Listo para la mision");
    sala->enviar("Marta", "Vamos alli!");

    return 0;
}
