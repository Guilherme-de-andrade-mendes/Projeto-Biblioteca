#include <stdio.h>
#include <locale.h>
#include <string.h>

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
    char isbn[16];
    char titulo[100];
    char genero[100];
    char autores[100][10];
    int numPaginas;
} Book;

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

int existeUsuario(User *usuario, int qntUserAtual, char *cpf) {
    for (int i = 0; i < qntUserAtual; i++) {
        if (strcmp(usuario[i].cpf, cpf) == 0) {
            return 1;
        }
    }
    return 0;
}

void incluirUsuario(User *usuario, int indUser) {
    printf("====================== Incluindo Usuário ======================\n");
    char cpf[12];
    int x = 1;
    while (x != 0) {
        printf("CPF: ");
        scanf("%s", cpf);
        int existeUser = existeUsuario(usuario, indUser, cpf);
        if (existeUser == 0){
            strcpy(usuario[indUser].cpf, cpf);
            x = 0;
            break;
        }
        printf("CPF já existe na base de dados. Tente novamente.\n");
    }
    printf("Nome: ");
    scanf("%s", usuario[indUser].nome);
    printf("Data de nascimento (dia/mês/ano): ");
    scanf("%s", usuario[indUser].nascimento);
    printf("Rua: ");
    scanf("%s", usuario[indUser].rua);
    printf("CEP (xxxxxxxx): ");
    scanf("%s", usuario[indUser].cep);

    int numTelefones = 0, y = 1;
    while (y != 0) {
        printf("Telefone (xxxxx-xxxx): ");
        scanf("%s", usuario[indUser].telefones[numTelefones]);
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
        scanf("%s", usuario[indUser].emails[numEmails]);
        numEmails++;
        char resp;
        printf("Deseja inserir mais um email (s/n)?: ");
        scanf(" %c", &resp);
        if (resp == 'n') {
            z = 0;
        }
    }
    printf("Profissão: ");
    scanf("%s", usuario[indUser].profissao);
}

void imprimirDadosDoUsuario(User *usuario, int qntUserAtual) {
    printf("====================== Listar todos os usuários ======================\n");
    int i;
    for (i = 0; i < qntUserAtual; i++) {
        printf("Usuario %d* | Cpf: %s | Nome: %s | Data de nascimento: %s | Rua: %s | CEP: %s | ", (i + 1), usuario[i].cpf, usuario[i].nome, usuario[i].nascimento, usuario[i].rua, usuario[i].cep);
        printf("Telefone(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuario[i].telefones[j][0] != '\0') {
                printf("%s ", usuario[i].telefones[j]);
            }
        }
        printf("] | Email(s): [ ");
        int j;
        for (j = 0; j < 100; j++) {
            if (usuario[i].emails[j][0] != '\0') {
                printf("%s ", usuario[i].emails[j]);
            }
        }
        printf("] | Profissão: %s\n", usuario[i].profissao);
    }
}

int buscarUsuario(User *usuario, int qntUserAtual) {
    char cpf[12];
    printf("Digite o CPF do usuário desejado: ");
    scanf("%s", cpf);
    int i;
    for (i = 0; i < qntUserAtual; i++) {
        if (strcmp(usuario[i].cpf, cpf) == 0) {
            printf("Usuario %d | Cpf: %s\n", i + 1, usuario[i].cpf);
            return i;
        }
    }
    printf("Esse usuario nao pode ser encontrado. Tente novamente.\n");
    return -1;
}

void imprimirUsuarioEspecifico(User *usuario, int qntUserAtual) {
    int indUser = buscarUsuario(usuario, qntUserAtual);
    if (indUser >= 0) {
        printf("====================== Listando usuário específico ======================\nUsuario %d* | Cpf: %s | Nome: %s | Data de nascimento: %s | Rua: %s | CEP: %s | ", (indUser + 1), usuario[indUser].cpf, usuario[indUser].nome, usuario[indUser].nascimento, usuario[indUser].rua, usuario[indUser].cep);
        printf("Telefone(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuario[indUser].telefones[j][0] != '\0') {
                printf("%s ", usuario[indUser].telefones[j]);
            }
        }
        printf("] | Email(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuario[indUser].emails[j][0] != '\0') {
                printf("%s ", usuario[indUser].emails[j]);
            }
        }
        printf("] | Profissão: %s\n", usuario[indUser].profissao);
    }
    else
        printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
}

