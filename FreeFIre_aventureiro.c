#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ===============================
// STRUCT DOS ITENS
// ===============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ===============================
// STRUCT DA LISTA ENCADEADA
// ===============================
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ===============================
// VARIÁVEIS GLOBAIS
// ===============================

// Vetor
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Lista Encadeada
No* mochilaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===============================
// FUNÇÕES AUXILIARES
// ===============================

// Limpa buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// ===============================
// FUNÇÕES DO VETOR
// ===============================

// Inserir item no vetor
void inserirItemVetor() {

    if (totalItensVetor >= MAX_ITENS) {
        printf("\nMochila do vetor cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", mochilaVetor[totalItensVetor].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochilaVetor[totalItensVetor].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);

    totalItensVetor++;

    printf("\nItem inserido no vetor com sucesso!\n");
}

// Listar itens do vetor
void listarItensVetor() {

    int i;

    printf("\n======= MOCHILA VETOR =======\n");

    if (totalItensVetor == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("%-20s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");

    for (i = 0; i < totalItensVetor; i++) {

        printf("%-20s %-15s %-10d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

// Remover item do vetor
void removerItemVetor() {

    char nomeBusca[30];
    int i, j;
    int encontrado = 0;

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (i = 0; i < totalItensVetor; i++) {

        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {

            encontrado = 1;

            for (j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }

            totalItensVetor--;

            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado.\n");
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor() {

    char nomeBusca[30];
    int i;
    int encontrado = 0;

    comparacoesSequencial = 0;

    printf("\nDigite o nome do item para busca sequencial: ");
    scanf(" %[^\n]", nomeBusca);

    for (i = 0; i < totalItensVetor; i++) {

        comparacoesSequencial++;

        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {

            encontrado = 1;

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochilaVetor[i].nome);
            printf("Tipo: %s\n", mochilaVetor[i].tipo);
            printf("Quantidade: %d\n", mochilaVetor[i].quantidade);

            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado.\n");
    }

    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor() {

    int i, j;
    Item temp;

    for (i = 0; i < totalItensVetor - 1; i++) {

        for (j = 0; j < totalItensVetor - i - 1; j++) {

            if (strcmp(mochilaVetor[j].nome,
                       mochilaVetor[j + 1].nome) > 0) {

                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    printf("\nVetor ordenado com sucesso!\n");
}

// Busca binária no vetor
void buscarBinariaVetor() {

    char nomeBusca[30];

    int inicio = 0;
    int fim = totalItensVetor - 1;
    int meio;

    comparacoesBinaria = 0;

    printf("\nDigite o nome do item para busca binaria: ");
    scanf(" %[^\n]", nomeBusca);

    while (inicio <= fim) {

        comparacoesBinaria++;

        meio = (inicio + fim) / 2;

        int resultado = strcmp(mochilaVetor[meio].nome, nomeBusca);

        if (resultado == 0) {

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochilaVetor[meio].nome);
            printf("Tipo: %s\n", mochilaVetor[meio].tipo);
            printf("Quantidade: %d\n",
                   mochilaVetor[meio].quantidade);

            printf("Comparacoes realizadas: %d\n",
                   comparacoesBinaria);

            return;
        }

        if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nItem nao encontrado.\n");
    printf("Comparacoes realizadas: %d\n",
           comparacoesBinaria);
}

// ===============================
// FUNÇÕES DA LISTA ENCADEADA
// ===============================

// Inserir item na lista
void inserirItemLista() {

    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("\nErro de memoria!\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\nItem inserido na lista com sucesso!\n");
}

// Listar itens da lista
void listarItensLista() {

    No* atual = mochilaLista;

    printf("\n======= MOCHILA LISTA =======\n");

    if (atual == NULL) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("%-20s %-15s %-10s\n",
           "NOME", "TIPO", "QUANTIDADE");

    while (atual != NULL) {

        printf("%-20s %-15s %-10d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

// Remover item da lista
void removerItemLista() {

    char nomeBusca[30];

    No* atual = mochilaLista;
    No* anterior = NULL;

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nomeBusca);

    while (atual != NULL &&
           strcmp(atual->dados.nome, nomeBusca) != 0) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        mochilaLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    printf("\nItem removido com sucesso!\n");
}

// Busca sequencial na lista
void buscarSequencialLista() {

    char nomeBusca[30];

    No* atual = mochilaLista;

    int encontrado = 0;

    comparacoesSequencial = 0;

    printf("\nDigite o nome do item para busca: ");
    scanf(" %[^\n]", nomeBusca);

    while (atual != NULL) {

        comparacoesSequencial++;

        if (strcmp(atual->dados.nome, nomeBusca) == 0) {

            encontrado = 1;

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n",
                   atual->dados.quantidade);

            break;
        }

        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\nItem nao encontrado.\n");
    }

    printf("Comparacoes realizadas: %d\n",
           comparacoesSequencial);
}

// ===============================
// MENU PRINCIPAL
// ===============================
int main() {

    int opcao;

    do {

        printf("\n==============================\n");
        printf(" MOCHILA FREE FIRE - AVENTUREIRO\n");
        printf("==============================\n");

        printf("1 - Inserir item no VETOR\n");
        printf("2 - Remover item do VETOR\n");
        printf("3 - Listar itens do VETOR\n");
        printf("4 - Busca sequencial no VETOR\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria no VETOR\n");

        printf("\n7 - Inserir item na LISTA\n");
        printf("8 - Remover item da LISTA\n");
        printf("9 - Listar itens da LISTA\n");
        printf("10 - Busca sequencial na LISTA\n");

        printf("\n0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItemVetor();
                break;

            case 2:
                removerItemVetor();
                break;

            case 3:
                listarItensVetor();
                break;

            case 4:
                buscarSequencialVetor();
                break;

            case 5:
                ordenarVetor();
                break;

            case 6:
                buscarBinariaVetor();
                break;

            case 7:
                inserirItemLista();
                break;

            case 8:
                removerItemLista();
                break;

            case 9:
                listarItensLista();
                break;

            case 10:
                buscarSequencialLista();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}