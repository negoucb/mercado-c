#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTOS 50  // Define o número máximo de produtos no estoque
#define MAX_CARRINHO 50  // Define o número máximo de itens no carrinho

// Estrutura para representar um Produto
typedef struct {
    int codigo;        // Código do produto
    char nome[30];     // Nome do produto
    float preco;       // Preço do produto
} Produto;

// Estrutura para representar um item no carrinho, incluindo o produto e a quantidade
typedef struct {
    Produto produto;   // Produto adicionado ao carrinho
    int quantidade;    // Quantidade do produto no carrinho
} Carrinho;

// Variáveis globais para o estoque de produtos e o carrinho de compras
Produto estoque[MAX_PRODUTOS];  // Array que armazena os produtos no estoque
Carrinho carrinho[MAX_CARRINHO];  // Array que armazena os produtos adicionados ao carrinho
int total_produtos = 0;  // Contador de produtos cadastrados
int total_itens_carrinho = 0;  // Contador de itens no carrinho

// Declaração das funções utilizadas no sistema
void menuDoMercado();         // Função principal que exibe o menu do mercado
void cadastrarProduto();      // Função para cadastrar novos produtos no estoque
void ListaDeProdutos();       // Função para listar os produtos disponíveis
void comprarProduto();        // Função para adicionar produtos ao carrinho
void produtosDoCarrinho();    // Função para exibir os produtos no carrinho
void fecharPedido();          // Função para finalizar a compra
void infoProduto(Produto prod); // Função para exibir informações de um produto
int temNoCarrinho(int codigo); // Função que verifica se um produto já está no carrinho
void perguntarVoltarMenu();   // Função para perguntar se o usuário deseja voltar ao menu principal

// Função principal que inicializa o sistema
int main() {
    menuDoMercado();  // Chama o menu principal
    return 0;
}

// Função que exibe o menu principal e permite ao usuário escolher uma ação
void menuDoMercado() {
    int opcao;  // Variável para armazenar a escolha do usuário

    // Loop que mantém o menu ativo até o usuário escolher sair
    do {
        // Exibe as opções do menu
        printf("\nS U P E R M E R C A D O\n");
        printf("Bem vindo, escolha sua opcao desejada:\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Lista de Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Sair\n");
        printf("-------->  ");
        scanf("%d", &opcao);  // Lê a opção escolhida
        getchar();  // Limpa o buffer do teclado

        // Escolhe a ação com base na opção inserida
        switch (opcao) {
            case 1:
                cadastrarProduto();  // Cadastra um novo produto
                break;
            case 2:
                ListaDeProdutos();  // Exibe a lista de produtos
                break;
            case 3:
                comprarProduto();  // Adiciona produtos ao carrinho
                break;
            case 4:
                produtosDoCarrinho();  // Exibe o carrinho de compras
                break;
            case 5:
                fecharPedido();  // Fecha o pedido
                break;
            case 6:
                printf("[]Saindo do sistema[]\n");  // Encerra o sistema
                break;
        }
    } while (opcao != 6);  // O loop termina quando o usuário escolhe a opção 6 (Sair)
}

// Função para cadastrar novos produtos no estoque
void cadastrarProduto() {
    if (total_produtos >= MAX_PRODUTOS) {  // Verifica se o estoque está cheio
        printf("[]Estoque de produtos cheio.[]\n");
        perguntarVoltarMenu();
        return;
    }

    Produto novo_produto;  // Variável para armazenar os dados do novo produto

    // Coleta as informações do novo produto
    printf("Digite o codigo do produto: ");
    scanf("%d", &novo_produto.codigo);
    getchar();  // Limpa o buffer do teclado

    // Verifica se o código já está em uso
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == novo_produto.codigo) {
            printf("[]Esse codigo ja foi registrado, insira outro.[]\n");
            perguntarVoltarMenu();
            return;
        }
    }

    // Coleta o nome e o preço do produto
    printf("Digite o nome do produto: ");
    fgets(novo_produto.nome, 30, stdin);
    novo_produto.nome[strcspn(novo_produto.nome, "\n")] = '\0';  // Remove o caractere de nova linha
    printf("Digite o valor do produto: ");
    scanf("%f", &novo_produto.preco);
    getchar();  // Limpa o buffer do teclado

    // Armazena o produto no estoque
    estoque[total_produtos] = novo_produto;
    total_produtos++;  // Incrementa o contador de produtos

    printf("[]Produto cadastrado na lista de produtos[]\n");
    perguntarVoltarMenu();
}

