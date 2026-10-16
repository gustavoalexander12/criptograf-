#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LETRAS 15
#define TAM_ENTRADA 256

/* Verifica se um numero e primo */
int eh_primo(int n)
{
    int i;

    if (n < 2)
        return 0;

    for (i = 2; i <= n / i; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

/* Retorna o nome da sequencia escolhida */
const char *nome_sequencia(int tipo)
{
    switch (tipo)
    {
    case 1:
        return "PA";
    case 2:
        return "PG";
    case 3:
        return "Fibonacci";
    case 4:
        return "Numeros primos";
    default:
        return "Desconhecida";
    }
}

/* Gera o termo da sequencia na posicao informada */
int sequencia(int posicao, int tipo)
{
    int i, a, b, c, numero, quantidade;

    if (tipo == 1)
    {
        /* PA: 1, 2, 3, 4... */
        return (posicao + 1) % 26;
    }

    if (tipo == 2)
    {
        /* PG: 1, 2, 4, 8, 16... */
        a = 1;

        for (i = 0; i < posicao; i++)
            a = (a * 2) % 26;

        return a;
    }

    if (tipo == 3)
    {
        /* Fibonacci: 1, 1, 2, 3, 5... */
        a = 1;
        b = 1;

        if (posicao == 0 || posicao == 1)
            return 1;

        for (i = 2; i <= posicao; i++)
        {
            c = (a + b) % 26;
            a = b;
            b = c;
        }

        return b;
    }

    /* Numeros primos: 2, 3, 5, 7, 11... */
    numero = 2;
    quantidade = 0;

    while (1)
    {
        if (eh_primo(numero))
        {
            if (quantidade == posicao)
                return numero % 26;

            quantidade++;
        }

        numero++;
    }
}

/* Le uma linha inteira e verifica se ela cabe no buffer */
int ler_linha(char texto[], int tamanho)
{
    int c;
    size_t comprimento;

    if (fgets(texto, tamanho, stdin) == NULL)
        return 0;

    comprimento = strlen(texto);

    if (comprimento > 0 && texto[comprimento - 1] == '\n')
    {
        texto[comprimento - 1] = '\0';
    }
    else
    {
        c = getchar();

        if (c != '\n' && c != EOF)
        {
            while (c != '\n' && c != EOF)
                c = getchar();

            return -1;
        }
    }

    return 1;
}

/* Le um numero inteiro, rejeitando entradas invalidas */
int ler_inteiro(const char *mensagem, int *valor)
{
    char entrada[TAM_ENTRADA];
    char extra;
    int resultado;

    printf("%s", mensagem);

    resultado = ler_linha(entrada, sizeof(entrada));

    if (resultado != 1)
        return 0;

    if (sscanf(entrada, " %d %c", valor, &extra) != 1)
        return 0;

    return 1;
}

/* Valida a palavra secreta */
int validar_palavra(const char palavra[])
{
    size_t i;
    size_t tamanho = strlen(palavra);

    if (tamanho < 1 || tamanho > MAX_LETRAS)
        return 0;

    for (i = 0; i < tamanho; i++)
    {
        if (!((palavra[i] >= 'A' && palavra[i] <= 'Z') ||
              (palavra[i] >= 'a' && palavra[i] <= 'z')))
            return 0;
    }

    return 1;
}

/* Aplica as duas camadas de criptografia ou desfaz as duas */
void transformar(char palavra[], int shift, int tipo, int codificar)
{
    int i;
    int deslocamento;
    int base;

    for (i = 0; palavra[i] != '\0'; i++)
    {
        if (palavra[i] >= 'a' && palavra[i] <= 'z')
            base = 'a';
        else
            base = 'A';

        deslocamento = (shift + sequencia(i, tipo)) % 26;

        if (!codificar)
            deslocamento = -deslocamento;

        palavra[i] =
            (char)((palavra[i] - base + deslocamento + 26) % 26 + base);
    }
}

/* Salva os dados da execucao em arquivo */
int salvar_resultado(const char palavra[], int shift, int tipo, int codificar)
{
    FILE *arquivo;
    const char *modo;

    /* Acrescenta cada execucao sem apagar os resultados anteriores */
    arquivo = fopen("resultado_criptografia.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro: nao foi possivel abrir o arquivo de resultado.\n");
        return 0;
    }

    modo = codificar ? "Criptografia" : "Descriptografia";

    fprintf(arquivo, "Operacao: %s\n", modo);
    fprintf(arquivo, "Palavra resultante: %s\n", palavra);
    fprintf(arquivo, "SHIFT: %d\n", shift);
    fprintf(arquivo, "Sequencia: %s\n", nome_sequencia(tipo));
    fprintf(arquivo, "Quantidade de letras: %d\n\n",
            (int)strlen(palavra));

    if (fclose(arquivo) != 0)
    {
        printf("Erro ao fechar o arquivo de resultado.\n");
        return 0;
    }

    printf("Resultado salvo em resultado_criptografia.txt\n");
    return 1;
}

int main(void)
{
    int opcao, shift, tipo;
    int resultado;
    char palavra[TAM_ENTRADA];

    do
    {
        printf("\n=== CRIPTOGRAFIA MATEMATICA ===\n");
        printf("1 - Criptografar\n");
        printf("2 - Descriptografar\n");
        printf("3 - Sair\n");

        if (!ler_inteiro("Escolha: ", &opcao))
        {
            printf("Entrada invalida. Digite 1, 2 ou 3.\n");
            continue;
        }

        if (opcao == 3)
            break;

        if (opcao != 1 && opcao != 2)
        {
            printf("Opcao invalida.\n");
            continue;
        }

        printf("Digite a palavra (ate 15 letras, sem acentos): ");

        resultado = ler_linha(palavra, sizeof(palavra));

        if (resultado != 1)
        {
            printf("Entrada muito longa ou erro de leitura.\n");
            continue;
        }

        if (!validar_palavra(palavra))
        {
            printf("Palavra invalida. Use de 1 a 15 letras, "
                   "sem acentos, espacos ou simbolos.\n");
            continue;
        }

        if (!ler_inteiro("Digite o SHIFT (0 a 25): ", &shift))
        {
            printf("SHIFT invalido. Digite um numero inteiro.\n");
            continue;
        }

        if (shift < 0 || shift > 25)
        {
            printf("SHIFT invalido. Use um valor de 0 a 25.\n");
            continue;
        }

        printf("\nEscolha a sequencia matematica:\n");
        printf("1 - PA\n");
        printf("2 - PG\n");
        printf("3 - Fibonacci\n");
        printf("4 - Numeros primos\n");

        if (!ler_inteiro("Opcao: ", &tipo))
        {
            printf("Entrada invalida.\n");
            continue;
        }

        if (tipo < 1 || tipo > 4)
        {
            printf("Sequencia invalida. Escolha de 1 a 4.\n");
            continue;
        }

        transformar(palavra, shift, tipo, opcao == 1);

        if (opcao == 1)
            printf("Palavra criptografada: %s\n", palavra);
        else
            printf("Palavra descriptografada: %s\n", palavra);

        salvar_resultado(palavra, shift, tipo, opcao == 1);

    } while (1);

    printf("Programa encerrado.\n");

    return 0;
}