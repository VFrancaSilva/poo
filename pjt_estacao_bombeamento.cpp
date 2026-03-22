#include <iostream>
#include <string>

using namespace std;

// =========================================================
// CLASSE BASE: AtivoCampo
// =========================================================
class AtivoCampo {
private:
    string tag;
    bool bloqueado = false; // Inicializacao direta (C++11)

protected:
    string area;
    void redefinirArea(string novaArea) { area = novaArea; } // Método inline

public:
    AtivoCampo(string t, string a) : tag(t), area(a) {}

    // Métodos compactados
    string getTag() const { return tag; }
    bool estaBloqueado() const { return bloqueado; }
    void bloquear() { bloqueado = true; }
    void liberar() { bloqueado = false; }
};

// =========================================================
// CLASSE DERIVADA: SensorNivel
// =========================================================
class SensorNivel : public AtivoCampo {
private:
    double nivelAtual = 0.0; 
    double limiteAlto;

public:
    SensorNivel(string novaTag, string novaArea, double limite) 
        : AtivoCampo(novaTag, novaArea), limiteAlto(limite) {}

    void atualizarNivel(double novoNivel) {
        if (estaBloqueado()) { cout << "[Alarme] " << getTag() << ": Sensor bloqueado para manutencao. Nivel descartado.\n"; return; }
        if (novoNivel < 0.0) { cout << "[Erro] " << getTag() << ": Nivel negativo (" << novoNivel << ") invalido.\n"; return; }
        nivelAtual = novoNivel;
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << getTag() << " | Area: " << area << " | Nivel Atual: " << nivelAtual << " | Limite: " << limiteAlto << "\n";
    }

    friend void inspecaoTecnica(const SensorNivel& sensor);
};

// =========================================================
// FUNCAO FRIEND DE SENSOR
// =========================================================
void inspecaoTecnica(const SensorNivel& sensor) {
    cout << "\n--- INSPETOR TECNICO ACIONADO ---\n";
    cout << "Acessando banco de dados interno do ativo: " << sensor.getTag() << "\n";
    cout << "Leitura bruta de memoria - Nivel: " << sensor.nivelAtual << " | Parametro de Limite: " << sensor.limiteAlto << "\n";
    cout << "Status da auditoria: Conforme.\n";
}

// =========================================================
// CLASSE DERIVADA: BombaDosadora
// =========================================================
class BombaDosadora : public AtivoCampo {
private:
    double vazaoPercentual = 0.0;

public:
    BombaDosadora(string novaTag, string novaArea) : AtivoCampo(novaTag, novaArea) {}

    void ajustarVazao(double novaVazao) {
        if (estaBloqueado()) { cout << "[Alarme] " << getTag() << ": Bomba bloqueada eletricamente. Comando de vazao rejeitado.\n"; return; }
        if (novaVazao >= 0.0 && novaVazao <= 100.0) vazaoPercentual = novaVazao;
        else cout << "[Erro] " << getTag() << ": Comando de vazao (" << novaVazao << "%) fora da faixa operacional.\n";
    }

    void moverParaArea(string novaArea) {
        redefinirArea(novaArea);
        cout << "[Log] O ativo " << getTag() << " foi remanejado para a area: " << novaArea << "\n";
    }

    void exibirResumo() const {
        cout << "[BombaDosadora] " << getTag() << " | Area: " << area << " | Vazao Atual: " << vazaoPercentual << "%\n";
    }
};

// =========================================================
// PROGRAMA PRINCIPAL
// =========================================================
int main() {
    cout << "=== INICIANDO PLANTA DE PROCESSO ===\n\n";

    SensorNivel sn1("LIT-401", "Tanque_A", 80.0);
    BombaDosadora bd1("P-101", "Tratamento_Quimico");

    sn1.atualizarNivel(45.5);
    bd1.ajustarVazao(60.0);

    sn1.exibirResumo();
    bd1.exibirResumo();

    cout << "\n=== SIMULANDO FALHAS E MANUTENCAO ===\n";

    sn1.atualizarNivel(-10.0);
    
    bd1.bloquear();
    bd1.ajustarVazao(100.0); 
    
    bd1.moverParaArea("Oficina_Central");

    cout << "\n=== RESUMO APOS MANUTENCAO ===\n";
    sn1.exibirResumo();
    bd1.exibirResumo();

    inspecaoTecnica(sn1);

    return 0;
}