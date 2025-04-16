// Biblioteca que possui comandos relativos � entrada e sa�da de dados do computador
#include <stdio.h>
// Biblioteca para fun��es envolvendo aloca��o de mem�ria, controle de processos, convers�es etc
#include <stdlib.h>

// Declara��o das fun��es
int menuPrincipal();
int categoriaMaterialDeLimpeza();
int categoriaVendaDeAlimentos();
int categoriaPadaria();
int comprarProdutosLimpeza(float valorDoProduto);
int comprarProdutosAlimento(float valorDoProduto);
int comprarProdutosPadaria(float valorDoProduto);
int pagamento();
int continuarCompra();

// Declara��o das vari�veis globais
char compra, abrindoCaixa;
int quantidade;
int quantProdVendidos = 0, diaJaIniciado = 0, simulacaoDias = 0, validacaoSaldoInicial = 0;
int i = 1, estoqueValido = 1, foiAbertoHoje = 0;

// Vari�vel respons�vel por armazenar a escolha do Menu Principal
int escolhaDoMenuPrincipal = 0;

// Vari�veis respons�veis por armazenamento das categorias
float totalDia;
float total, valorCompra, desconto, descontoDaBere, total_desconto, valor_cliente, troco, totalDia, saldoFinal, saldoInicial, total_limpeza, total_alimentos, total_padaria;

// Vetor respons�vel por armazenar a quantidade de produtos do estoque da categoria 2. Material de Limpeza
int estoqueLimpeza[] = {50, 30, 0, 20, 100, 15, 60};
// Vetor respons�vel por armazenar a quantidade de produtos do estoque da categoria 3. Venda de Alimentos
int estoquealimentos[] = {10, 15, 10, 5, 20, 6, 15};

