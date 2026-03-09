#include <iostream>
#include <vector>
using namespace std;

double media(const vector<double>& valores) {
    double soma = 0.0;
    for (double v : valores) soma += v;
    return valores.empty() ? 0.0 : soma / valores.size();
}

int main() {
    cout << "Informe os valores lidos: " << endl;
    double temp1, temp2, temp3, temp4;
    cin >> temp1 >> temp2 >> temp3 >> temp4;
    vector<double> leituras = {temp1, temp2, temp3, temp4};
    cout << "Media das Temperaturas: " << media(leituras) << endl;
    return 0;
}