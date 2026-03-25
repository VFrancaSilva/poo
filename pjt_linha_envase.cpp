#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================
// CLASSE ABSTRATA: AtuadorLinha (A "Interface" da rede)
// =========================================================
class AtuadorLinha {
private:
    string tag;
    string area;

protected:
    double limitarPercentual(double percentual) const {
        if (percentual < 0.0) return 0.0;
        if (percentual > 100.0) return 100.0;
        return percentual;
    }

public:
    AtuadorLinha(string novaTag, string novaArea)
        : tag(novaTag), area(novaArea) {}

    virtual ~AtuadorLinha() = default;

    string getTag() const { return tag; }
    string getArea() const { return area; }

    virtual void aplicarReferenciaPercentual(double percentual) = 0;
    virtual void exibirResumo() const = 0;
};

// =========================================================
// CLASSE DERIVADA 1: MotorEsteira
// =========================================================
class MotorEsteira : public AtuadorLinha {
private:
    double frequenciaHz;

public:
    MotorEsteira(string novaTag, string novaArea) 
        : AtuadorLinha(novaTag, novaArea), frequenciaHz(0.0) {}

    void aplicarReferenciaPercentual(double percentual) override {
        double percentualSeguro = limitarPercentual(percentual);
        frequenciaHz = percentualSeguro * 0.6;
    }

    void exibirResumo() const override {
        cout << "[Motor] Tag: " << getTag() 
             << " | Area: " << getArea() 
             << " | Frequencia: " << frequenciaHz << " Hz\n";
    }
};

// =========================================================
// CLASSE DERIVADA 2: ValvulaDosagem
// =========================================================
class ValvulaDosagem : public AtuadorLinha {
private:
    double aberturaPercentual;

public:
    ValvulaDosagem(string novaTag, string novaArea) 
        : AtuadorLinha(novaTag, novaArea), aberturaPercentual(0.0) {}

    void aplicarReferenciaPercentual(double percentual) override {
        aberturaPercentual = limitarPercentual(percentual);
    }

    void exibirResumo() const override {
        cout << "[Valvula] Tag: " << getTag() 
             << " | Area: " << getArea() 
             << " | Abertura: " << aberturaPercentual << "%\n";
    }
};

// =========================================================
// PROGRAMA PRINCIPAL
// =========================================================
int main() {
    cout << "--- COMANDO DE REDE MULTIPONTO ---\n\n";

    // 1. Criar instâncias físicas dos equipamentos
    MotorEsteira motor("M-101", "Esteira_Principal");
    ValvulaDosagem valvula("V-201", "Misturador_Quimico");

    // 2. Criar um vetor polimórfico usando ponteiros para a classe base
    vector<AtuadorLinha*> redeAtuadores;
    redeAtuadores.push_back(&motor);
    redeAtuadores.push_back(&valvula);

    // 3. Receber o set point desejado do usuário via teclado
    double setpointDesejado;
    cout << "Digite o setpoint global desejado (0 a 100%): ";
    cin >> setpointDesejado;

    // --- NOVO: ALARME DE LIMITE OPERACIONAL ---
    if (setpointDesejado < 0.0 || setpointDesejado > 100.0) {
        cout << "\n[ALARME SCADA] Atencao! O setpoint de " << setpointDesejado 
             << "% esta fora dos limites (0-100%)." << endl;
        cout << ">> O intertravamento forcou o comando para o limite mais seguro.\n";
    }

    // 4. Aplicar o setpoint a todos os dispositivos da rede num único laço
    cout << "\n>> Transmitindo comando global para a rede...\n\n";
    for (AtuadorLinha* atuador : redeAtuadores) {
         atuador->aplicarReferenciaPercentual(setpointDesejado);
    }

    // 5. Exibir o resumo do chão de fábrica
    cout << "--- STATUS ATUAL DOS EQUIPAMENTOS ---\n";
    cout << "--- COMANDO ENVIADO: " << setpointDesejado << "% ---\n";
    for (AtuadorLinha* atuador : redeAtuadores) {
        atuador->exibirResumo();
    }

    return 0;
}