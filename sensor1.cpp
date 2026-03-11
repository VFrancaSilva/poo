#include <iostream>
#include <string>
using namespace std;

class Valvula {
public:
    string tag;
    double abertura;

    Valvula(string novaTag, double aberturaInicial) {
        tag = novaTag;
        abertura = aberturaInicial;
    }

    void exibirEstado() {
        cout << tag << " -> " << abertura << "%\n";
    }
};

int main() {
    Valvula v1("XV-02", 35.0);
    v1.exibirEstado();
    return 0;
}