#include <iostream>
#include <iomanip>

// Função para simular o cálculo de vazão em um duto
double calcularVazao(double area, double velocidade) {
    return area * velocidade;
}

int main() {
    double area = 0.05;       // m²
    double velocidade = 2.5;  // m/s

    double vazao = calcularVazao(area, velocidade);

    std::cout << "--- Sistema de Monitoramento Industrial ---" << std::endl;
    std::cout << "Area do duto: " << area << " m2" << std::endl;
    std::cout << "Velocidade do fluido: " << velocidade << " m/s" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Vazao calculada: " << vazao << " m3/s" << std::endl;

    return 0;
}