// Fun��o principal do sistema
int main()
{
    // Vari�vel respons�vel por armazenar a escolha de produtos do usu�rio
    int produtoEscolhido;
    // Vetor respons�vel por armazenar os pre�os dos produtos da categoria 2. Material de Limpeza
    float valoresProdutoLimpeza[] = {1.99, 8.99, 1.50, 15.00, 4.99, 7.99, 1.00};
    // Vetor respons�vel por armazenar os pre�os dos produtos da categoria 3. Venda de Alimentos
    float valoresProdutoAlimento[] = {19.99, 5.90, 4.50, 8.00, 5.00, 2.00, 5.00};
    // Vetor respons�vel por armazenar os pre�os dos produtos da categoria 4. Padaria
    float valoresProdutosPadaria[] = {9.50, 12.50, 1.90, 8.50, 12.50, 2.50, 17.50};
    // Vetor respons�vel por armazenar a quantidade de produtos do estoque da categoria 3. Venda de Alimentos
    int estoqueAlimentos[] = {10, 15, 10, 5, 20, 6, 15};
    // Vari�vel auxiliar usada em loops de repeti��o (ex: para percorrer arrays)
    int a;
    // Quantidade total de produtos da padaria
    int n = 7;

    // Vetor que armazena a quantidade em estoque de cada produto da padaria
    int EstoquePadaria[n];
    // Vetor de strings com os nomes dos produtos da padaria
    char *nomesProdutosPadaria[] = {"Pao de Forma", "Pao Integral", "Pao Frances", "Sonho", "Biscoito", "Pao Doce", "Salgado"};

    // Vetor respons�vel por armazenar as categorias do Menu Principal
    float categorias[] = {total_limpeza, total_alimentos, total_padaria};
    // Vari�vel respons�vel por armazenar a escolha de pagamento do usu�rio
    int formaPagamento, cartao;

    // In�cio do loop principal que representa os dias de opera��o da mercearia
    do
    {
        // Enquanto o dia atual (i) for diferente da quantidade total de dias simulados
        while (i != simulacaoDias)
        {
            // Executa o procedimento de "fim de dia" somente se for o primeiro acesso do dia
            if (diaJaIniciado == 0)
            {
                // Exibe informa��es de finaliza��o do dia anterior
                diaFinalizado();
            }

            // O usu�rio escolhe uma op��o no Menu Principal
            switch (escolhaDoMenuPrincipal)
            {

            // Caso o usu�rio escolha a op��o 1. Abertura de Caixa
            case 1:
                // Verifica se o caixa ainda n�o foi aberto no dia
                if (foiAbertoHoje == 0)
                {
                    // Solicita ao usu�rio que confirme a abertura do caixa com 'A' ou 'a'
                    do
                    {
                        avisoAbrindoCaixa();
                        printf("Digite 'A' ou 'a' para abrir o caixa: ");
                        scanf(" %c", &abrindoCaixa);

                        // Se o usu�rio digitar corretamente
                        if (abrindoCaixa == 'A' || abrindoCaixa == 'a')
                        {
                            // Solicita o valor inicial do caixa
                            printf("Insira o Saldo Inicial do Caixa: R$ ");
                            while (scanf("%f", &saldoInicial) != 1)
                            {
                                // Valida a entrada e solicita novamente caso n�o seja n�mero
                                printf("Insira o Saldo Inicial do Caixa: R$ ");
                                while (getchar() != '\n');
                            }

                            // Valida��es espec�ficas para quando o sistema j� passou do primeiro dia
                            while (i >= 2)
                            {
                                // Verifica se o saldo inicial inserido � maior que o fechamento anterior
                                if (saldoInicial > saldoFinal)
                                {
                                    validacaoSaldoInicial = 1;
                                    break;
                                }

                                else
                                {
                                    validacaoSaldoInicial = 0;
                                    break;
                                }
                            }

                            // Se o valor inserido for maior do que o saldo final anterior
                            if (validacaoSaldoInicial == 1)
                            {
                                while (saldoInicial > saldoFinal)
                                {
                                    printf("Voce esta tentando inserir um valor maior que o fechamento do caixa do dia anterior\n"
                                           "INSIRA UM VALOR MENOR PARA DAR PROSSEGUIMENTO NO SISTEMA\n\n");
                                    // Solicita novo valor inicial v�lido
                                    adicionarNovoSaldoInicial();
                                }
                            }

                            // Se o valor for menor que R$ 200,00. Pede confirma��o da Dona Ber�
                            if (validacaoSaldoInicial == 0)
                            {
                                while (saldoInicial < 200.00)
                                {
                                    // Mensagem avisando que o valor � muito baixo
                                    avisoParaBere();
                                    scanf("%s", &compra);

                                    // Se a Dona Ber� quiser continuar mesmo assim
                                    if (compra == 's' || compra == 'S')
                                    {
                                        // Exibe um alerta de valor baixo
                                        avisoValorMinimo();
                                        break;
                                    }

                                    // Se quiser digitar um novo valor
                                    if (compra == 'n' || compra == 'N')
                                    {
                                        while (saldoInicial < 200.00)
                                        {
                                            // Solicita um novo valor
                                            adicionarNovoSaldoInicial();
                                            break;
                                        }

                                    }
                                }
                            }

                            // Exibe mensagem de sucesso ao abrir o caixa com o valor informado
                            avisoSaldoInicial();
                            // Marca que o dia j� come�ou
                            diaJaIniciado = 1;
                            // Marca que o caixa foi aberto hoje
                            foiAbertoHoje = 1;

                                // Solicita o estoque dos produtos da padaria (manual)
                                for (a = 0; a < n; a++)
                                {
                                    printf("Informe o estoque para %s (codigo %d): ", nomesProdutosPadaria[a], 31 + a);

                                    // Valida��o: entrada deve ser n�mero
                                    while(scanf("%d", &EstoquePadaria[a]) != 1)
                                    {
                                        printf("Por favor, informe somente numeros: >> ");
                                        while(getchar() != '\n');
                                    }

                                    // Valida��o: n�o permitir valores negativos
                                    while (EstoquePadaria[a] < 0)
                                    {
                                        printf("\033[31mNao eh permitido inserir valores negativos. Por favor, insira valores maiores que 0:\033[0m ");
                                        scanf("%d", &EstoquePadaria[a]);
                                    }
                            }
                            break;
                        }

                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while (getchar() != '\n');

                    // Continua solicitando at� que digite 'A' ou 'a' corretamente
                    } while (diaJaIniciado != 'A' || diaJaIniciado != 'a');

                }

                // Se tentar abrir o caixa novamente no mesmo dia, n�o permite
                else
                {
                    printf("\033[31mNao eh possivel abrir o caixa novamente. Tente no dia seguinte\033[0m\n");

                    // Exibe o Menu Principal
                    menuPrincipal();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }break;
                }

                // Exibe o Menu Principal
                menuPrincipal();
                // Enquanto a escolha do usu�rio seja diferente da Abertura de Caixa
                while (scanf("%d", &escolhaDoMenuPrincipal) != 1)
                {
                    // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                    while (getchar() != '\n');
                    // Mensagem caso digite algo inv�lido
                    avisoPalavra();
                    // Exibe o Menu Principal
                    menuPrincipal();
                }
                break;

            // Caso o usu�rio escolha a op��o 2. Material de Limpeza
            case 2:
                // In�cio do loop Do While da categoria 2. Material de Limpeza
                do
                {
                    // Exibe o menu da categoria 2. Material de Limpeza
                    categoriaMaterialDeLimpeza();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &produtoEscolhido) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }

                    // Escolha dos produtos da categoria 2. Material de Limpeza
                    switch (produtoEscolhido)
                    {
                        // 11 - Detergente - R$ 1.99 - Estoque: 50
                        case 11:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[0]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueLimpeza[0] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[0]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[0])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[0]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[0] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 12 - Sabao em Po (1 kg) - R$ 8.99 - Estoque: 30
                        case 12:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[1]);

                            // Se o estoque do Sab�o em P� estiver vazio
                            if (estoqueLimpeza[1] == 0)
                            {
                                // Exibir� um aviso que falta Sab�o em P� no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[1]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[1])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[1]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[1] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 13 - Esponja - R$ 1.50 - Estoque: 0
                        case 13:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[2]);

                            // Se o estoque da Esponja estiver vazio
                            if (estoqueLimpeza[2] == 0)
                            {
                                // Exibir� um aviso que falta Esponja no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[2]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[2])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[2]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[2] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 14 - Amaciante (1 L) - R$ 15.00 - Estoque: 20
                        case 14:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[3]);

                            // Se o estoque do Amaciante estiver vazio
                            if (estoqueLimpeza[3] == 0)
                            {
                                // Exibir� um aviso que falta Esponja no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[3]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[3])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[3]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[3] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 15 - Bucha de Pia (kit c/3) - R$ 4.99 - Estoque: 100
                        case 15:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[4]);

                            // Se o estoque da Bucha de Pia estiver vazio
                            if (estoqueLimpeza[4] == 0)
                            {
                                // Exibir� um aviso que falta Bucha de Pia no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[4]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[4])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[4]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[4] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 16 - Desinfetante (1 L) - R$ 7.99 - Estoque: 15
                        case 16:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[5]);

                            // Se o estoque do Desinfetante estiver vazio
                            if (estoqueLimpeza[5] == 0)
                            {
                                // Exibir� um aviso que falta Desinfetante no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[5]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[5])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[5]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[5] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 17 - Sabao em Barra (unidade) - R$ 1.00 - Estoque: 60
                        case 17:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosLimpeza(valoresProdutoLimpeza[6]);

                            // Se o estoque do Sab�o em Barra estiver vazio
                            if (estoqueLimpeza[6] == 0)
                            {
                                // Exibir� um aviso que falta Sab�o em Barra no estoque
                                faltaProdutoNoEstoque();
                                total_limpeza = total_limpeza - (quantidade * valoresProdutoLimpeza[6]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueLimpeza[6])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueLimpeza[6]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueLimpeza[6] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[0] = total_limpeza;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 18 - Voltar ao Menu Principal
                        case 18:
                            // Exibe uma mensagem perguntando ao usu�rio se ele deseja permanecer na categoria ou n�o
                            continuarCompra();
                            break;

                        // Caso o usu�rio n�o escolha nenhuma das alternativas anteriores
                        default:
                            printf("\033[31m*** Escolha invalida ***\033[0m\n");
                            continue;
                    }
                } while (compra == 'S' || compra == 's');

                // Se o usu�rio n�o quiser n�o deseja continuar comprando
                if (compra == 'n' || compra == 'N')
                {
                    // Exibe o Menu Principal para o usu�rio escolher outra categoria
                    menuPrincipal();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }
                }
                break;

            // Caso o usu�rio escolha a op��o 3. Venda de Alimentos
            case 3:
                // In�cio do loop Do While da categoria 3. Venda de Alimentos
                do
                {
                    // Exibe o menu da categoria 3. Venda de Alimentos
                    categoriaVendaDeAlimentos();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &produtoEscolhido) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }

                    // Escolha dos produtos da categoria 3. Venda de Alimentos
                    switch (produtoEscolhido)
                    {
                        // 21 - Cafe (500 mg) - R$ 19.99 - Estoque: 10
                        case 21:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[0]);

                            // Se o estoque do Caf� estiver vazio
                            if (estoqueAlimentos[0] == 0)
                            {
                                // Exibir� um aviso que falta Caf� no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[0]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[0])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[0]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[0] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 22 - Leite (caixinha) - R$ 5.90 - Estoque: 15
                        case 22:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[1]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[1] == 0)
                            {
                                // Exibir� um aviso que falta Leite no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[1]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[1])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[1]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[1] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 23 - Arroz (1 kg) - R$ 4.50 - Estoque: 10
                        case 23:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[2]);

                            // Se o estoque do Arroz estiver vazio
                            if (estoqueAlimentos[2] == 0)
                            {
                                // Exibir� um aviso que falta Arroz no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[2]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[2])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[2]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[2] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 24 - Feijao Preto (1kg) - R$ 8.00 - Estoque: 5
                        case 24:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[3]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[3] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[3]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[3])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[3]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[3] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 25 - Acucar (1 kg) - R$ 5.00 - Estoque: 20
                        case 25:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[4]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[4] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[4]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[4])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[4]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[4] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 26 - Sal (1 kg) - R$ 2.00 - Estoque: 6
                        case 26:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[5]);

                            // Se o estoque do Sal estiver vazio
                            if (estoqueAlimentos[5] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[5]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[5])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[5]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[5] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 27 - Farinha de Trigo (1 kg) R$ 5.00 - Estoque: 15
                        case 27:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[6]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[6] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[6]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[6])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[6]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            estoqueAlimentos[6] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 28 - Voltar ao Menu Principal
                        case 28:
                            // Exibe uma mensagem perguntando ao usu�rio se ele deseja permanecer na categoria ou n�o
                            continuarCompra();
                            break;

                        // Caso o usu�rio n�o escolha nenhuma das alternativas anteriores
                        default:
                            printf("\033[31m*** Escolha invalida ***\033[0m\n");
                            continue;
                    }
                } while (compra == 'S' || compra == 's');

                if (compra == 'n' || compra == 'N')
                {
                    menuPrincipal();
                    scanf("%d", &escolhaDoMenuPrincipal);
                }
                break;

            // Caso o usu�rio escolha a op��o 4. Padaria
            case 4:
                // In�cio do loop Do While da categoria 4.Padaria
                do
                {
                    // Exibe o menu da categoria 4. Padaria
                    categoriaPadaria();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &produtoEscolhido) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }

                    // Escolha dos produtos da categoria 4. Padaria
                    switch (produtoEscolhido)
                    {
                        // 31 - Pao de Forma (pacote) - R$ 9.50 - Unidade: ?
                        case 31:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[0]);

                            // Se o estoque do P�o de Forma estiver vazio
                            if (EstoquePadaria[0] == 0)
                            {
                                // Exibir� um aviso que falta P�o de Forma no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[0]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[0])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[0]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[0] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 32 - Pao Integral (pacote) - R$ 12.50 - Unidade: ?
                        case 32:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[1]);

                            // Se o estoque do P�o Integral estiver vazio
                            if (EstoquePadaria[1] == 0)
                            {
                                // Exibir� um aviso que falta P�o Integral no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[1]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[1])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[1]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[1] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 33 - Pao Frances (unidade) - R$ 1.90 - Unidade: ?
                        case 33:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[2]);

                            // Se o estoque do P�o Franc�s estiver vazio
                            if(EstoquePadaria[2] == 0)
                            {
                                // Exibir� um aviso que falta P�o Franc�s no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[2]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[2])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[2]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[2] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 34 - Sonho (unidade) - R$ 8.50 - Unidade: ?
                        case 34:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[3]);

                            // Se o estoque do Sonho estiver vazio
                            if(EstoquePadaria[3] == 0)
                            {
                                // Exibir� um aviso que falta Sonho no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[3]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[3])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[3]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[3] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 35 - Biscoito (kg) - R$ 12.50 - Unidade: ?
                        case 35:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[4]);

                            // Se o estoque do Biscoito estiver vazio
                            if(EstoquePadaria[4] == 0)
                            {
                                // Exibir� um aviso que falta Biscoito no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[4]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[4])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[4]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[4] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 36 - Pao Doce (unidade) - R$ 2.50 - Unidade: ?
                        case 36:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[5]);

                            // Se o estoque do P�o Doce estiver vazio
                            if(EstoquePadaria[5] == 0)
                            {
                                // Exibir� um aviso que falta P�o Doce no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[5]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[5])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[5]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[5] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 37 - Salgado (unidade) - R$ 17.50 - Estoque: ?
                        case 37:
                            // Fun��o utilizando como par�metro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[6]);

                            // Se o estoque do Salgado estiver vazio
                            if (EstoquePadaria[6] == 0)
                            {
                                // Exibir� um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[6]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usu�rio escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[6])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[6]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usu�rio
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque ap�s a venda do item
                            EstoquePadaria[6] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[2] = total_padaria;
                            // Indica que n�o houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 38 - Voltar ao Menu Principal
                        case 38:
                            // Exibe uma mensagem perguntando ao usu�rio se ele deseja permanecer na categoria ou n�o
                            continuarCompra();
                            break;

                        // Caso o usu�rio n�o escolha nenhuma das alternativas anteriores
                        default:
                            printf("\033[31m*** Escolha invalida ***\033[0m\n");
                            continue;
                    }
                } while (compra == 'S' || compra == 's');

                // Se o usu�rio n�o queira permanecer na categoria
                if (compra == 'n' || compra == 'N')
                {
                    // Exibe o Menu Principal
                    menuPrincipal();
                    // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                    while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                        while(getchar() != '\n');
                    }
                }
                break;

            // Caso o usu�rio escolha a op��o 5. Pagamento
            case 5:
                // In�cio do Do While da categoria 5. Pagamento
                do
                {
                    // Fun��o que mostra as op��es de pagamento
                    pagamento();
                    // Guarda a escolha do usu�rio
                    while(scanf("%d", &formaPagamento) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        while(getchar() != '\n');
                    }
                    // Switch do 5. Pagamento
                    switch (formaPagamento)
                    {
                    // Caso o usu�rio escolha a op��o de pagamento 1. Dinheiro
                    case 1:
                        // Informando a forma de pagamento
                        avisoPagamento();
                        // Aqui estou guardando o valor total da compra do cliente
                        total = total_alimentos + total_limpeza + total_padaria;
                        // Hist�rico das categorias
                        printf("1. Material de Limpeza - Total: R$ %.2f\n", categorias[0]);
                        printf("2. Venda de Alimentos - Total: R$ %.2f\n", categorias[1]);
                        printf("3. Padaria - Total: R$ %.2f\n\n", categorias[2]);

                        // Valor total sem desconto
                        printf("Valor Total (SEM desconto): R$ %.2f\n\n", total);
                        printf("-------------------------------------------------\n");

                        // Se o usu�rio gastou menos ou igual a R$ 50.00
                        if (total <= 50)
                        {
                            total = total_alimentos + total_limpeza + total_padaria;
                            // C�lculo do valor do desconto
                            desconto = total * 0.05;
                            // C�lculo do valor que o cliente ir� pagar
                            total_desconto = total - desconto;
                            // Mostrando o valor que o usu�rio ir� pagar
                            printf("Valor Total (COM desconto): R$ %.2f \n\n", total_desconto);
                            // Aqui est� dizendo para o usu�rio inserir o valor recebido em dinheiro
                            printf("Insira o Valor recebido em Dinheiro: R$ ");
                            // Armazenando o valor que o usu�rio informou acima
                            scanf("%f", &valor_cliente);

                            // Condi��o que � quando o usu�rio coloca um valor menor do que ele tem que pagar
                            if (valor_cliente < total_desconto)
                            {
                                // Informando o usuario que o valor inserido � menor que o valor a pagar
                                printf("-------------------------------------------------\n");
                                printf("O numero em Dinheiro fornecido pelo cliente eh menor que o Valor a Pagar\n"
                                       "Insira o Valor Novamente: R$ ");
                                // Aqui ficar� armazenado o novo valor que o usu�rio deu para o pagamento
                                scanf("%f", &valor_cliente);
                            }

                            // C�lculo do valor de troco
                            troco = valor_cliente - total_desconto;
                            // Informa o troco que precisa ser entregado ao cliente
                            printf("Devolva o Troco de: R$ %.2f \n", troco);

                            // Calcula o que foi gastado no dia
                            totalDia = totalDia + total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no hist�rico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;
                            break;
                        }

                        // Se o usu�rio gastou mais que R$ 50.00 e menos que R$ 100.00
                        else if (total > 50 && total < 200)
                        {
                            total = total_alimentos + total_limpeza + total_padaria;
                            // C�lculo do valor do desconto
                            desconto = total * 0.1;
                            // C�lculo do valor que o cliente ir� pagar
                            total_desconto = total - desconto;
                            // Mostrando o valor que o usu�rio ir� pagar
                            printf("Valor Total (COM desconto): R$ %.2f \n\n", total_desconto);
                            // Aqui est� dizendo para o usu�rio inserir o valor recebido em dinheiro
                            printf("Insira o Valor recebido em Dinheiro: R$ ");
                            // Armazenando o valor que o usu�rio informou acima
                            scanf("%f", &valor_cliente);

                            // Condi��o que � erro que eh quando o usu�rio coloca um valor menor do que ele tem que pagar
                            if (valor_cliente < total_desconto)
                            {
                                // Informando o usuario que o valor inserido � menor que o valor a pagar
                                printf("-------------------------------------------------\n");
                                printf("O numero em Dinheiro fornecido pelo cliente eh menor que o Valor a Pagar\n"
                                       "Insira o Valor Novamente: R$ ");
                                // Aqui ficar� armazenado o novo valor que o usu�rio deu para o pagamento
                                scanf("%f", &valor_cliente);
                            }

                            // C�lculo do valor de troco
                            troco = valor_cliente - total_desconto;
                            // Informa o troco que precisa ser entregado ao cliente
                            printf("Devolva o Troco de: R$ %.2f \n", troco);
                            // Calcula o que foi gastado no dia
                            totalDia = totalDia + total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no hist�rico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;
                            break;
                        }

                        // Caso o valor total da compra seja superior a R$ 200,00
                        else if (total >= 200)
                        {
                            printf("O cliente fez uma compra superior a R$ 200.00\n");

                            // Solicita que Dona Ber� informe o desconto (percentual)
                            do
                            {
                                printf("Dona Bere, informe o percentual de desconto (ex: 10 para 10%%): ");
                                // Garante que o usu�rio digite um n�mero v�lido ao escolher a op��o no menu
                                if (scanf("%f", &descontoDaBere) != 1 || descontoDaBere < 0 || descontoDaBere > 100) {
                                    printf("\033[31mValor invalido. Informe um numero entre 0 e 100.\033[0m\n");
                                    // Limpa o buffer de entrada caso o usu�rio digite algo inv�lido (ex: letras)
                                    while (getchar() != '\n');
                                } else {
                                    break;
                                }
                            // While (1) � como um loop que nunca termina, at� que algo dentro dele interrompa a execu��o (normalmente com 'break')
                            } while (1);

                            // Recalcula o total e aplica o desconto corretamente
                            total = total_alimentos + total_limpeza + total_padaria;
                            desconto = total * (descontoDaBere / 100.0);
                            total_desconto = total - desconto;

                            printf("Valor com %.2f%% de desconto: R$ %.2f\n", descontoDaBere, total_desconto);

                            // Solicita o valor recebido pelo cliente
                            printf("Insira o valor recebido em dinheiro: R$ ");
                            scanf("%f", &valor_cliente);

                            // Valida��o: valor deve ser suficiente
                            while (valor_cliente < total_desconto)
                            {
                                printf("\033[31mValor insuficiente. Por favor, insira novamente: R$ \033[0m");
                                scanf("%f", &valor_cliente);
                            }

                            // Calcula o troco e exibe
                            troco = valor_cliente - total_desconto;
                            printf("Troco: R$ %.2f\n", troco);

                            // Atualiza os dados financeiros do dia
                            totalDia += total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Atualiza totais por categoria
                            categorias[0] += total_limpeza;
                            categorias[1] += total_alimentos;
                            categorias[2] += total_padaria;

                            // Reseta os acumuladores para o pr�ximo cliente
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;
                            estoqueValido = 1;

                            break;
                        }

                    // Caso o usu�rio escolha a op��o de pagamento 2. Cart�o
                    case 2:

                        // Informando a forma de pagamento
                        printf("\033[35m==========================================================\n"
                                "*** Forma de pagamento escolhida: Cartao***\n"
                                "==========================================================\033[0m\n\n");

                        // Op��es que o usu�rio tem que escolher no pagamento por cart�o
                        printf("Pagamento na maquina (1. Ok ou 0. Nao Ok): ");
                        // Guarda o que o usu�rio escolheu
                        scanf("%d", &cartao);

                        // Switch do pagamento 2. Cart�o
                        switch (cartao)
                        {
                        // Caso o usu�rio escolha a op��o de pagamento 1. Ok
                        case 1:
                            total = total_alimentos + total_limpeza + total_padaria;
                            // C�lculo do total vendido que aparecer� no hist�rico
                            totalDia += total;
                            saldoFinal = totalDia + saldoInicial;
                            // Exibindo que o pagamento foi conclu�do
                            printf("\033[32mPagamento realizado com sucesso! :D \n"
                                   "O valor pago foi de\033[0m: R$ %.2f \n",
                                   total);

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no hist�rico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;

                            // Faz o case 1 parar
                            break;

                        // Caso o usu�rio escolha a op��o de pagamento 0. N�o Ok
                        case 0:
                            // Exibindo que o pagamento deu errado
                            printf("\033[31mPagamento deu erro! Tente outra forma de pagamento :( \033[0m\n");
                            // Aqui vai fazer ele voltar para o usu�rio escolher a forma de pagamento novamente
                            continue;
                        } // Fecha switch cartao
                        break;

                    // Caso o usu�rio n�o escolha nenhuma das op��es listadas
                    default:
                        printf("\033[31m*** Escolha invalida ***\033[0m\n");
                        continue;
                    }
                    break; // fecha o switch de  pagamento

                    // Aqui encera o Do While do cartao ele faz voltar na escolha do pagamento
                } while (cartao == 0);

                menuPrincipal();
                while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                    printf("Por favor, informe somente numeros: >> ");
                    while(getchar() != '\n');
                }

            // Caso o usu�rio escolha a op��o 6. Fechamento de Caixa
            case 6:
                // Se o usu�rio pagar corretamente
                if (estoqueValido == 1)
                {
                    avisoValoresFinais();
                    mostraFinalDia();
                    troco = 0;
                    diaFinalizado();
                }
                // Se o usu�rio n�o pagar o valor correto ou sair sem pagar
                else
                {
                    avisoDeRoubo();
                    menuPrincipal();
                    scanf("%d", &escolhaDoMenuPrincipal);
                }
                break;

            // Exibe mensagem de encerramento e finaliza o sistema imediatamente
            case 7:
                printf("\033[31m *** Sistema encerrado ***\033[0m\n");
                // O programa termina na hora com sucesso (sem erro)
                exit(0);
            }
        }
    } while (escolhaDoMenuPrincipal != 8);
    return 0;
}

