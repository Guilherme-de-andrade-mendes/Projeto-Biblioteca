#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    char input[100];  // Altere o tamanho do array conforme necessário

    printf("Digite uma frase: ");
    fgets(input, sizeof(input), stdin);

    printf("Você digitou: %s\n", input);

    return 0;
}
