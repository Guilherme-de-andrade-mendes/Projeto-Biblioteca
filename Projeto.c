#include <stdio.h>
#include <locale.h>

void Linhas(){
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

int main() {
    int opcao_Menu;
    int opcao_Submenu;
    int opcao_Relatorio;
    setlocale(LC_ALL, "portuguese");
    do {
        opcao_Menu = MenuPrincipal();
        if (opcao_Menu == 5)
            break;
        switch (opcao_Menu) {
            case 1:
                printf("Submenu de Usuários\n");
                while (1) {
                    opcao_Submenu = Submenus();
                    if (opcao_Submenu == 1)
                        printf("Incluindo usuário.\n");
                    else if (opcao_Submenu == 2)
                        printf("Listar todos os usuários.\n");
                    else if (opcao_Submenu == 3)
                        printf("Listar um usuário específico.\n");
                    else if (opcao_Submenu == 4)
                        printf("Alterando dados do usuário.\n");
                    else if (opcao_Submenu == 5)
                        printf("Excluindo usuário.\n");
                    else if (opcao_Submenu == 6)
                        break;
                    else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                }
                break;
            case 2:
                printf("Submenu de Livros\n");
                while (1) {
                    opcao_Submenu = Submenus();
                    if (opcao_Submenu == 1)
                        printf("Incluindo livro.\n");
                    else if (opcao_Submenu == 2)
                        printf("Listar todos os livros.\n");
                    else if (opcao_Submenu == 3)
                        printf("Listar um livro específico.\n");
                    else if (opcao_Submenu == 4)
                        printf("Alterando dados de um livro.\n");
                    else if (opcao_Submenu == 5)
                        printf("Excluindo livro.\n");
                    else if (opcao_Submenu == 6)
                        break;
                    else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                }
                break;
            case 3:
                printf("Submenu de Empréstimos\n");
                while (1) {
                    opcao_Submenu = Submenus();
                    if (opcao_Submenu == 1)
                        printf("Incluindo empréstimo.\n");
                    else if (opcao_Submenu == 2)
                        printf("Listar todos os empréstimos.\n");
                    else if (opcao_Submenu == 3)
                        printf("Listar um empréstimo específico.\n");
                    else if (opcao_Submenu == 4)
                        printf("Alterando dados de um empréstimo.\n");
                    else if (opcao_Submenu == 5)
                        printf("Excluindo empréstimo.\n");
                    else if (opcao_Submenu == 6)
                        break;
                    else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                }
                break;
            case 4:
                printf("Submenu de Relatório\n");
                while (1) {
                    opcao_Relatorio = SubmenuRelatorios();
                    if (opcao_Relatorio == 1)
                        printf("Mostrar usuários por idade.\n");
                    else if (opcao_Relatorio == 2)
                        printf("Mostrar livros por autores.\n");
                    else if (opcao_Relatorio == 3)
                        printf("Mostrar dados por empréstimo.\n");
                    else if (opcao_Relatorio == 4)
                        break;
                    else
                        printf("Opção inválida. Entre com um número de submenu existente.\n");
                }
                break;
            default:
                printf("Opção inválida. Entre com um número de submenu existente.\n");
                break;
        }
    } while (opcao_Menu != 5);
    Linhas();
    printf("Obrigado por utilizar nosso sistema. Volte sempre!\n");
    return 0;
}