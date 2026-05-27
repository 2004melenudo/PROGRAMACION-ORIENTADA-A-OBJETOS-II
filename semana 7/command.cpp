#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Receiver
class Editor {
private:
    string texto;
    string ultimo_texto; // Para undo

public:
    void escribir(const string& t) {
        ultimo_texto = texto; // Guardar estado anterior
        texto += t;
    }

    void limpiar() {
        ultimo_texto = texto;
        texto = "";
    }

    void ver() const {
        cout << "Contenido: " << texto << "" << endl;
    }

    string getTexto() const {
        return texto;
    }

    string getUltimoTexto() const {
        return ultimo_texto;
    }
};

// Command interface
class Comando {
public:
    virtual void ejecutar() = 0;
    virtual void deshacer() = 0;
    virtual ~Comando() = default;
};

// Concrete Command
class EscribirCmd : public Comando {
private:
    Editor* editor;
    string texto;
    string texto_anterior;

public:
    EscribirCmd(Editor* e, const string& t)
        : editor(e), texto(t) {}

    void ejecutar() override {
        texto_anterior = editor->getTexto();
        editor->escribir(texto);
    }

    void deshacer() override {
        editor->limpiar();
        editor->escribir(texto_anterior);
    }
};

// Invoker
class Historial {
private:
    vector<shared_ptr<Comando>> pila;

public:
    void ejecutar(shared_ptr<Comando> cmd) {
        cmd->ejecutar();
        pila.push_back(cmd);
    }

    void deshacer() {
        if (!pila.empty()) {
            pila.back()->deshacer();
            pila.pop_back();
        } else {
            cout << "[Historial] No hay comandos para deshacer" << endl;
        }
    }
};

int main() {
    cout << "=== Command Pattern ===" << endl;

    Editor ed;
    Historial h;

    cout << "\n--- Ejecutando comandos ---" << endl;

    auto cmd1 = make_shared<EscribirCmd>(&ed, "Hola ");
    auto cmd2 = make_shared<EscribirCmd>(&ed, "Mundo");

    h.ejecutar(cmd1);
    ed.ver();

    h.ejecutar(cmd2);
    ed.ver();

    cout << "\n--- Deshaciendo ---" << endl;

    h.deshacer();
    ed.ver();

    h.deshacer();
    ed.ver();

    return 0;
}
