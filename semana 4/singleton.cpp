#include <iostream>
#include <string>
using namespace std;

class Config {
private:
    static Config* instance;   // única instancia estática
    string valor;

    Config() : valor("configuracion por defecto") {
        cout << "[Singleton] Instancia creada." << endl;
    }

    // Eliminar copia y asignación
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

public:
    static Config* getInstance() {
        if (!instance) {
            instance = new Config();
        }

        return instance;
    }

    void setValor(string v) {
        valor = v;
    }

    string getValor() const {
        return valor;
    }

    ~Config() {
        cout << "[Singleton] Instancia destruida." << endl;
    }
};

// Inicialización de variable estática
Config* Config::instance = nullptr;
int main() {
    cout << "=== Prueba de Singleton ===" << endl;

    Config* obj1 = Config::getInstance();
    Config* obj2 = Config::getInstance();

    cout << "Son la misma instancia? "
         << boolalpha << (obj1 == obj2) << endl;

    obj1->setValor("nueva configuracion");

    cout << "Valor desde obj1: " << obj1->getValor() << endl;
    cout << "Valor desde obj2: " << obj2->getValor() << endl;

    delete Config::getInstance(); // Liberación manual

    return 0;
}
