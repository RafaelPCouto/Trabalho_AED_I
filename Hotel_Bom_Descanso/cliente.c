#include <stdio.h>
#include <string.h>

typedef struct
{
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;

void cadastrarCliente(Cliente clientes[], int *total)
{
    int codigo;
    printf("\n--- CADASTRO DE CLIENTE ---\nCodigo: ");
    scanf("%d", &codigo);
    getchar();

    // Verificar código duplicado
    for (int i = 0; i < *total; i++)
    {
        if (clientes[i].codigo == codigo)
        {
            printf("ERRO: Ja existe um cliente com esse codigo!\n");
            return;
        }
    }

    clientes[*total].codigo = codigo;

    printf("Nome: ");
    fgets(clientes[*total].nome, 50, stdin);
    clientes[*total].nome[strcspn(clientes[*total].nome, "\n")] = '\0';

    printf("Endereco: ");
    fgets(clientes[*total].endereco, 100, stdin);
    clientes[*total].endereco[strcspn(clientes[*total].endereco, "\n")] = '\0';

    printf("Telefone: ");
    fgets(clientes[*total].telefone, 20, stdin);
    clientes[*total].telefone[strcspn(clientes[*total].telefone, "\n")] = '\0';

    (*total)++;

    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes(Cliente clientes[], int total)
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
               clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
    }
}