void alterarInformacoesUsuario(User *usuario, int qntUserAtual) {
    int indUser = buscarUsuario(usuario, qntUserAtual);
    int op;
    if (indUser >= 0) {
        printf("====================== Alterando dados do usuário ======================\n1-Nome.\n2-Data de nascimento\n3-Rua.\n4-CEP.\n5-Telefone(s).\n6-Email(s).\n7-Profissão.\nEntre com o número do submenu desejado: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("Alterando nome: ");
            scanf("%s", usuario[indUser].nome);
            break;
        case 2:
            printf("Alterando a data de nascimento (dia/mês/ano): ");
            scanf("%s", usuario[indUser].nascimento);
            break;
        case 3:
            printf("Alterando rua: ");
            scanf("%s", usuario[indUser].rua);
            break;
        case 4:
            printf("CEP (xxxxx-xxx): ");
            scanf("%s", usuario[indUser].cep);
            break;
        case 5:
            printf("Alterando telefone(s): ");
            scanf("%s", usuario[indUser].telefones);
            break;
        case 6:
            printf("Alterando email(s): ");
            scanf("%s", usuario[indUser].emails);
            break;
        case 7:
            printf("Profissão: ");
            scanf("%s", usuario[indUser].profissao);
            break;
        default:
            printf("Opção inválida. Tente novamente com uma opção disponível no submenu de atributos a serem alterados do usuário.");
            break;
        }
    } else {
        printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
    }
}

int excluirUsuario(User *usuario, int qntUserAtual){
    int indUser = buscarUsuario(usuario, qntUserAtual);
    if (indUser >= 0){
        printf("\nUsuario excluído com sucesso!");
        int i;
        for (i = indUser; i < (qntUserAtual - 1); i++){
            strcpy(usuario[i].cpf, usuario[i+1].cpf);
            strcpy(usuario[i].nome, usuario[i+1].nome);
            strcpy(usuario[i].nascimento, usuario[i+1].nascimento);
            strcpy(usuario[i].rua, usuario[i+1].rua);
            strcpy(usuario[i].cep, usuario[i+1].cep);
            strcpy(usuario[i].telefones, usuario[i+1].telefones);
            strcpy(usuario[i].emails, usuario[i+1].emails);
            strcpy(usuario[i].profissao, usuario[i+1].profissao);
        }
        return 1;
    }
    else
        return 0;
}

int existeLivro(Book *livros, int qntBookAtual, char *isbn) {
    int i;
    for (i = 0; i < qntBookAtual; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0)
            return 1;
    }
    return 0;
}

void incluirLivro(Book *livros, int indBook){
    printf("====================== Incluindo Livro ======================\n");
    char isbn[16];
    int x = 1;
    while (x != 0) {
        printf("ISBN: ");
        scanf("%s", isbn);
        int existeBook = existeLivro(livros, indBook, isbn);
        if (existeBook == 0){
            strcpy(livros[indBook].isbn, isbn);
            x = 0;
            break;
        }
        printf("Esse isbn já existe na base de dados. Tente novamente.\n");
    }
    printf("Titulo: ");
    scanf("%s", livros[indBook].titulo);
    printf("Genero: ");
    scanf("%s", livros[indBook].genero);
    int numAutores = 0;
    int y = 1;
    while (y != 0) {
        printf("Autor(es): ");
        scanf("%s", livros[indBook].autores[numAutores]);
        numAutores++;
        char resp;
        printf("Deseja inserir mais um autor (s/n)?: ");
        scanf(" %c", &resp);
        if (resp == 'n') {
            y = 0;
        }
    }
    printf("Numero de páginas: ");
    scanf("%d", &livros[indBook].numPaginas);
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
    char isbn[16];
    printf("Digite o ISBN do livro desejado: ");
    scanf("%s", isbn);
    int i;
    for (i = 0; i < qntBookAtual; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0) {
            printf("Livro %d* | ISBN: %s\n", i + 1, livros[i].isbn);
            return i;
        }
    }
    printf("Esse livro nao pode ser encontrado. Tente novamente.\n");
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

