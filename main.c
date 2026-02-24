#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float nota;
} Aluno;

void inicializarAluno(Aluno *a, const char *nome, int idade, float nota) {
    strncpy(a->nome, nome, sizeof(a->nome) - 1);
    a->nome[sizeof(a->nome) - 1] = '\0';
    a->idade = idade;
    a->nota = nota;
}

void exibirAluno(const Aluno *a) {
    printf("Nome: %s\n", a->nome);
    printf("Idade: %d\n", a->idade);
    printf("Nota: %.2f\n", a->nota);
}

int main() {
    Aluno aluno1;

    inicializarAluno(&aluno1, "Vinicius", 20, 8.5);
    exibirAluno(&aluno1);

    return 0;
}