// Fun��o que mostra o Menu Principal
int menuPrincipal()
{
    // Exibe o Menu Principal
    printf("\033[35m===================================================\n");
    printf("*** Menu Principal ***\n");
    printf("===================================================\033[0m\n\n");

    printf("1. Abertura de Caixa\n"
           "2. Material de Limpeza\n"
           "3. Venda de Alimentos\n"
           "4. Padaria\n"
           "5. Pagamento\n"
           "6. Fechamento do Caixa\n"
           "7. Sair\n\n");

    // Aqui o usu�rio escolhe a op��o do Menu Principal
    printf("Digite o numero da categoria: ");
    return 0;
}

// Fun��o que mostra os produtos da categoria 2. Material de Limpeza
int categoriaMaterialDeLimpeza()
{
    // Fun��o que exibe o t�tulo da categoria 2. Material de Limpeza
    tituloCategoriaLimpeza();
    // Produtos da categoria 2. Material de Limpeza
    printf("11 - Detergente - R$ 1.99 - Estoque: %d\n"
           "12 - Sabao em Po (1 kg) - R$ 8.99 - Estoque: %d\n"
           "13 - Esponja - R$ 1.50 - Estoque: %d\n"
           "14 - Amaciante (1 L) - R$ 15.00 - Estoque: %d\n"
           "15 - Bucha de Pia (kit c/3) - R$ 4.99 - Estoque: %d\n"
           "16 - Desinfetante (1 L) - R$ 7.99 - Estoque: %d\n"
           "17 - Sabao em Barra (unidade) - R$ 1.00 - Estoque: %d\n"
           "18 - Voltar ao Menu Principal\n\n", estoqueLimpeza[0], estoqueLimpeza[1], estoqueLimpeza[2], estoqueLimpeza[3], estoqueLimpeza[4], estoqueLimpeza[5], estoqueLimpeza[6]);

    // O usu�rio escolhe o produto atrav�s do c�digo
    printf("Digite o codigo do produto: ");
    return 0;
}