int main(){
    setlocale(LC_ALL, "portuguese");
    User usuarios[255] = {0};
    Book livros[255] = {0};
    int opMenu, opSubMenu, opRelat, qntUser = 0, qntBook = 0;

    do {
        opMenu = MenuPrincipal();
        if (opMenu == 5)
            break;
        switch (opMenu) {
            case 1:
                printf("Submenu de Usuários\n");
                int w = 1;
                do {
                    opSubMenu = Submenus();
                    if (opSubMenu == 1) {
                        incluirUsuario(usuarios, qntUser);
                        qntUser++;
                        printf("Usuario incluído com sucesso!\n");
                    } else if (opSubMenu == 2) {
                        imprimirDadosDoUsuario(usuarios, qntUser);
                    } else if (opSubMenu == 3) {
                        imprimirUsuarioEspecifico(usuarios, qntUser);
                    } else if (opSubMenu == 4) {
                        alterarInformacoesUsuario(usuarios, qntUser);
                    } else if (opSubMenu == 5) {
                        int excluir = excluirUsuario(usuarios, qntUser);
                        if (excluir == 1) {
                            qntUser--;
                            printf("Usuário excluído com sucesso!\n");
                        } else {
                            printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.\n");
                        }
                    } else if (opSubMenu == 6) {
                        w = 0;
                    } else {
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                    }
                } while (w == 1);
                break;
            case 2:
                printf("Submenu de Livros\n");
                int x = 1;
                do {
                    opSubMenu = Submenus();
                    if (opSubMenu == 1) {
                        incluirLivro(livros, qntBook);
                        qntBook++;
                        printf("Livro incluído com sucesso!\n");
                    } else if (opSubMenu == 2) {
                        imprimirDadosDolivro(livros, qntBook);
                    } else if (opSubMenu == 3) {
                        imprimirLivroEspecifico(livros, qntBook);
                    } else if (opSubMenu == 4) {
                        printf("Alterando dados de um livro.\n");
                    } else if (opSubMenu == 5) {
                        printf("Excluindo livro.\n");
                    } else if (opSubMenu == 6) {
                        x = 0;
                    } else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                } while (x == 1);
                break;
            case 3:
                printf("Submenu de Empréstimos\n");
                int y = 1;
                do {
                    opSubMenu = Submenus();
                    if (opSubMenu == 1) {
                        printf("Incluindo empréstimo.\n");
                    } else if (opSubMenu == 2) {
                        printf("Listar todos os empréstimos.\n");
                    } else if (opSubMenu == 3) {
                        printf("Listar um empréstimo específico.\n");
                    } else if (opSubMenu == 4) {
                        printf("Alterando dados de um empréstimo.\n");
                    } else if (opSubMenu == 5) {
                        printf("Excluindo empréstimo.\n");
                    } else if (opSubMenu == 6) {
                        y = 0;
                    } else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                } while (y == 1);
                break;
            case 4:
                printf("Submenu de Relatórios\n");
                int z = 1;
                do {
                    opRelat = SubmenuRelatorios();
                    if (opRelat == 1) {
                        printf("Mostrar usuários por idade.\n");
                    } else if (opRelat == 2) {
                        printf("Mostrar livros por autores.\n");
                    } else if (opRelat == 3) {
                        printf("Mostrar dados por empréstimo.\n");
                    } else if (opRelat == 4) {
                        z = 0;
                    } else 
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                } while (z == 1);
                break;
            default:
                printf("Opção inválida. Entre com um número de submenu existente.\n");
                break;
        }
    } while (opMenu != 5);

    Linhas();
    printf("Obrigado por utilizar nosso sistema. Volte sempre!\n");
    return 0;
}