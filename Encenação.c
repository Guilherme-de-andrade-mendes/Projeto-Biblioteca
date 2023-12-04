#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char cpf[12];
    char nome[100];
    char nascimento[11];
    char rua[100];
    char cep[11];
    char telefones[100][15];
    char emails[100][50];
    char profissao[100];
} User;

typedef struct{
    char isbn[13];
    char titulo[100];
    char genero[100];
    char autores[100][10];
    int qntautores[255];
    int numPaginas;
} Book;

typedef struct{
    char codcpf[12];
    char codisbn[13];
    char retirada[11];
    char devolucao[11];
    float multa;
} Loan;

struct tm parse_date(char *data){
    struct tm tm = {0};
    char *token;
    token = strtok(data, "/");
    tm.tm_mday = atoi(token);
    token = strtok(NULL, "/");
    tm.tm_mon = atoi(token) - 1;
    token = strtok(NULL, "/");
    tm.tm_year = atoi(token) - 1900;
    if (tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mon > 11 || tm.tm_mday < 1 || tm.tm_mday > 31 || (tm.tm_mday > 30 && (tm.tm_mon == 3 || tm.tm_mon == 5 || tm.tm_mon == 8 || tm.tm_mon == 10)) || (tm.tm_mday > 29 && tm.tm_mon == 1) || (tm.tm_mday > 28 && tm.tm_mon == 1 && !(tm.tm_year % 4 == 0 && (tm.tm_year % 100 != 0 || tm.tm_year % 400 == 0)))) {
        tm.tm_year = -1;
        tm.tm_mon = -1;
        tm.tm_mday = -1;
    }
    return tm;
}

void Linhas() {
    printf("==========================================================================================\n");
}

int MenuPrincipal() {
    int op;
    Linhas();
    printf("Gerenciamento de Biblioteca\n\n1-Submenu de Usuários.\n2-Submenu de Livros.\n3-Submenu de Empréstimos.\n4-Submenu de Relatórios.\n5-Sair.\nEntre com o número do submenu desejado: ");
    scanf("%d", &op);
    return op;
}

int Submenus() {
    int op;
    Linhas();
    printf("1-Incluir.\n2-Listar todos.\n3-Listar um elemento específico\n4-Alterar.\n5-Excluir.\n6-Voltar.\nEntre com o número da funcionalidade desejada: ");
    scanf("%d", &op);
    return op;
}

int SubmenuRelatorios() {
    int op;
    Linhas();
    printf("1-Mostrar todos os usuários pela idade.\n2-Mostrar todos os livros por seu(s) autor(es).\n3-Mostrar dados por meio de empréstimo.\n4-Voltar.\nEntre com o número da funcionalidade desejada: ");
    scanf("%d", &op);
    return op;
}

int existeUsuario(User *usuarios, int qntUserAtual, char *cpf) {
    int i;
    for (i = 0; i < qntUserAtual; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0)
            return 1;
    }
    return 0;
}

int validarCPF(char *cpf) {
    int i;
    for (i = 0; i < 12; i++) {
        if (!isdigit(cpf[i]) && cpf[i] != '\0') {
            return 0;
        }
    }
    return 1;
}

