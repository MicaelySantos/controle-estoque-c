#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define ARQUIVO "produtos.dat"

// Estrutura que representa um produto
typedef struct {
    int codigo;
    char nome[100];
    float preco;
    int quantidade;
} Produto;

Produto produtos[MAX_PRODUTOS];
int total = 0;

// Limpa o restante da entrada
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Le um numero inteiro
int lerInteiro(const char *mensagem, int *valor) {
    printf("%s", mensagem);

    if (scanf("%d", valor) != 1) {
        limparEntrada();
        printf("Entrada invalida!\n");
        return 0;
    }

    limparEntrada();
    return 1;
}

// Le um preco usando ponto decimal
int lerPreco(const char *mensagem, float *valor) {
    char entrada[100];
    char extra;

    printf("%s", mensagem);

    if (!fgets(entrada, sizeof(entrada), stdin)) {
        return 0;
    }

    // Aceita virgula ou ponto decimal
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == ',') {
            entrada[i] = '.';
        }
    }

    if (sscanf(entrada, "%f %c", valor, &extra) != 1) {
        printf("Preco invalido!\n");
        return 0;
    }

    if (*valor < 0) {
        printf("O preco nao pode ser negativo!\n");
        return 0;
    }

    return 1;
}

// Salva os produtos no arquivo
void salvarProdutos() {
    FILE *arquivo = fopen(ARQUIVO, "wb");

    if (arquivo == NULL) {
        printf("Erro ao salvar os produtos!\n");
        return;
    }

    fwrite(&total, sizeof(int), 1, arquivo);
    fwrite(produtos, sizeof(Produto), total, arquivo);

    fclose(arquivo);
}

