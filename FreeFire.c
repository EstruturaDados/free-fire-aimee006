// Sistema de Inventário - Mochila de Sobrevivência (Free Fire)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definições de constantes: tamanho máximo da mochila e tamanhos dos campos.
#define MAX_ITENS 10
#define NOME_TAM 30
#define TIPO_TAM 20

// Definição da struct "Item": armazena nome, tipo e quantidade do objeto.
typedef struct {
    char nome[NOME_TAM];
    char tipo[TIPO_TAM];
    int quantidade;
} Item;

// Vetor que representa a mochila e contador de itens atuais.
Item mochila[MAX_ITENS];
int itemCount = 0;

// Helper: lê uma linha da entrada e remove o '\n' final, se houver.
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        // Em caso de erro, garante string vazia
        buffer[0] = '\0';
    }
}

// Lista todos os itens atualmente registrados na mochila.
void listarItens() {
    printf("\n-------------- CONTEÚDO DA MOCHILA (%d/%d) ----------\n", itemCount, MAX_ITENS);
    if (itemCount == 0) {
        printf("(Mochila vazia!)\n");
    } else {
        for (int i = 0; i < itemCount; i++) {
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("----------------------------------------------------\n");
}

// Inserir um novo item na mochila, se houver capacidade.
void inserirItem() {
    if (itemCount >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível inserir mais itens.\n");
        return;
    }

    Item novo;
    char qtdStr[16];

    printf("Digite o nome do item: ");
    readLine(novo.nome, NOME_TAM);
    if (strlen(novo.nome) == 0) {
        printf("\nNome inválido. Operação cancelada.\n");
        return;
    }

    printf("Digite o tipo do item (ex: arma, munição, cura, ferramenta): ");
    readLine(novo.tipo, TIPO_TAM);
    if (strlen(novo.tipo) == 0) {
        printf("\nTipo inválido. Operação cancelada.\n");
        return;
    }

    printf("Digite a quantidade: ");
    readLine(qtdStr, sizeof(qtdStr));
    if (sscanf(qtdStr, "%d", &novo.quantidade) != 1 || novo.quantidade < 0) {
        printf("\nQuantidade inválida. Operação cancelada.\n");
        return;
    }

    // Copia o item para o vetor e incrementa o contador.
    mochila[itemCount++] = novo;
    printf("\nItem '%s' cadastrado com sucesso!\n", novo.nome);
    listarItens();
}

// Remove um item da mochila informando seu nome; desloca os demais.
void removerItem() {
    if (itemCount == 0) {
        printf("\nMochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[NOME_TAM];
    printf("Digite o nome do item a remover: ");
    readLine(nomeBusca, NOME_TAM);
    if (strlen(nomeBusca) == 0) {
        printf("\nNome inválido. Operação cancelada.\n");
        return;
    }

    int pos = -1;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem '%s' não encontrado na mochila...\n", nomeBusca);
    } else {
        // Desloca os elementos seguintes para manter vetor compacto.
        for (int j = pos; j < itemCount - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        itemCount--;
        printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
    }

    listarItens();
}

// Busca sequencial por nome e exibe os dados do item, se encontrado.
void buscarItem() {
    if (itemCount == 0) {
        printf("\nMochila vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[NOME_TAM];
    printf("\nDigite o nome do item para buscar: ");
    readLine(nomeBusca, NOME_TAM);
    if (strlen(nomeBusca) == 0) {
        printf("\nNome inválido. Operação cancelada.\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
}

// Menu principal e fluxo de execução.
int main() {
    char escolhaStr[8];
    int escolha = 0;

    printf("\n=========================================================\n");
    printf("==== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA ====\n");
    printf("=========================================================\n");

    while (1) {
        printf("\n1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("5 - Sair\n");
        printf("\nEscolha uma opção: ");

        readLine(escolhaStr, sizeof(escolhaStr));
        if (sscanf(escolhaStr, "%d", &escolha) != 1) {
            printf("\nOpção inválida. Digite um número de 1 a 5.\n");
            continue;
        }

        switch (escolha) {
        case 1:
            inserirItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            buscarItem();
            break;
        case 4:
            listarItens();
            break;
        case 5:
            printf("\nSaindo... Boa sorte na partida!\n");
            return 0;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
        }
    }

    return 0;
}