
/*
 * Módulo: Cliente
 * Objetivo: Cadastrar e listar clientes do Hotel Descanso Garantido.
 *
 * Observações:
 * - Valida código duplicado.
 * - Uso de " %d" e " %[^\n]" para consumir quebras de linha pendentes.
 */

#include <stdio.h>
#include <string.h>

/*
 * Estrutura que representa um cliente.
 */

struct Cliente
{
    int codigo;
    char nome[50];      /* 49 caracteres + '\0' */
    char endereco[100]; /* 99 caracteres + '\0' */
    char telefone[20];  /* 19 caracteres + '\0' */
};

/*
 * Função: cadastrarCliente
 * Parâmetros:
 *   - clientes: vetor de clientes (já alocado)
 *   - total: ponteiro para a quantidade atual de clientes no vetor
 * Comportamento:
 *   - Lê dados do novo cliente com scanf
 *   - Garante que não há código duplicado
 *   - Incrementa *total ao final do cadastro
 */
void cadastrarCliente(struct Cliente clientes[], int *total)
{
    int codigo;

    printf("\n--- CADASTRO DE CLIENTE ---\nCodigo: ");
    /* " %d" consome eventuais espaços/novas linhas anteriores */
    if (scanf(" %d", &codigo) != 1)
    {
        /* leitura falhou (não-inteiro) */
        printf("ERRO: Codigo invalido.\n");
        /* Limpa buffer simples: consome até a próxima linha */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        { /* nada */
        }
        return;
    }

    /* Verificar código duplicado */
    for (int i = 0; i < *total; i++)
    {
        if (clientes[i].codigo == codigo)
        {
            printf("ERRO: Ja existe um cliente com esse codigo!\n");
            return;
        }
    }

    clientes[*total].codigo = codigo;

    /*
     * - Larguras: 49, 99, 19 para evitar overflow e garantir '\0'.
     */

    printf("Nome: ");
    if (scanf(" %49[^\n]", clientes[*total].nome) != 1)
    {
        printf("ERRO: Nome invalido.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        return;
    }

    printf("Endereco: ");
    if (scanf(" %99[^\n]", clientes[*total].endereco) != 1)
    {
        printf("ERRO: Endereco invalido.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        return;
    }

    printf("Telefone: ");
    if (scanf(" %19[^\n]", clientes[*total].telefone) != 1)
    {
        printf("ERRO: Telefone invalido.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        { /* nada */
        }
        return;
    }

    /* Incrementa total de clientes cadastrados */
    (*total)++;

    printf("Cliente cadastrado com sucesso!\n");
}

/*
 * Função: listarClientes
 * Parâmetros:
 *   - clientes: vetor de clientes
 *   - total: quantidade atual de clientes cadastrados
 * Comportamento:
 *   - Imprime todos os clientes.
 */
void listarClientes(struct Cliente clientes[], int total)
{
    printf("\n========== LISTA DE CLIENTES ==========\n");
    if (total == 0)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\nCodigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
               clientes[i].codigo,
               clientes[i].nome,
               clientes[i].endereco,
               clientes[i].telefone);
    }
}
