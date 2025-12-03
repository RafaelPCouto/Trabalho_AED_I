#include <stdio.h>
#include "cliente.c"
#include "funcionario.c"
#include "quarto.c"
#include "estadia.c"

#define MAX 100

int main()
{
    Cliente clientes[MAX];
    Funcionario funcionarios[MAX];
    Quarto quartos[MAX];
    Estadia estadias[MAX];

    int totalClientes = 0, totalFunc = 0, totalQuartos = 0, totalEstadias = 0;
    int opc;

    do
    {
        printf("\n====================================\n");
        printf("         HOTEL BOM DESCANSO\n");
        printf("====================================\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Cadastrar Funcionario\n");
        printf("4 - Listar Funcionarios\n");
        printf("5 - Cadastrar Quarto\n");
        printf("6 - Listar Quartos\n");
        printf("7 - Registrar Estadia\n");
        printf("8 - Listar Estadias\n");
        printf("0 - Sair\nEscolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            cadastrarCliente(clientes, &totalClientes);
            break;
        case 2:
            listarClientes(clientes, totalClientes);
            break;
        case 3:
            cadastrarFuncionario(funcionarios, &totalFunc);
            break;
        case 4:
            listarFuncionarios(funcionarios, totalFunc);
            break;
        case 5:
            cadastrarQuarto(quartos, &totalQuartos);
            break;
        case 6:
            listarQuartos(quartos, totalQuartos);
            break;
        case 7:
            cadastrarEstadia(estadias, &totalEstadias, clientes, totalClientes, quartos, totalQuartos);
            break;
        case 8:
            listarEstadias(estadias, totalEstadias);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opçao invalida!\n");
        }

    } while (opc != 0);

    return 0;
}
