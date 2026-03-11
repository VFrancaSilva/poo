class Valvula:
    def __init__(self, tag, abertura):
        self.tag = tag
        self.abertura = abertura

    def exibir_estado(self):
        print(f"{self.tag} -> {self.abertura}%")


v1 = Valvula("XV-02", 35.0)
v1.exibir_estado()