// Fun��o que mostra os produtos da categoria 3. Venda de Alimentos
int categoriaVendaDeAlimentos()
{
    // Fun��o que exibe o t�tulo da categoria 3. Venda de Alimentos
    tituloCategoriaAlimentos();
    // Produtos da categoria 3. Venda de Alimentos
    printf("21 - Cafe (500 mg) - R$ 19.99 - Estoque: %d\n"
           "22 - Leite (caixinha) - R$ 5.90 - Estoque: %d\n"
           "23 - Arroz (1 kg) - R$ 4.50 - Estoque: %d\n"
           "24 - Feijao Preto (1kg) - R$ 8.00 - Estoque: %d\n"
           "25 - Acucar (1 kg) - R$ 5.00 - Estoque: %d\n"
           "26 - Sal (1 kg) - R$ 2.00 - Estoque: %d\n"
           "27 - Farinha de Trigo (1 kg) R$ 5.00 - Estoque: %d\n"
           "28 - Voltar ao Menu Principal\n\n", estoquealimentos[0], estoquealimentos[1], estoquealimentos[2], estoquealimentos[3], estoquealimentos[4], estoquealimentos[5], estoquealimentos[6]);

    // O usu�rio escolhe o produto atrav�s do c�digo
    printf("Digite o codigo do produto: ");
    return 0;
}