void incluirUsuario(User *usuarios, int *indUser) {
    printf("====================== Incluindo Usuário ======================\n");
    char cpf[12];
    int x = 1;
    while (x != 0) {
        printf("CPF: ");
        scanf("%s", cpf);
        int valido = validarCPF(cpf);
        int existeUser = existeUsuario(usuarios, *indUser, cpf);
        if (existeUser == 0 && valido) {
            strcpy(usuarios[*indUser].cpf, cpf);
            x = 0;
            break;
        } else if (!valido) {
            printf("CPF inválido. Tente novamente.\n");
        } else {
            printf("Esse CPF já existe na base de dados. Tente novamente.\n");
        }
    }
    printf("Nome: ");
    scanf("%s", usuarios[*indUser].nome);
    char data[11];
    int l = 0;
    while (l != 1) {
        printf("Data de nascimento (dd/mm/aaaa): ");
        scanf("%s", data);
        struct tm valiData = parse_date(data);
        if (valiData.tm_year >= 0) {
            strftime(usuarios[*indUser].nascimento, sizeof(usuarios[*indUser].nascimento), "%d/%m/%Y", &valiData);
            l = 1;
        }
    }
    printf("Rua: ");
    scanf("%s", usuarios[*indUser].rua);
    printf("CEP (xxxxxxxx): ");
    scanf("%s", usuarios[*indUser].cep);
    int numTelefones = 0, y = 1;
    while (y != 0) {
        printf("Telefone (xxxxx-xxxx): ");
        scanf("%s", usuarios[*indUser].telefones[numTelefones]);
        numTelefones++;
        char resp;
        printf("Deseja inserir mais um telefone (s/n)?: ");
        scanf(" %c", &resp);
        if (resp == 'n') {
            y = 0;
        }
    }
    int numEmails = 0, z = 1;
    while (z != 0) {
        printf("Email: ");
        scanf("%s", usuarios[*indUser].emails[numEmails]);
        numEmails++;
        char resp;
        printf("Deseja inserir mais um email (s/n)?: ");
        scanf(" %c", &resp);
        if (resp == 'n') {
            z = 0;
        }
    }
    printf("Profissão: ");
    scanf("%s", usuarios[*indUser].profissao);
    (*indUser)++;
    printf("Usuario incluído com sucesso!\n");
}

void imprimirDadosDoUsuario(User *usuarios, int qntUserAtual) {
    printf("====================== Listar todos os usuários ======================\n");
    int i;
    for (i = 0; i < qntUserAtual; i++) {
        printf("Usuario %d* | Cpf: %s | Nome: %s | Data de nascimento: %s | Rua: %s | CEP: %s | ", (i + 1), usuarios[i].cpf, usuarios[i].nome, usuarios[i].nascimento, usuarios[i].rua, usuarios[i].cep);
        printf("Telefone(s): [ ");
        int j;
        for ( j = 0; j < 100; j++) {
            if (usuarios[i].telefones[j][0] != '\0') {
                printf("%s ", usuarios[i].telefones[j]);
            }
        }
        printf("] | Email(s): [ ");
        int l;
        for (l = 0; l < 100; l++) {
            if (usuarios[i].emails[l][0] != '\0') {
                printf("%s ", usuarios[i].emails[l]);
            }
        }
        printf("] | Profissão: %s\n", usuarios[i].profissao);
    }
}

int buscarUsuario(User *usuarios, int qntUserAtual) {
    char cpf[12];
    printf("Digite o CPF do usuário desejado: ");
    scanf("%s", cpf);
    int i;
    for (i = 0; i < qntUserAtual; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("Usuario %d | Cpf: %s\n", i + 1, usuarios[i].cpf);
            return i;
        }
    }
    return -1;
}

void imprimirUsuarioEspecifico(User *usuarios, int qntUserAtual) {
    int indUser = buscarUsuario(usuarios, qntUserAtual);
    if (indUser >= 0) {
        printf("====================== Listando usuário específico ======================\nUsuario %d* | Cpf: %s | Nome: %s | Data de nascimento: %s | Rua: %s | CEP: %s | ", (indUser + 1), usuarios[indUser].cpf, usuarios[indUser].nome, usuarios[indUser].nascimento, usuarios[indUser].rua, usuarios[indUser].cep);
        printf("Telefone(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuarios[indUser].telefones[j][0] != '\0') {
                printf("%s ", usuarios[indUser].telefones[j]);
            }
        }
        printf("] | Email(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuarios[indUser].emails[j][0] != '\0') {
                printf("%s ", usuarios[indUser].emails[j]);
            }
        }
        printf("] | Profissão: %s\n", usuarios[indUser].profissao);
    }
    else
        printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
}

