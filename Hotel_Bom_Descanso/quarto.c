#include <stdio.h>

typedef struct
{
    int numero;
    int capacidade;
    float diaria;
    int ocupado; // 0 = livre, 1 = ocupado
} Quarto;

void cadastrarQuarto(Quarto quartos[], int *total)
{
    int numero;

    printf("\n--- CADASTRO DE QUARTO ---\nNumero do quarto: ");
    scanf("%d", &numero);

    for (int i = 0; i < *total; i++)
    {
        if (quartos[i].numero == numero)
        {
            printf("ERRO: Ja existe um quarto com esse numero!\n");
            return;
        }
    }

    quartos[*total].numero = numero;

    printf("Capacidade: ");
    scanf("%d", &quartos[*total].capacidade);

    printf("Valor da diaria (R$): ");
    scanf("%f", &quartos[*total].diaria);

    quartos[*total].ocupado = 0;

    (*total)++;

    printf("Quarto cadastrado com sucesso!\n");
}

void listarQuartos(Quarto quartos[], int total)
{
    printf("\n========== LISTA DE QUARTOS ==========\n");

    if (total == 0)
    {
        printf("Nenhum quarto cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\nNumero: %d\nCapacidade: %d\nDiaria: R$ %.2f\nStatus: %s\n",
               quartos[i].numero, quartos[i].capacidade, quartos[i].diaria,
               quartos[i].ocupado ? "Ocupado" : "Desocupado");
    }
}