// Fun��o que mostra os produtos da categoria 4. Padaria
int categoriaPadaria()
{
    // Fun��o que exibe o t�tulo da categoria 4. Padaria
    tituloCategoriaPadaria();
    // Produtos da categoria 4. Padaria
    printf("31 - Pao de Forma (pacote) - R$ 9.50\n"
           "32 - Pao Integral (pacote) - R$ 12.50\n"
           "33 - Pao Frances (unidade) - R$ 1.90\n"
           "34 - Sonho (unidade) - R$ 8.50\n"
           "35 - Biscoito (kg) - R$ 12.50\n"
           "36 - Pao Doce (unidade) - R$ 2.50\n"
           "37 - Salgado (unidade) - R$ 17.50\n"
           "38 - Voltar ao Menu Principal\n\n");

    // O usu�rio escolhe o produto atrav�s do c�digo
    printf("Digite o codigo do produto: ");
    return 0;
}

// Fun��o que faz toda as etapas de comprar os produtos da categoria funcionarem
int comprarProdutosLimpeza(float valorDoProduto)
{

    // Solicita a quantidade do produto
    printf("Informe a quantidade do produto: ");
    // Guarda a escolha do usu�rio
    while(scanf("%d", &quantidade) != 1){
                printf("Por favor, informe somente numeros: >> ");
                while(getchar() != '\n');
        }

    // Aqui come�a o Do While para tratativa de erro sobre produto negativo
    do
    {
        // Estamos observando se a quantidade informada pelo usuario foi negativa caso ela for ele entrara no IF
        if (quantidade <= 0)
        {
            // Solicita a quantidade do produto
            printf("Por favor, informe a quantidade de produto maior que 0: ");
            // Guarda a escolha do usu�rio
            while(scanf("%d", &quantidade) != 1){
                printf("Por favor, informe somente numeros: >> ");
                while(getchar() != '\n');
            }

        }
        // Encerramento do Do While para ver se a quantidade for menor que 0 caso sim ele ficara em um loop
    } while (quantidade <= 0);

    // Calcula o valor que o cliente deve pagar
    valorCompra = quantidade * valorDoProduto;
    // Atualiza o total gasto na categoria 1. Material de Limpeza
    total_limpeza += valorCompra;
    // Quebra de linha
    printf("\n");
    // Pergunta se o usu�rio quer adicionar mais produtos dessa categoria
    printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
    // Aqui ficar� armazenda o valor que o usu�rio digitar
    scanf("%s", &compra);
    while (compra != 's' && compra != 'n')
    {
        printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
        // Aqui ficar� armazenda o valor que o usu�rio digitar
        scanf("%s", &compra);
    }
    // Quebra de linha
    printf("\n");
    // Aqui tem um auxiliar para guardar o valor da quantidade de produtos vendidos
    quantProdVendidos += quantidade;
    return valorDoProduto;
}

