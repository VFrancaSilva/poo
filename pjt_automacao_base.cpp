#include <iostream>
#include <string>

using namespace std;

// Modela um transmissor de nivel
class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double valorAtual;

public:
    // Construtor minimo: sensor detectado, usa valores padrao de seguranca
    SensorNivel(string t) : tag(t), minimo(0.0), maximo(100.0), valorAtual(0.0) {}

    // Construtor completo: sensor parametrizado pela engenharia
    SensorNivel(string t, double min, double max, double atual) : tag(t), valorAtual(atual) {
        // Valida se o range e coerente
        if (min < max) {
            this->minimo = min;
            this->maximo = max;
        } else {
            cout << "[Alarme] " << tag << ": Range invalido. Usando 0-100.\n";
            this->minimo = 0.0;
            this->maximo = 100.0;
        }
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << tag << " | faixa: " << minimo << " a " << maximo << " | valor atual: " << valorAtual << "\n";
    }
};

// Modela uma bomba de recalque
class Bomba {
private:
    string tag;
    double velocidade;

public:
    // Construtor minimo: bomba nasce parada
    Bomba(string t) : tag(t), velocidade(0.0) {}

    // Construtor completo: bomba recebe setpoint inicial
    Bomba(string t, double vel) : tag(t) {
        // Valida limites de velocidade (0 a 100%)
        if (vel >= 0.0 && vel <= 100.0) {
            this->velocidade = vel;
        } else {
            cout << "[Alarme] " << tag << ": Velocidade fora do limite. Parando bomba.\n";
            this->velocidade = 0.0;
        }
    }

    void exibirResumo() const {
        cout << "[Bomba] " << tag << " | velocidade: " << velocidade << "%\n";
    }
};

// Modela um controlador PID da malha
class ControladorTanque {
private:
    string tag;
    double setpoint;
    double kp;

public:
    // Construtor minimo: aguardando sintonia
    ControladorTanque(string t) : tag(t), setpoint(0.0), kp(1.0) {}

    // Construtor completo: parametros sintonizados
    ControladorTanque(string t, double sp, double ganho) : tag(t), setpoint(sp) {
        // Garante ganho proporcional positivo
        if (ganho > 0.0) {
            this->kp = ganho;
        } else {
            cout << "[Alarme] " << tag << ": Kp invalido. Aplicando Kp=1.0.\n";
            this->kp = 1.0;
        }
    }

    void exibirResumo() const {
        cout << "[ControladorTanque] " << tag << " | SP=" << setpoint << " | Kp=" << kp << "\n";
    }
};

int main() {
    cout << "--- INICIALIZANDO GÊMEOS DIGITAIS ---\n\n";

    // Criando equipamentos apenas com a tag (Construtor Minimo)
    SensorNivel sn1("LT-401");
    Bomba b1("P-201");
    ControladorTanque ct1("LIC-101");

    // Criando equipamentos com parametros corretos (Construtor Completo)
    SensorNivel sn2("LT-402", 0.0, 5000.0, 2780.0);
    Bomba b2("P-202", 65.5);
    ControladorTanque ct2("LIC-102", 2500.0, 2.5);
    
    // TESTES DE VALIDAÇÃO: Parametrizando com valores absurdos
    SensorNivel sn3("LT-403", 500.0, 10.0, 250.0);  // Range invertido
    Bomba b3("P-203", 150.0);                       // Velocidade > 100%
    ControladorTanque ct3("LIC-103", 1200.0, -2.0); // Ganho Kp negativo
    
    cout << "\n--- RESUMO DOS EQUIPAMENTOS ---\n";
    
    // Imprimindo relatorio
    sn1.exibirResumo();
    sn2.exibirResumo();
    sn3.exibirResumo(); // Vai exibir faixa corrigida para 0-100
    cout << "--------------------------------------\n";
    
    b1.exibirResumo();
    b2.exibirResumo();
    b3.exibirResumo(); // Vai exibir velocidade cortada para 0%
    cout << "--------------------------------------\n";
    
    ct1.exibirResumo();
    ct2.exibirResumo();
    ct3.exibirResumo(); // Vai exibir Kp corrigido para 1

    return 0;
}