void alterarInformacoesUsuario(User *usuarios, int qntUserAtual) {
    int indUser = buscarUsuario(usuarios, qntUserAtual);
    int op;
    if (indUser >= 0) {
        printf("====================== Alterando dados do usuário ======================\n1-Nome.\n2-Data de nascimento\n3-Rua.\n4-CEP.\n5-Telefone(s).\n6-Email(s).\n7-Profissão.\nEntre com o número do submenu desejado: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("Alterando nome: ");
            scanf("%s", usuarios[indUser].nome);
            break;
        case 2:
            printf("Alterando a data de nascimento (dia/mês/ano)\n");
            char data[11];
            int l = 0;
            while (l != 1) {
                printf("Data de nascimento (dd/mm/aaaa): ");
                scanf("%s", data);
                struct tm valiData = parse_date(data);
                if (valiData.tm_year >= 0) {
                    strftime(usuarios[indUser].nascimento, sizeof(usuarios[indUser].nascimento), "%d/%m/%Y", &valiData);
                    l = 1;
                }
            }
            break;
        case 3:
            printf("Alterando rua: ");
            scanf("%s", usuarios[indUser].rua);
            break;
        case 4:
            printf("CEP (xxxxx-xxx): ");
            scanf("%s", usuarios[indUser].cep);
            break;
        case 5:
            printf("Alterando telefone(s): ");
            int numTelefone = 0;
            int z = 1;
            while (z != 0 && numTelefone < 100) {
                scanf("%s", usuarios[indUser].telefones[numTelefone]);
                numTelefone++;
                char resp;
                printf("Deseja inserir mais um telefone (s/n)?: ");
                scanf(" %c", &resp);
                if (resp == 'n') {
                    z = 0;
                }
            }
            break;
        case 6:
            printf("Alterando email(s): ");
            int y = 1, numEmails = 0;
            while (y != 0 && numEmails < 100) {
                scanf("%s", usuarios[indUser].emails[numEmails]);
                numEmails++;
                char resp;
                printf("Deseja inserir mais um email (s/n)?: ");
                scanf(" %c", &resp);
                if (resp == 'n') {
                    y = 0;
                }
            }
            break;
        case 7:
            printf("Profissão: ");
            scanf("%s", usuarios[indUser].profissao);
            break;
        default:
            printf("Opção inválida. Tente novamente com uma opção disponível no submenu de atributos a serem alterados do usuário.");
            break;
        }
    } else {
        printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
    }
}

int usuarioPossuiEmprestimo(Loan *emprestimos, int qntEmprestimos, char *cpf) {
    for (int i = 0; i < qntEmprestimos; i++) {
        if (strcmp(emprestimos[i].codcpf, cpf) == 0) {
            return 1;
        }
    }
    return 0;
}

int excluirUsuario(User *usuarios, Loan *emprestimos, int *qntUserAtual, int qntLoanAtual){
    int indUser = buscarUsuario(usuarios, *qntUserAtual);
    if (indUser >= 0){
        if ((usuarioPossuiEmprestimo(emprestimos, qntLoanAtual, usuarios[indUser].cpf)) == 1){
            return 0;
        }
        else{
            int i, j, k;
            for (i = indUser; i < (*qntUserAtual - 1); i++){
                strcpy(usuarios[i].cpf, usuarios[i+1].cpf);
                strcpy(usuarios[i].nome, usuarios[i+1].nome);
                strcpy(usuarios[i].nascimento, usuarios[i+1].nascimento);
                strcpy(usuarios[i].rua, usuarios[i+1].rua);
                strcpy(usuarios[i].cep, usuarios[i+1].cep);
                for (j = 0; j < 100; j++)
                    strcpy(usuarios[i].telefones[j], usuarios[i+1].telefones[j]);
                for (k = 0; k < 100; k++)
                    strcpy(usuarios[i].emails[k], usuarios[i+1].emails[k]);
                strcpy(usuarios[i].profissao, usuarios[i+1].profissao);
            }
            (*qntUserAtual)--;
            return 1;
        }
    }
    else
        return 2;
}

//--------------------------------------------------------------------------------------------------------------------------------

int existeLivro(Book *livros, int qntBookAtual, char *isbn) {
    int i;
    for (i = 0; i < qntBookAtual; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0)
            return 1;
    }
    return 0;
}

/*int validarISBN(const char *isbn) {
    int i;
    for (i = 0; i < 13; i++) {
        if (!isdigit(isbn[i]) && isbn[i] != '\0') {
            return 0;
        }
    }
    return 1;
}*/