// Fun��o que faz toda as etapas de comprar os produtos da categoria funcionarem
int comprarProdutosAlimento(float valorDoProduto)
{
    printf("Informe a quantidade do produto: ");
    // Guarda a escolha do usu�rio
    while(scanf("%d", &quantidade) != 1){
        printf("Por favor, informe somente numeros: >> ");
        while(getchar() != '\n');
    }

    // Aqui come�a o Do While para tratativa de erro sobre produto negativo
    do
    {
        // Estamos observando se a quantidade informada pelo usuario foi negativa caso ela for ele entrara no IF
        if (quantidade <= 0)
        {
            printf("Por favor, informe um numero ou a quantidade de produto maior que 0: ");
            // Guarda a escolha do usu�rio
            while(scanf("%d", &quantidade) != 1){
                printf("Por favor, informe somente numeros: >> ");
                while(getchar() != '\n');
            }
        }
        // Encerramento do Do While para ver se a quantidade for menor que 0 caso sim ele ficara em um loop
    } while (quantidade <= 0);
    // Calcula o valor que o cliente deve pagar
    valorCompra = quantidade * valorDoProduto;
    // Atualiza o total gasto na categoria 2. Venda de Alimentos
    total_alimentos += valorCompra;
    // Quebra de linha
    printf("\n");
    // Pergunta se o usu�rio quer adicionar mais produtos dessa categoria
    printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
    // Aqui ficara armazenda o valor que o usu�rio digitar
    scanf(" %s", &compra);
    while (compra != 's' && compra != 'n')
    {
        printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
        // Aqui ficar� armazenda o valor que o usu�rio digitar
        scanf("%s", &compra);
    }
    // Quebra de linha
    printf("\n");
    // Aqui tem um auxiliar para guardar o valor da quantidade de produto vendido
    quantProdVendidos += quantidade;
    return valorDoProduto;
}

