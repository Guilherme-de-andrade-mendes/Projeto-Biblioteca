#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para converter uma string de data para struct tm
struct tm parse_date(char *date_str) {
    struct tm date = {0};
    sscanf(date_str, "%d/%d/%d", &date.tm_mday, &date.tm_mon, &date.tm_year);
    date.tm_mon--; // Ajuste, pois tm_mon inicia em 0 para janeiro
    date.tm_year -= 1900; // Ajuste, pois tm_year conta os anos desde 1900
    return date;
}

// Função para calcular a idade com base na data de nascimento
int calcularIdade(struct tm dataNascimento) {
    time_t agora;
    time(&agora);
    struct tm *dataAtual = localtime(&agora);

    int idade = dataAtual->tm_year - dataNascimento.tm_year;

    // Ajustes para considerar o mês e o dia de nascimento
    if (dataNascimento.tm_mon > dataAtual->tm_mon ||
        (dataNascimento.tm_mon == dataAtual->tm_mon && dataNascimento.tm_mday > dataAtual->tm_mday)) {
        idade--;
    }

    return idade;
}

int main() {
    char dataStr[11];
    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(dataStr, sizeof(dataStr), stdin);
    struct tm dataNascimento = parse_date(dataStr);

    int idade = calcularIdade(dataNascimento);

    printf("A idade é: %d anos\n", idade);

    return 0;
}