void incluirLivro(Book *livros, int *indBook){
    printf("====================== Incluindo Livro ======================\n");
    char isbn[13];
    int x = 1;
    while (x != 0) {
        printf("ISBN: ");
        scanf("%s", isbn);
        //int valido = validarISBN(isbn);
        int existeBook = existeLivro(livros, *indBook, isbn);
        //if (existeBook == 0 && valido) {
        if (existeBook == 0) {  //Apagar essa linha quando terminar os testes
            strcpy(livros[*indBook].isbn, isbn);
            x = 0;
            break;
        }
        /*else if (!valido)
            printf("ISBN inválido. Tente novamente.\n");*/
        else
            printf("Esse ISBN já existe na base de dados. Tente novamente.\n");
    }
    printf("Titulo: ");
    scanf("%s", livros[*indBook].titulo);
    printf("Genero: ");
    scanf("%s", livros[*indBook].genero);
    int numAutores = 0;
    int y = 1;
    while (y != 0) {
        printf("Autor(es): ");
        scanf("%s", livros[*indBook].autores[numAutores]);
        numAutores++;
        char resp;
        printf("Deseja inserir mais um autor (s/n)?: ");
        scanf(" %c", &resp);
        if (resp == 'n') {
            y = 0;
        }
    }
    livros[*indBook].qntautores[*indBook] = numAutores;
    printf("Numero de páginas: ");
    scanf("%d", &livros[*indBook].numPaginas);
    (*indBook)++;
    printf("Livro incluído com sucesso!\n");
}

void imprimirDadosDolivro(Book *livros, int qntBookAtual){
    printf("====================== Listar todos os Livros ======================\n");
    int i;
    for (i = 0; i < qntBookAtual; i++) {
        printf("Livro %d* | ISBN: %s | Titulo: %s | Genero: %s | ", (i + 1), livros[i].isbn, livros[i].titulo, livros[i].genero);
        printf("Autor(es): [ ");
        int j;
        for (j = 0; j < 100; j++) {
            if (livros[i].autores[j][0] != '\0')
                printf("%s ", livros[i].autores[j]);
        }
        printf("] | Número de páginas: %d\n", livros[i].numPaginas);
    }
}

int buscarlivros(Book *livros, int qntBookAtual){
    char isbn[17];
    printf("Digite o ISBN do livro desejado: ");
    scanf("%s", isbn);
    int i;
    for (i = 0; i < qntBookAtual; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0) {
            return i;
       }
    }
    return -1;
}