// Fun��o que faz toda as etapas de comprar os produtos da categoria funcionarem
int comprarProdutosPadaria(float valorDoProduto)
{
    // Solicita a quantidade do produto
    printf("Informe a quantidade do produto: ");
    // Guarda a escolha do usu�rio
    while(scanf("%d", &quantidade) != 1){
        printf("Por favor, informe somente numeros: >> ");
        while(getchar() != '\n');
    }

    // Aqui come�a o Do While para tratativa de erro sobre produto negativo
    do
    {
        // Estamos observando se a quantidade informada pelo usuario foi negativa caso ela for ele entrara no IF
        if (quantidade <= 0)
        {
            // Solicita a quantidade do produto
            printf("Por favor, informe a quantidade de produto maior que 0: ");
            // Guarda a escolha do usu�rio
            while(scanf("%d", &quantidade) != 1){
                printf("Por favor, informe somente numeros: >> ");
                while(getchar() != '\n');
            }
        }
        // Encerramento do Do While para ver se a quantidade for menor que 0 caso sim ele ficara em um loop
    } while (quantidade <= 0);

    // Calcula o valor que o cliente deve pagar
    valorCompra = quantidade * valorDoProduto;
    // Atualiza o total gasto na categoria 1. Material de Limpeza
    total_padaria += valorCompra;
    // Quebra de linha
    printf("\n");
    // Pergunta se o usu�rio quer adicionar mais produtos dessa categoria
    printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
    // Aqui ficar� armazenda o valor que o usu�rio digitar
    scanf("%s", &compra);
    while (compra != 's' && compra != 'n')
    {
        printf("Deseja adicionar mais produtos? Digite S para Sim ou N para Nao: ");
        // Aqui ficar� armazenda o valor que o usu�rio digitar
        scanf("%s", &compra);
    }
    // Quebra de linha
    printf("\n");
    // Aqui tem um auxiliar para guardar o valor da quantidade de produtos vendidos
    quantProdVendidos += quantidade;
    return valorDoProduto;
}

// Fun��o que mostra as op��es de pagamento
int pagamento()
{
    // Exibe o t�tulo da categoria 5. Pagamento
    printf("\033[35m=====================================================\n"
            "                *** Pagamento ***\n"
            "=====================================================\033[0m\n\n");
    // Op��es em Dinheiro ou Cart�o que o usu�rio tem que escolher
    printf("1. Dinheiro \n"
           "2. Cartao\n\n");

    // O usu�rio escolhe a forma de pagamento
    printf("Escolha forma de pagamento (1. Dinheiro ou 2. Cartao): ");
    return 0;
}

// Fun��o que mostra o aviso de permanecer ou n�o na categoria escolhida pelo usu�rio
int continuarCompra()
{
    // Deixando o menu mais agrad�vel para o usu�rio interagir
    printf("\033[35m===================================================\n");
    printf("*** Voltar ao Menu Principal ***\n");
    printf("===================================================\033[0m\n\n");
    // Mostrando para o usuario se ele quer permanecer ou n�o da categoria que escolheu
    printf("Deseja permanecer nessa categoria? Digite N para sair ou S para permanecer: ");
    // Guarda a escolha do usu�rio
    scanf(" %c", &compra);
    return 0;
}

// Fun��o de aviso para o usu�rio iniciar apenas com o 1. Abertura de Caixa
int avisoAberturaDeCaixa()
{
    printf("\033[31m============================================================================================\033[0m\n");
    printf("\033[33m*** Para iniciar o dia, sera necessario a abertura de caixa! ***\033[0m\n");
    printf("\033[31m============================================================================================\033[0m\n");
}

