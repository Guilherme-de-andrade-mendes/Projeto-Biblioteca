#include <stdio.h>
#include <locale.h>

typedef struct {
    int cpf;
    char nome[100];
    char nascimento[11];
    char rua[100];
    char cep[11];
    char telefones[100][15];
    char emails[100][50];
    char profissao[100];
} User;

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

void IncluirUsuario(User usuario[], int indUser) {
    printf("====================== Incluindo Usuário ======================\nCPF: ");
    scanf("%d", &usuario[indUser].cpf);
    printf("Nome: ");
    scanf("%s", usuario[indUser].nome);
    printf("Data de nascimento (dia/mês/ano): ");
    scanf("%s", usuario[indUser].nascimento);
    printf("Rua: ");
    scanf("%s", usuario[indUser].rua);
    printf("CEP (xxxxxxxx): ");
    scanf("%s", usuario[indUser].cep);

    int numTelefones = 0;
    while (1) {
        printf("Telefone (xxxxx-xxxx): ");
        scanf("%s", usuario[indUser].telefones[numTelefones]);
        numTelefones++;
        char resp;
        printf("Deseja inserir mais um telefone (s/n)?: ");
        scanf(" %c", &resp);  // Alterado para ler um único caractere.
        if (resp == 'n')
            break;
    }

    int numEmails = 0;
    while (1) {
        printf("Email: ");
        scanf("%s", usuario[indUser].emails[numEmails]);
        numEmails++;
        char resp;
        printf("Deseja inserir mais um email (s/n)?: ");
        scanf(" %c", &resp);  // Alterado para ler um único caractere.
        if (resp == 'n')
            break;
    }

    printf("Profissão: ");
    scanf("%s", usuario[indUser].profissao);
}

void imprimirDadosDoUsuario(User usuario[], int qntUserAtual) {
    printf("====================== Listar todos os usuários ======================\n");
    for (int i = 0; i < qntUserAtual; i++) {
        printf("Usuario %d* | Cpf: %d | Nome: %s | Rua: %s | CEP: %s | ", (i + 1), usuario[i].cpf, usuario[i].nome, usuario[i].rua, usuario[i].cep);
        printf("Telefone(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuario[i].telefones[j][0] != '\0') {
                printf("%s ", usuario[i].telefones[j]);
            }
        }
        printf("] | Email(s): [ ");
        for (int j = 0; j < 100; j++) {
            if (usuario[i].emails[j][0] != '\0') {
                printf("%s ", usuario[i].emails[j]);
            }
        }
        printf("] | Profissão: %s\n", usuario[i].profissao);
    }
}

int buscarUsuario(User usuario[], int qntUserAtual) {
    int cpf;
    printf("Digite o CPF do usuário desejado: ");
    scanf("%d", &cpf);
    for (int i = 0; i < qntUserAtual; i++) {
        if (usuario[i].cpf == cpf)
            return i;
    }
    printf("O CPF digitado não consta na base de dados atual. Tente novamente com um CPF válido.");
    return -1;
}

void imprimirUsuarioEspecifico(User usuario[], int qntUserAtual) {
    int indUser = buscarUsuario(usuario, qntUserAtual);
    if (indUser >= 0) {
        printf("====================== Listar todos os usuários ======================\nUsuario %d* | Cpf: %d | Nome: %s | Rua: %s | CEP: %s | ", (indUser + 1), usuario[indUser].cpf, usuario[indUser].nome, usuario[indUser].rua, usuario[indUser].cep);
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
    } else {
        printf("O usuário indicado não pode ser encontrado. Verifique se o mesmo consta na base de dados atual.");
    }
}

void alterarInformacoesUsuario(User usuario[], int qntUserAtual) {
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
            break;
        case 6:
            printf("Alterando email(s): ");
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

int main() {
    setlocale(LC_ALL, "portuguese");
    User usuarios[255] = {0};
    int opMenu, opSubMenu, opRelat, qntUser = 0;
    do {
        opMenu = MenuPrincipal();
        if (opMenu == 5)
            break;
        switch (opMenu) {
        case 1:
            printf("Submenu de Usuários\n");
            while (1) {
                opSubMenu = Submenus();
                if (opSubMenu == 1) {
                    IncluirUsuario(usuarios, qntUser);
                    qntUser++;
                } else if (opSubMenu == 2)
                    imprimirDadosDoUsuario(usuarios, qntUser);
                else if (opSubMenu == 3)
                    imprimirUsuarioEspecifico(usuarios, qntUser);
                else if (opSubMenu == 4)
                    alterarInformacoesUsuario(usuarios, qntUser);
                else if (opSubMenu == 5)
                    printf("Excluindo usuário.\n");
                else if (opSubMenu == 6)
                    break;
                else
                    printf("Opção inválida. Entre com um número de submenu existente.\n");
            }
            break;
        case 2:
            printf("Submenu de Livros\n");
            while (1) {
                opSubMenu = Submenus();
                if (opSubMenu == 1)
                    printf("Incluindo livro.\n");
                else if (opSubMenu == 2)
                    printf("Listar todos os livros.\n");
                else if (opSubMenu == 3)
                    printf("Listar um livro específico.\n");
                else if (opSubMenu == 4)
                    printf("Alterando dados de um livro.\n");
                else if (opSubMenu == 5)
                    printf("Excluindo livro.\n");
                else if (opSubMenu == 6)
                    break;
                else
                    printf("Opção inválida. Entre com um número de submenu existente.\n");
            }
            break;
        case 3:
            printf("Submenu de Empréstimos\n");
            while (1) {
                opSubMenu = Submenus();
                if (opSubMenu == 1)
                    printf("Incluindo empréstimo.\n");
                else if (opSubMenu == 2)
                    printf("Listar todos os empréstimos.\n");
                else if (opSubMenu == 3)
                    printf("Listar um empréstimo específico.\n");
                else if (opSubMenu == 4)
                    printf("Alterando dados de um empréstimo.\n");
                else if (opSubMenu == 5)
                    printf("Excluindo empréstimo.\n");
                else if (opSubMenu == 6)
                    break;
                else
                    printf("Opção inválida. Entre com um número de submenu existente.\n");
            }
            break;
        case 4:
            printf("Submenu de Relatórios\n");
            while (1) {
                opRelat = SubmenuRelatorios();
                if (opRelat == 1)
                    printf("Mostrar usuários por idade.\n");
                else if (opRelat == 2)
                    printf("Mostrar livros por autores.\n");
                else if (opRelat == 3)
                    printf("Mostrar dados por empréstimo.\n");
                else if (opRelat == 4)
                    break;
                else
                    printf("Opção inválida. Entre com um número de submenu existente.\n");
            }
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
