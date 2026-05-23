#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens
Item mochila[MAX_ITENS];

// Variável que controla a quantidade de itens cadastrados
int totalItens = 0;

// Função para listar todos os itens da mochila
void listarItens() {
    int i;

    printf("\n========== ITENS DA MOCHILA ==========\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("%-20s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("-------------------------------------------------\n");

        for (i = 0; i < totalItens; i++) {
            printf("%-20s %-15s %-10d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }

    printf("======================================\n");
}

// Função para inserir um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Limite de 10 itens.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Digite o tipo do item (arma, municao, cura...): ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("\nItem adicionado com sucesso!\n");

    listarItens();
}

// Função para remover um item pelo nome
void removerItem() {
    char nomeBusca[30];
    int i, encontrado = 0;

    if (totalItens == 0) {
        printf("\nNao ha itens para remover.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (i = 0; i < totalItens; i++) {

        // strcmp compara duas strings
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            encontrado = 1;

            // Move os itens para preencher o espaco vazio
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;

            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado.\n");
    }

    listarItens();
}

// Função de busca sequencial
void buscarItem() {
    char nomeBusca[30];
    int i, encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item para busca: ");
    scanf(" %[^\n]", nomeBusca);

    for (i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("===========================\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila.\n");
    }
}

// Função principal
int main() {

    int opcao;

    do {

        printf("\n========== MENU ==========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("==========================\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}