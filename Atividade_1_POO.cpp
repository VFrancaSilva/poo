//------------------------------------
// Atividade 01 - POO
// Nome: Vinicius França da Silva
// Matrícula: 20192CECA70067
//------------------------------------


#include <iostream>
#include <string>

using namespace std;

class Carro {
  private:
    int velocidadeInstantanea;

  public:
    string marca;
    string modelo;
    int ano;

    Carro() : velocidadeInstantanea(0) {}

    // Acelerador
    void acelerar(int taxa) {
      velocidadeInstantanea += taxa;
      cout << "Acelerando em " << taxa << " km/h... Velocidade atual: " << velocidadeInstantanea << " km/h" << endl;
    }

    // Freio
    void frear(int taxa) {
      velocidadeInstantanea -= taxa;
      if (velocidadeInstantanea < 0) velocidadeInstantanea = 0;
      cout << "Freando em " << taxa << " km/h... Velocidade atual: " << velocidadeInstantanea << " km/h" << endl;
    }

	// Retorna Velocidade
    int obterVelocidade() {
      return velocidadeInstantanea;
    }
};

int main() {
  Carro meuCarro;
  
  cout << "Digite a marca do carro: ";
  cin >> meuCarro.marca;
  cout << "Digite o modelo do carro: ";
  cin >> meuCarro.modelo;
  cout << "Digite o ano do carro: ";
  cin >> meuCarro.ano;

  cout << "--- Veiculo: " << meuCarro.marca << " " << meuCarro.modelo << " " << meuCarro.ano << " ---" << endl;
  
  cout << "Digite a velocidade desejada: ";
  int velocidadeDesejada; 
  
  meuCarro.acelerar(velocidadeDesejada);  // Acelera 1
  meuCarro.acelerar(23);  // Acelera 2
  meuCarro.acelerar(15);  // Acelera 3
  meuCarro.frear(40);     // Freia 1

  cout << "\n--- Resultado Final ---" << endl;
  cout << "Velocidade final medida no objeto: " << meuCarro.obterVelocidade() << " km/h" << endl;

  return 0;
}