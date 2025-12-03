
/*
 * Programa: Hotel Bom Descanso
 * Conceito: Menu principal que integra os módulos de Cliente, Funcionário, Quarto e Estadia.
 * Destaques:
 *  - Leitura de opção do menu com scanf e validação.
 */

#include <stdio.h>

#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

#define MAX 100

/* Função auxiliar simples para "limpar" resto da linha do stdin.
    Poderia ser o fflush
 */
void limpaLinha(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* nada */ }
}

int main(void)
{
    /* Vetores das entidades.
     */
    struct Cliente clientes[MAX];
    struct Funcionario funcionarios[MAX];
    struct Quarto quartos[MAX];
    struct Estadia estadias[MAX];

    int totalClientes = 0;
    int totalFunc     = 0;
    int totalQuartos  = 0;
    int totalEstadias = 0;

    int opc = -1;

    do {
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
        printf("0 - Sair\n");
        printf("Escolha: ");

        /* Leitura da opção.
         */
        if (scanf(" %d", &opc) != 1) {
            printf("Opcao invalida (nao numerica).\n");
            limpaLinha();      /* descarta o restante da linha inválida */
            opc = -1;          /* força continuar no menu */
            continue;
        }
        limpaLinha();          /* consome a quebra de linha após o número */

        switch (opc) {
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
                cadastrarEstadia(estadias, &totalEstadias,
                                 clientes, totalClientes,
                                 quartos, totalQuartos);
                break;
            case 8:
                listarEstadias(estadias, totalEstadias);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 0);

    return 0;
}