// Função que exibe a lista de produtos cadastrados
void ListaDeProdutos() {
    if (total_produtos == 0) {  // Verifica se há produtos cadastrados
        printf("[]Nenhum produto cadastrado.[]\n");
    } else {
        printf("\nLISTA DE PRODUTOS:\n");
        printf("Codigo\t\tNome\t\tValor\n");
        // Percorre e exibe cada produto do estoque
        for (int i = 0; i < total_produtos; i++) {
            infoProduto(estoque[i]);
        }
    }
    perguntarVoltarMenu();
}

// Função para adicionar produtos ao carrinho de compras
void comprarProduto() {
    if (total_produtos == 0) {  // Verifica se há produtos cadastrados
        printf("[]Nenhum produto cadastrado[].\n");
        perguntarVoltarMenu();
        return;
    }

    int codigo, quantidade;

    // Coleta o código do produto e a quantidade desejada
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);
    getchar();

    // Procura o produto no estoque
    int indice_produto = -1;
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            indice_produto = i;
            break;
        }
    }

    if (indice_produto == -1) {  // Verifica se o produto foi encontrado
        printf("[]Produto não encontrado.[]\n");
        perguntarVoltarMenu();
        return;
    }

    // Coleta a quantidade desejada
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    getchar();

    if (quantidade <= 0) {  // Verifica se a quantidade é válida
        printf("[]Quantidade inválida.[]\n");
        perguntarVoltarMenu();
        return;
    }

    // Verifica se o produto já está no carrinho
    int indice_carrinho = temNoCarrinho(codigo);
    if (indice_carrinho != -1) {
        carrinho[indice_carrinho].quantidade += quantidade;  // Atualiza a quantidade no carrinho
    } else {
        if (total_itens_carrinho >= MAX_CARRINHO) {  // Verifica se o carrinho está cheio
            printf("[]Carrinho cheio.[]\n");
            perguntarVoltarMenu();
            return;
        }
        // Adiciona o produto ao carrinho
        carrinho[total_itens_carrinho].produto = estoque[indice_produto];
        carrinho[total_itens_carrinho].quantidade = quantidade;
        total_itens_carrinho++;  // Incrementa o contador de itens no carrinho
    }

    printf("[]Produto adicionado ao carrinho.[]\n");
    perguntarVoltarMenu();
}

// Função que exibe os produtos no carrinho de compras
void produtosDoCarrinho() {
    if (total_itens_carrinho == 0) {  // Verifica se o carrinho está vazio
        printf("[]Carrinho vazio.[]\n");
    } else {
        float total = 0;

        // Exibe os produtos no carrinho com detalhes
        printf("\nCARRINHO DE COMPRAS\n");
        printf("Codigo\t\tNome\t\tQuantidade\tValor\tSubtotal\n");
        for (int i = 0; i < total_itens_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int qtd = carrinho[i].quantidade;
            float subtotal = p.preco * qtd;
            total += subtotal;

            printf("%d\t\t%s\t\t%d\t\tR$%.2f\t\tR$%.2f\n", p.codigo, p.nome, qtd, p.preco, subtotal);
        }

        printf("\n[]Total a pagar: R$%.2f []\n", total);  // Exibe o valor total da compra
    }
    perguntarVoltarMenu();
}

// Função que finaliza a compra e fecha o pedido
void fecharPedido() {
    if (total_itens_carrinho == 0) {  // Verifica se o carrinho está vazio
        printf("[]O Carrinho esta vazio. Adicione um produto para fechar o pedido.[]\n");
    } else {
        produtosDoCarrinho();  // Exibe os itens no carrinho antes de finalizar
        printf("\n[]Pedido fechado com sucesso[]\n");
        printf("[]Volte sempre![]\n");

        total_itens_carrinho = 0;  // Limpa o carrinho
    }
    perguntarVoltarMenu();
}

// Função auxiliar para exibir as informações de um produto
void infoProduto(Produto prod) {
    printf("%d\t\t%s\t\tR$%.2f\n", prod.codigo, prod.nome, prod.preco);
}

// Função que verifica se um produto já está no carrinho
int temNoCarrinho(int codigo) {
    for (int i = 0; i < total_itens_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;  // Retorna o índice do produto no carrinho
        }
    }
    return -1;  // Retorna -1 se o produto não estiver no carrinho
}

// Função que pergunta se o usuário deseja voltar ao menu principal
void perguntarVoltarMenu() {
    char opcao;
    do {
        printf("\nDeseja voltar ao menu principal? (s/n): ");
        scanf(" %c", &opcao);
        getchar();
    } while (opcao != 's' && opcao != 'n');  // Verifica se a resposta é válida

    if (opcao == 'n') {  // Se o usuário escolher 'n', o sistema encerra
        printf("[]Saindo do sistema[]\n");
        exit(0);
    }
}