void imprimirLivroEspecifico(Book *livros, int qntBookAtual) {
    int indBook = buscarlivros(livros, qntBookAtual);
    if (indBook >= 0) {
        printf("====================== Listando livro específico ======================\nLivro %d* | ISBN: %s | Titulo: %s | Genero: %s | ", (indBook+1), livros[indBook].isbn, livros[indBook].titulo, livros[indBook].genero);
        printf("Autor(es): [ ");
        int j;
        for (j = 0; j < 100; j++) {
            if (livros[indBook].autores[j][0] != '\0') {
                printf("%s ", livros[indBook].autores[j]);
            }
        }
        printf("] | Número de páginas: %d\n", livros[indBook].numPaginas);
    }
    else
        printf("O livro indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
}

void alterarInformacoesLivro(Book *livros, int qntBookAtual){
   int indBook = buscarlivros(livros, qntBookAtual);
    int op;
    if (indBook >= 0) {
        printf("====================== Alterando dados do livro ======================\n1-Titulo.\n2-Gênero\n3-Autor(es).\n4-Número de páginas.\nEntre com o número do submenu desejado: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("Alterando título: ");
            scanf("%s", livros[indBook].titulo);
            break;
        case 2:
            printf("Alterando gênero: ");
            scanf("%s", livros[indBook].genero);
            break;
        case 3:
            printf("Alterando autor(es): ");
            int numAutores = 0;
            int y = 1;
            while (y != 0 && numAutores < 100) {
                scanf("%s", livros[indBook].autores[numAutores]);
                numAutores++;
                char resp;
                printf("Deseja inserir mais um autor (s/n)?: ");
                scanf(" %c", &resp);
                if (resp == 'n') {
                    y = 0;
                }
            }
            livros[indBook].qntautores[indBook] = numAutores;
            break;
        case 4:
            printf("Alterando número de páginas: ");
            scanf("%d", &livros[indBook].numPaginas);
            break;
        default:
            printf("Opção inválida. Tente novamente com uma opção disponível no submenu de atributos a serem alterados do usuário.");
            break;
        }
    } else {
        printf("O livro indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
    } 
}

int LivroPossuiEmprestimo(Loan *emprestimos, int qntEmprestimos, char *isbn) {
    for (int i = 0; i < qntEmprestimos; i++) {
        if (strcmp(emprestimos[i].codisbn, isbn) == 0) {
            return 1;
        }
    }
    return 0;
}

int excluirLivro(Book *livros, Loan *emprestimos, int *qntBookAtual, int qntLoanAtual){
    int indBook = buscarlivros(livros, *qntBookAtual);
    if (indBook >= 0){
        if (LivroPossuiEmprestimo(emprestimos, qntLoanAtual, livros[indBook].isbn) == 1){
            return 0;
        }
        else{
            int i, j;
            for (i = indBook; i < (*qntBookAtual - 1); i++){
                strcpy(livros[i].isbn, livros[i+1].isbn);
                strcpy(livros[i].titulo, livros[i+1].titulo);
                strcpy(livros[i].genero, livros[i+1].genero);
                for (j = 0; j < 100; j++)
                    strcpy(livros[i].autores[j], livros[i+1].autores[j]);
                livros[i].qntautores[i] = livros[i+1].qntautores[i+1];
                livros[i].numPaginas = livros[i+1].numPaginas;
            }
            (*qntBookAtual)--;
            return 1;
        }
    }
    else
        return 2;
}

//--------------------------------------------------------------------------------------------------------------------------------

int existeEmprestimo(Loan *emprestimos, int qntLoanAtual, char *cpf, char *isbn, char *retirada){
    int i;
    for (i = 0; i < qntLoanAtual; i++) {
        if (strcmp(emprestimos[i].codcpf, cpf) == 0 && strcmp(emprestimos[i].codisbn, isbn) == 0 && strcmp(emprestimos[i].retirada, retirada) == 0)
            return 1;
    }
    return 0;
}

void incluirEmprestimo(Loan *emprestimos, User *usuarios, Book *livros, int *indLoan, int indUser, int indBook) {
    char cpf[12];
    char isbn[13];
    char retirada[11];
    char devolucao[11];
    printf("CPF: ");
    scanf("%s", cpf);
    while (existeUsuario(usuarios, indUser, cpf) != 0) { // mudar paara 1 dps
        printf("Esse CPF não existe na base de dados. Tente novamente.\n");
        printf("CPF: ");
        scanf("%s", cpf);
    }
    printf("ISBN: ");
    scanf("%s", isbn);
    while (existeLivro(livros, indBook, isbn) != 0) { // mudar paara 1 dps
        printf("Esse ISBN não existe na base de dados. Tente novamente.\n");
        printf("ISBN: ");
        scanf("%s", isbn);
    }
    int l = 0;
    do {
        printf("Data de retirada (dd/mm/aaaa): ");
        scanf("%s", retirada);
        struct tm valiData = parse_date(retirada);
        if (valiData.tm_year >= 0) {
            char retiradaFormatada[11];
            strftime(retiradaFormatada, sizeof(retiradaFormatada), "%d/%m/%Y", &valiData);
            strcpy(retirada, retiradaFormatada);

            l = 1;
        } else {
            printf("Data inválida. Tente novamente.\n");
        }
    } while (l != 1);
    if (existeEmprestimo(emprestimos, *indLoan, cpf, isbn, retirada) == 0) {
        strcpy(emprestimos[*indLoan].codcpf, cpf);
        strcpy(emprestimos[*indLoan].codisbn, isbn);
        strcpy(emprestimos[*indLoan].retirada, retirada);
        int v = 0;
        do {
            printf("Data de devolução (dd/mm/aaaa): ");
            scanf("%s", devolucao);
            struct tm valiDataDev = parse_date(devolucao);

            struct tm retirada_tm = parse_date(emprestimos[*indLoan].retirada);
            time_t retirada_time = mktime(&retirada_tm);

            time_t devolucao_time = mktime(&valiDataDev);
            if ((valiDataDev.tm_year >= 0) && difftime(devolucao_time, retirada_time) >= 0) {
                char devolucao_formatada[11];
                strftime(devolucao_formatada, sizeof(devolucao_formatada), "%d/%m/%Y", &valiDataDev);
                strcpy(devolucao, devolucao_formatada);
                strcpy(emprestimos[*indLoan].devolucao, devolucao);
                v = 1;
            }
            else {
                printf("Data inválida ou menor que a data de retirada. Tente novamente.\n");
            }
        } while (v != 1);
        printf("Valor diário da multa por atraso: ");
        scanf("%f", &emprestimos[*indLoan].multa);
        (*indLoan)++;
        printf("Empréstimo efetivado com sucesso!\n");
    }
    else
        printf("Já existe um empréstimo com essas características.\n");
}

void imprimirDadosDoEmprestimo(Loan *emprestimos, int indLoan){
    int i = 0;
    for ( i = 0; i < indLoan; i++){
       printf("Empréstimo %d* | CPF: %s | ISBN: %s | Data de retirada: %s | Data de devolução: %s | Multa por atraso (diário): %.2f\n", (i+1),emprestimos[i].codcpf, emprestimos[i].codisbn, emprestimos[i].retirada, emprestimos[i].devolucao , emprestimos[i].multa);
    }
}

int buscarEmprestimo(Loan *emprestimos, int indLoan){
    char cpf[12];
    char isbn[13];
    char retirada[11];
    printf("Digite o CPF do usuário: ");
    scanf("%s", cpf);
    printf("Digite o ISBN do livro desejado: ");
    scanf("%s", isbn);
    printf("Digite a data de retirada do livros: ");
    scanf("%s", retirada);
    int i;
    for (i = 0; i < indLoan; i++) {
        if ((strcmp(emprestimos[i].codcpf, cpf) == 0) && (strcmp(emprestimos[i].codisbn, isbn) == 0) && (strcmp(emprestimos[i].retirada, retirada) == 0)) {
            printf("Empréstimo %d* | CPF: %s | ISBN: %s | Data de retirada: %s\n", (i+1),emprestimos[i].codcpf, emprestimos[i].codisbn, emprestimos[i].retirada);
            return i;
        }
    }
    printf("Esse empréstimo não podê ser encontrado. Tente novamente.\n");
    return -1;
}

void imprimirEmprestimoEspecifico(Loan *emprestimos, int qntLoanAtual) {
    int indloan = buscarEmprestimo(emprestimos, qntLoanAtual);
    if (indloan >= 0) {
        printf("====================== Listando empréstimo específico ======================\nEmpréstimo %d* | CPF: %s | ISBN: %s | Data de retirada: %s | Data de devolução: %s | Multa por atraso (diário): %.2f\n", (indloan+1),emprestimos[indloan].codcpf, emprestimos[indloan].codisbn, emprestimos[indloan].retirada, emprestimos[indloan].devolucao , emprestimos[indloan].multa);
    }
    else
        printf("O empréstimo indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
}

void alterarInformacoesEmprestimo(Loan *emprestimos, int qntLoanAtual){
    int indloan = buscarEmprestimo(emprestimos, qntLoanAtual);
    int op;
    int x = 0;
    char devolucao[11];
    if (indloan >= 0) {
        printf("====================== Alterando dados do empréstimo ======================\n1-Data de Devolução.\n2-Valor da multa de atraso diária.\nEntre com o número do submenu desejado: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
            do {
                printf("Alterando data de devolução: ");
                scanf("%s", devolucao);
                struct tm valiDataDev = parse_date(devolucao);
                struct tm retirada_tm = parse_date(emprestimos[indloan].retirada);
                time_t retirada_time = mktime(&retirada_tm);
                time_t devolucao_time = mktime(&valiDataDev);
                if ((valiDataDev.tm_year >= 0) && difftime(devolucao_time, retirada_time) >= 0) {
                    char devolucao_formatada[11];
                    strftime(devolucao_formatada, sizeof(devolucao_formatada), "%d/%m/%Y", &valiDataDev);
                    strcpy(devolucao, devolucao_formatada);
                    strcpy(emprestimos[indloan].devolucao, devolucao);
                    x = 1;
                }
                else
                    printf("Data inválida ou menor que a data de retirada. Tente novamente.\n");
            } while (x == 0);
            break;
        case 2:
            printf("Alterando valor da multa de atraso diária: ");
            scanf("%f", &emprestimos[indloan].multa);
            break;
        default:
            printf("Opção inválida. Tente novamente com uma opção disponível no submenu de atributos a serem alterados do usuário.");
            break;
        }
    }
    else 
        printf("O empréstimo indicado não podê ser encontrado. Verifique se o mesmo consta na base de dados atual.");
}

int excluirEmprestimo(Loan *emprestimos, int *qntLoanAtual){
    int indLoan = buscarEmprestimo(emprestimos, *qntLoanAtual);
    if (indLoan >= 0){
        int i;
        for (i = indLoan; i < (*qntLoanAtual - 1); i++){
            strcpy(emprestimos[i].codcpf, emprestimos[i+1].codcpf);
            strcpy(emprestimos[i].codisbn, emprestimos[i+1].codisbn);
            strcpy(emprestimos[i].retirada, emprestimos[i+1].retirada);
            strcpy(emprestimos[i].devolucao, emprestimos[i+1].devolucao);
            emprestimos[i].multa = emprestimos[i+1].multa;
        }
        (*qntLoanAtual)--;
        return 1;
    }
    else
        return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------

/*void listarPorIdade(User *usuarios, int indUser){
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    printf("Listando usuários por idade\nEntre com o valor da idade mínima: ");
    int idadeMin = 0, i;
    scanf("%d", &idadeMin);
    for (i = 0; i < indUser; i++){
        struct tm dataNascimento = parse_date(usuarios[i].nascimento);

        if (dataNascimento.tm_year < 0) {
            continue;  // Pular para o próximo usuário se a data de nascimento for inválida
        }
        int idade = now->tm_year + 1900 - (dataNascimento.tm_year + 1900);
        if ((now->tm_mon < dataNascimento.tm_mon) || (now->tm_mon == dataNascimento.tm_mon && now->tm_mday < dataNascimento.tm_mday)) {
            idade--;  // Ainda não fez aniversário este ano
        }
        if (idade >= idadeMin){
            printf("Usuario %d* | Cpf: %s | Nome: %s | Data de nascimento: %s | Rua: %s | CEP: %s | ", (i + 1), usuarios[i].cpf, usuarios[i].nome, usuarios[i].nascimento, usuarios[i].rua, usuarios[i].cep);
            printf("Telefone(s): [ ");
            int j;
            for (j = 0; j < 100; j++) {
                if (usuarios[i].telefones[j][0] != '\0') {
                    printf("%s ", usuarios[i].telefones[j]);
                }
            }
            printf("] | Email(s): [ ");
            int l;
            for (l = 0; l < 100; l++) {
                if (usuarios[i].emails[l][0] != '\0') {
                    printf("%s ", usuarios[i].emails[l]);
                }
            }
            printf("] | Profissão: %s\n", usuarios[i].profissao);
        }
    }
}

void listarPorQuantidadeDeAutores(Book *livros, int indBook) {
    printf("Listando livros por quantidade de autores\nEntre com a quantidade mínima de autores: ");
    int minAutores = 0, i;
    scanf("%d", &minAutores);
    for (i = 0; i < indBook; i++){
        if (livros[i].qntautores[i] >= minAutores){
            printf("Livro %d* | ISBN: %s | Titulo: %s | Genero: %s | ", (i + 1), livros[i].isbn, livros[i].titulo, livros[i].genero);
            printf("Autor(es): [ ");
            int j;
            for (j = 0; j < 100; j++) {
                if (livros[i].autores[j][0] != '\0')
                    printf("%s ", livros[i].autores[j]);
            }
            printf("] | Número de páginas: %d\n", livros[i].numPaginas);
        }   
    } 
}

void listarPorIntervaloDeEmprestimo(User *usuarios, Book *livros, Loan *emprestimos, int indLoan){

}*/

int main(){
    setlocale(LC_ALL, "Portuguese");
    User usuarios[255] = {0};
    Book livros[255] = {0};
    Loan emprestimos[255] = {0};

    int opMenu, opSubMenu, opRelat, qntUser = 0, qntBook = 0, qntLoan = 0;

    do {

        opMenu = MenuPrincipal();

        switch (opMenu) {
            case 1: {
                printf("Submenu de Usuários\n");
                int w = 1;
                do {
                    opSubMenu = Submenus();
                    switch (opSubMenu) {
                        case 1:
                            incluirUsuario(usuarios, &qntUser);
                            break;
                        case 2:
                            imprimirDadosDoUsuario(usuarios, qntUser);
                            break;
                        case 3:
                            imprimirUsuarioEspecifico(usuarios, qntUser);
                            break;
                        case 4:
                            alterarInformacoesUsuario(usuarios, qntUser);
                            break;
                        case 5: {
                            int excluirUse = excluirUsuario(usuarios, emprestimos, &qntUser, qntLoan);
                            if (excluirUse == 1)
                                printf("Usuário excluído com sucesso!\n");
                            else if (excluirUse == 2)
                                printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.\n");
                            else
                                printf("Esse usuário possui associações dentro dos registros de empréstimos. Logo, não pode ser excluído.\n");
                            break;
                        }
                        case 6:
                            w = 0;
                            break;
                        default:
                            printf("Opção inválida. Entre com um número de submenu existente.\n");
                            break;
                    }
                } while (w == 1);
                break;
            }
            case 2: {
                printf("Submenu de Livros\n");
                int x = 1;
                do {
                    opSubMenu = Submenus();
                    switch (opSubMenu) {
                        case 1:
                            incluirLivro(livros, &qntBook);
                            break;
                        case 2:
                            imprimirDadosDolivro(livros, qntBook);
                            break;
                        case 3:
                            imprimirLivroEspecifico(livros, qntBook);
                            break;
                        case 4:
                            printf("Alterando dados de um livro.\n");
                            alterarInformacoesLivro(livros, qntBook);
                            break;
                        case 5: {
                            int excluirLiv = excluirLivro(livros, emprestimos, &qntBook, qntLoan);
                            if (excluirLiv == 1)
                                printf("Livro excluído com sucesso!\n");
                            else if (excluirLiv == 2)
                                printf("O Livro indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.\n");
                            else
                                printf("Esse livro possui associações dentro dos registros de empréstimos. Logo, não pode ser excluído.\n");
                            break;
                        }
                        case 6:
                            x = 0;
                            break;
                        default:
                            printf("Opção inválida. Entre com um número de submenu existente.\n");
                            break;
                    }
                } while (x == 1);
                break;
            }
            case 3: {
                printf("Submenu de Empréstimos\n");
                int y = 1;
                do {
                    opSubMenu = Submenus();
                    switch (opSubMenu) {
                        case 1:
                            incluirEmprestimo(emprestimos, usuarios, livros, &qntLoan, qntUser, qntBook);
                            break;
                        case 2:
                            imprimirDadosDoEmprestimo(emprestimos, qntLoan);
                            break;
                        case 3:
                            imprimirEmprestimoEspecifico(emprestimos, qntLoan);
                            break;
                        case 4:
                            alterarInformacoesEmprestimo(emprestimos, qntLoan);
                            break;
                        case 5: {
                            int excluirEmp = excluirEmprestimo(emprestimos, &qntLoan);
                            if (excluirEmp == 1)
                                printf("Empréstimo excluído com sucesso!\n");
                            else
                                printf("O empréstimo indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.\n");
                            break;
                        }
                        case 6:
                            y = 0;
                            break;
                        default:
                            printf("Opção inválida. Entre com um número de submenu existente.\n");
                            break;
                    }
                } while (y == 1);
                break;
            }
            case 4: {
                printf("Submenu de Relatórios\n");
                int z = 1;
                do {
                    opRelat = SubmenuRelatorios();
                    switch (opRelat) {
                        case 1:
                            //listarPorIdade(usuarios, qntUser);
                            break;
                        case 2:
                            //listarPorQuantidadeDeAutores(livros, qntBook);
                            break;
                        case 3:
                            //listarPorIntervaloDeEmprestimo(usuarios, livros, emprestimos, qntLoan);
                            break;
                        case 4:
                            z = 0;
                            break;
                        default:
                            printf("Opção inválida. Entre com um número de submenu existente.\n");
                            break;
                    }
                } while (z == 1);
                break;
            }
            default:
                printf("Opção inválida. Entre com um número de submenu existente.\n");
                break;
        }
    } while (opMenu != 5);
    Linhas();
    printf("Desligando...");
    return 0;
}
