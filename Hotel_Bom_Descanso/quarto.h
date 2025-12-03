
/*
 * Módulo: Quarto
 * Objetivo: Cadastrar e listar quartos do hotel.
 * Padrão adotado:
 *  - "struct Quarto" (sem typedef)
 *  - scanf com validação básica e limpeza de linha quando necessário
 */

#include <stdio.h>

/* Estrutura do quarto. Use "struct Quarto" ao declarar variáveis/parâmetros. */
struct Quarto {
    int   numero;      /* número do quarto (único) */
    int   capacidade;  /* quantidade máxima de hóspedes */
    float diaria;      /* valor da diária */
    int   ocupado;     /* 0 = desocupado, 1 = ocupado */
};

/* Auxiliar simples para descartar o restante da linha (inclusive '\n') */
static void limpaLinhaQuarto(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* nada */ }
}

/*
 * Função: cadastrarQuarto
 * Parâmetros:
 *   - quartos: vetor de quartos
 *   - total: ponteiro para quantidade atual de quartos cadastrados
 * Comportamento:
 *   - Lê número, capacidade e diária
 *   - Valida duplicidade de número do quarto
 *   - Marca como desocupado inicialmente (ocupado = 0)
 */
void cadastrarQuarto(struct Quarto quartos[], int *total)
{
    int numero;

    printf("\n--- CADASTRO DE QUARTO ---\nNumero do quarto: ");
    if (scanf(" %d", &numero) != 1) {
        printf("ERRO: Numero invalido.\n");
        limpaLinhaQuarto();
        return;
    }

    /* Verificar número duplicado */
    for (int i = 0; i < *total; i++) {
        if (quartos[i].numero == numero) {
            printf("ERRO: Ja existe um quarto com esse numero!\n");
            return;
        }
    }

    quartos[*total].numero = numero;

    printf("Capacidade: ");
    if (scanf(" %d", &quartos[*total].capacidade) != 1 || quartos[*total].capacidade <= 0) {
        printf("ERRO: Capacidade invalida.\n");
        limpaLinhaQuarto();
        return;
    }

    printf("Valor da diaria (R$): ");
    if (scanf(" %f", &quartos[*total].diaria) != 1 || quartos[*total].diaria < 0.0f) {
        printf("ERRO: Valor de diaria invalido.\n");
        limpaLinhaQuarto();
        return;
    }

    /* Quarto inicia como desocupado */
    quartos[*total].ocupado = 0;

    (*total)++;
    printf("Quarto cadastrado com sucesso!\n");
}

/*
 * Função: listarQuartos
 * Parâmetros:
 *   - quartos: vetor de quartos
 *   - total: quantidade atual cadastrada
 * Comportamento:
 *   - Imprime todos os quartos com seus dados e status
 */
void listarQuartos(struct Quarto quartos[], int total)
{
    printf("\n========== LISTA DE QUARTOS ==========\n");

    if (total == 0) {
        printf("Nenhum quarto cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nNumero: %d\nCapacidade: %d\nDiaria: R$ %.2f\nStatus: %s\n",
               quartos[i].numero,
               quartos[i].capacidade,
               quartos[i].diaria,
               quartos[i].ocupado ? "Ocupado" : "Desocupado");
    }
}