// Carrega os produtos salvos
void carregarProdutos() {
    FILE *arquivo = fopen(ARQUIVO, "rb");

    if (arquivo == NULL) {
        return;
    }

    int quantidadeSalva;

    if (fread(&quantidadeSalva, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return;
    }

    if (quantidadeSalva < 0 || quantidadeSalva > MAX_PRODUTOS) {
        fclose(arquivo);
        return;
    }

    if (fread(produtos, sizeof(Produto),
              quantidadeSalva, arquivo) == (size_t) quantidadeSalva) {
        total = quantidadeSalva;
    }

    fclose(arquivo);
}

// Procura um produto pelo codigo
int buscarIndice(int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

// Exibe as informacoes de um produto
void mostrarProduto(Produto p) {
    printf("\nCodigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Preco: R$ %.2f\n", p.preco);
    printf("Quantidade: %d\n", p.quantidade);
    printf("-----------------------------\n");
}

// Opcao 1 - Cadastrar produto
void cadastrarProduto() {
    if (total >= MAX_PRODUTOS) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    Produto novo;

    printf("\n--- CADASTRAR PRODUTO ---\n");

    if (!lerInteiro("Codigo: ", &novo.codigo)) {
        return;
    }

    if (novo.codigo <= 0) {
        printf("O codigo deve ser positivo!\n");
        return;
    }

    if (buscarIndice(novo.codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    printf("Nome: ");

    if (!fgets(novo.nome, sizeof(novo.nome), stdin)) {
        return;
    }

    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    if (strlen(novo.nome) == 0) {
        printf("O nome nao pode estar vazio!\n");
        return;
    }

    if (!lerPreco("Preco: ", &novo.preco)) {
        return;
    }

    if (!lerInteiro("Quantidade: ", &novo.quantidade)) {
        return;
    }

    if (novo.quantidade < 0) {
        printf("A quantidade nao pode ser negativa!\n");
        return;
    }

    produtos[total] = novo;
    total++;

    salvarProdutos();

    printf("\nProduto cadastrado com sucesso!\n");
}

// Opcao 2 - Listar produtos
void listarProdutos() {
    printf("\n--- LISTA DE PRODUTOS ---\n");

    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        mostrarProduto(produtos[i]);
    }
}

// Opcao 3 - Buscar produto
void buscarProduto() {
    int codigo;

    printf("\n--- BUSCAR PRODUTO ---\n");

    if (!lerInteiro("Codigo do produto: ", &codigo)) {
        return;
    }

    int indice = buscarIndice(codigo);

    if (indice == -1) {
        printf("Produto nao encontrado!\n");
    } else {
        printf("\nProduto encontrado!\n");
        mostrarProduto(produtos[indice]);
    }
}

// Opcao 4 - Atualizar estoque
void atualizarEstoque() {
    int codigo, quantidade, opcao;

    printf("\n--- ATUALIZAR ESTOQUE ---\n");

    if (!lerInteiro("Codigo do produto: ", &codigo)) {
        return;
    }

    int indice = buscarIndice(codigo);

    if (indice == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    mostrarProduto(produtos[indice]);

    printf("1 - Adicionar unidades\n");
    printf("2 - Retirar unidades\n");

    if (!lerInteiro("Escolha: ", &opcao)) {
        return;
    }

    if (opcao != 1 && opcao != 2) {
        printf("Opcao invalida!\n");
        return;
    }

    if (!lerInteiro("Quantidade: ", &quantidade)) {
        return;
    }

    if (quantidade <= 0) {
        printf("A quantidade deve ser positiva!\n");
        return;
    }

    if (opcao == 1) {
        produtos[indice].quantidade += quantidade;
    } else {
        if (quantidade > produtos[indice].quantidade) {
            printf("Quantidade insuficiente no estoque!\n");
            return;
        }

        produtos[indice].quantidade -= quantidade;
    }

    salvarProdutos();

    printf("\nEstoque atualizado com sucesso!\n");
    printf("Novo estoque: %d\n",
           produtos[indice].quantidade);
}

// Opcao 5 - Registrar venda
void registrarVenda() {
    int codigo, quantidade;

    printf("\n--- REGISTRAR VENDA ---\n");

    if (!lerInteiro("Codigo do produto: ", &codigo)) {
        return;
    }

    int indice = buscarIndice(codigo);

    if (indice == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    mostrarProduto(produtos[indice]);

    if (!lerInteiro("Quantidade vendida: ", &quantidade)) {
        return;
    }

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade > produtos[indice].quantidade) {
        printf("Estoque insuficiente para a venda!\n");
        return;
    }

    float valorTotal = quantidade * produtos[indice].preco;

    produtos[indice].quantidade -= quantidade;

    salvarProdutos();

    printf("\nVenda registrada com sucesso!\n");
    printf("Produto: %s\n", produtos[indice].nome);
    printf("Quantidade vendida: %d\n", quantidade);
    printf("Valor total: R$ %.2f\n", valorTotal);
    printf("Estoque restante: %d\n",
           produtos[indice].quantidade);
}

// Opcao 6 - Remover produto
void removerProduto() {
    int codigo, confirmacao;

    printf("\n--- REMOVER PRODUTO ---\n");

    if (!lerInteiro("Codigo do produto: ", &codigo)) {
        return;
    }

    int indice = buscarIndice(codigo);

    if (indice == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    mostrarProduto(produtos[indice]);

    if (!lerInteiro("Confirmar remocao? (1-Sim / 0-Nao): ",
                    &confirmacao)) {
        return;
    }

    if (confirmacao != 1) {
        printf("Remocao cancelada.\n");
        return;
    }

    for (int i = indice; i < total - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    total--;

    salvarProdutos();

    printf("\nProduto removido com sucesso!\n");
}

// Opcao 7 - Relatorio de estoque
void relatorioEstoque() {
    int quantidadeTotal = 0;
    int estoqueBaixo = 0;
    float valorEstoque = 0;

    printf("\n--- RELATORIO DE ESTOQUE ---\n");

    for (int i = 0; i < total; i++) {
        quantidadeTotal += produtos[i].quantidade;

        valorEstoque += produtos[i].preco *
                        produtos[i].quantidade;

        if (produtos[i].quantidade < 5) {
            estoqueBaixo++;
        }
    }

    printf("Produtos diferentes: %d\n", total);
    printf("Total de unidades: %d\n", quantidadeTotal);
    printf("Valor total do estoque: R$ %.2f\n",
           valorEstoque);
    printf("Produtos com estoque baixo (< 5): %d\n",
           estoqueBaixo);

    if (estoqueBaixo > 0) {
        printf("\nProdutos com estoque baixo:\n");

        for (int i = 0; i < total; i++) {
            if (produtos[i].quantidade < 5) {
                printf("- %s: %d unidades\n",
                       produtos[i].nome,
                       produtos[i].quantidade);
            }
        }
    }
}

// Exibe o menu principal
void mostrarMenu() {
    printf("\n================================\n");
    printf("   SISTEMA DE CONTROLE DE ESTOQUE\n");
    printf("================================\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Buscar produto por codigo\n");
    printf("4 - Atualizar estoque\n");
    printf("5 - Registrar venda\n");
    printf("6 - Remover produto\n");
    printf("7 - Relatorio de estoque\n");
    printf("0 - Sair\n");
    printf("================================\n");
}

int main() {
    int opcao;

    carregarProdutos();

    do {
        mostrarMenu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;

            case 2:
                listarProdutos();
                break;

            case 3:
                buscarProduto();
                break;

            case 4:
                atualizarEstoque();
                break;

            case 5:
                registrarVenda();
                break;

            case 6:
                removerProduto();
                break;

            case 7:
                relatorioEstoque();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                printf("Ate a proxima!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
