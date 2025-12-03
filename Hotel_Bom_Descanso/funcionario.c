#include <stdio.h>
#include <string.h>

typedef struct
{
    int codigo;
    char nome[50];
    char telefone[20];
    char cargo[30];
    float salario;
} Funcionario;

void cadastrarFuncionario(Funcionario funcionarios[], int *total)
{
    int codigo;

    printf("\n--- CADASTRO DE FUNCIONARIO ---\nCodigo: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < *total; i++)
    {
        if (funcionarios[i].codigo == codigo)
        {
            printf("ERRO: Ja existe um funcionario com esse codigo!\n");
            return;
        }
    }

    funcionarios[*total].codigo = codigo;

    printf("Nome: ");
    fgets(funcionarios[*total].nome, 50, stdin);
    funcionarios[*total].nome[strcspn(funcionarios[*total].nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(funcionarios[*total].telefone, 20, stdin);
    funcionarios[*total].telefone[strcspn(funcionarios[*total].telefone, "\n")] = '\0';

    printf("Cargo: ");
    fgets(funcionarios[*total].cargo, 30, stdin);
    funcionarios[*total].cargo[strcspn(funcionarios[*total].cargo, "\n")] = '\0';

    printf("Salario (R$): ");
    scanf("%f", &funcionarios[*total].salario);

    (*total)++;

    printf("Funcionario cadastrado!\n");
}

void listarFuncionarios(Funcionario funcionarios[], int total)
{
    printf("\n========== LISTA DE FUNCIONaRIOS ==========\n");
    if (total == 0)
    {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\nCodigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: R$ %.2f\n",
               funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone,
               funcionarios[i].cargo, funcionarios[i].salario);
    }
}