// Fun��o que exibe o t�tulo da categoria 2. Material de Limpeza
int tituloCategoriaLimpeza()
{
    printf("\033[34m===================================================\n");
    printf("*** 2. Material de Limpeza ***\n");
    printf("===================================================\033[0m\n\n");
}

// Fun��o que exibe o t�tulo da categoria 3. Venda de Alimentos
int tituloCategoriaAlimentos()
{
    printf("\033[33m===================================================\n");
    printf("*** 3. Venda de Alimentos ***\n");
    printf("===================================================\033[0m\n\n");
}

// Fun��o que exibe o t�tulo da categoria 4. Padaria
int tituloCategoriaPadaria()
{
    printf("\033[36m===================================================\n");
    printf("*** 4. Padaria ***\n");
    printf("===================================================\033[0m\n\n");
}

// Fun��o que exibe a forma de pagamento escolhida pelo usu�rio 1. Dinheiro
int avisoPagamento()
{
    printf("\033[35m==============================================================\n"
            "*** Forma de pagamento escolhida: Dinheiro ***\n"
            "==============================================================\n\n\033[0m");
}

// Fun��o que exibe a quantidade em dinheiro que o caixa foi aberto
int avisoSaldoInicial()
{
    printf("\033[35m======================================================\n");
    printf("O caixa foi aberto com o total de: R$ %.2f \n", saldoInicial);
    printf("======================================================\033[0m\n");
}

// Fun��o que exibe que o item espec�fico n�o tem no estoque
int faltaProdutoNoEstoque()
{
    printf("\033[31m===================\033[0m \033[33mATENCAO\033[0m \033[31m===================\033[0m\n\n"
           "\033[31mProduto sem estoque! Por favor, selecione outro item\033[0m\n\n");
}

// Fun��o que exibe para o usu�rio digitar apenas n�meros, e n�o palavras
int avisoPalavra()
{
    printf("\033[31m=====================================================================\n");
    printf("Nao eh possivel digitar letra. Por favor, insira um numero: \n");
    printf("=====================================================================\033[0m\n\n");
}

// Fun��o que exibe o aviso de fechamento do dia
int diaFinalizado()
{
    while (escolhaDoMenuPrincipal != 1)
    {
        avisoDoDia();
        avisoAberturaDeCaixa();
        menuPrincipal();
        while (scanf("%d", &escolhaDoMenuPrincipal) != 1)
        {
            avisoPalavra();
            menuPrincipal();
            while (getchar() != '\n');
        }
        saldoFinal = (totalDia + saldoInicial) - troco;
        quantProdVendidos = 0;
        foiAbertoHoje = 0;
        totalDia = 0;
    }
}

// Fun��o que exibe o t�tulo de Venda e Faturamento
int avisoValoresFinais()
{
    printf("\033[35m=================================================\n");
    printf("*** Quantidade de Vendas e Faturamento ***\n");
    printf("=================================================\033[0m\n\n");
}

// Fun��o que exibe o hist�rico do dia
int mostraFinalDia()
{
    // Conta que indica o saldo final do dia
    saldoFinal = (totalDia + saldoInicial - troco);
    // Hist�rico da quantidades de produtos vendidos e das vendas
    printf("Valor de Abertura de Caixa: %.2f\n", saldoInicial);
    printf("Lucro do Dia: %.2f\n", totalDia);
    printf("Quantidade de produtos vendidos - Total: %d\n", quantProdVendidos);
    printf("Valor total do Fechamento de Caixa: %.2f\n\n", saldoFinal);
    printf("\033[32m*** DIA FINALIZADO! ***	\033[0m\n\n\n");
    i++;
}

// Fun��o que exibe qual dia �
int avisoDoDia()
{
    printf("==========================\n");
    printf("Day Number: %d\n", i);
    printf("==========================\n\n");
}

// Fun��o que exibe o aviso de que o caixa foi aberto abaixo do saldo m�nimo
int avisoValorMinimo()
{
    printf("\033[35m=================================================\n");
    printf("*** O CAIXA FOI ABERTO ABAIXO DO SALDO MINIMO ***\n");
    printf("=================================================\033[0m\n");
}

// Fun��o que exibe um aviso caso o usu�rio escolha um valor menor que o m�nimo para iniciar a abertura de caixa
int avisoParaBere()
{
    printf("\n\033[31m=================== \033[33mATENCAO\033[0m\033[31m ===================\033[0m\n");
    printf("\033[38m\nVoce esta abrindo o caixa com a valor a baixo do minimo que eh: R$ 200.00\n"
            "Tem certeza em abrir o caixa abaixo do valor minimo?\n\n"
            "Digite S para entrar com o Saldo Inferior ao Minimo ou N para inserir outro valor: >> \033[0m");
}

// Fun��o que exibe que o caixa foi aberto
int avisoAbrindoCaixa()
{
    printf("\033[35m======================================\n"
            "*** Realizando a Abertura do Caixa ***\n"
            "======================================\033[0m\n");
}

// Fun��o que exibe um aviso que o cliente n�o pode sair sem finalizar o pagamento
int avisoDeRoubo()
{
    printf("\033[31m===================\033[0m \033[33mATENCAO\033[0m \033[31m===================\033[0m\n\n"
           "Nao eh possivel fechar o dia. Pois tem item para finalizar pagamento\n\n");
}

// Fun��o que exibe um aviso para o usu�rio inserir novamente o saldo inicial do caixa
int adicionarNovoSaldoInicial()
{
    printf("Insira novamente o Saldo Inicial do Caixa: R$  ");
    while (scanf("%f", &saldoInicial) != 1)
    {
        while (getchar() != '\n');
    }
}
