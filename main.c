#include <stdio.h>
#include <stdlib.h>
//+-----------------------------------------------+
//|   Ferramenta para tradução do game Ringworld. |
//|                                               |
//|   A versão ALPHA(0.8.1) atual faz somente a   |
//| retirada dos dados do arquivo "RING.RLB".     |
//|                                               |
//+-----------------------------------------------+
//
// Dados relevantes para entendimento do código:
//
// Início de string: (tag*)TEXT(NULL)
// tag1: S Q M H C P E O
// tag2: FL SK PO
// tag3: CHF CDR BAT
// tag4: GAME
//
// Códigos desconhecidos(2): CR SL QR QU ML PR
// Códigos desconhecidos(3): CDR FLL POR
// Códigos desconhecidos(4): CHFL
//

// Caracteres especiais.
char n =	'\n';	// Quebra de linha.

//  Método que imprime uma string no arquivo, além de atualizar a posição
//da referência passada por parâmetro ("pos").
void printar_linha_na_saida(FILE *arquivo, char *buffer, unsigned int *pos)
{
    while (buffer[*pos] != '\0')
    {
        fputc((int)buffer[*pos], arquivo);
        *pos += 1;
    }

    *pos += 1;
    fputc((int)n, arquivo);
    fputc((int)n, arquivo);
    fputc((int)n, arquivo);
}

int main()
{
    FILE *entrada, *saida;	// Arquivos de entrada e saída.
    char *b;				// Ponteiro para buffer.
    unsigned int fim, pos;	// Referências para índices de acesso.

    // Abre o arquivo com os dados e cria o de tradução.
    entrada = fopen("RING.RLB", "rb");
    saida = fopen("TRADUÇÃO.txt", "w");

    // Exeção para caso não exista um "RING.RLB" na pasta do programa.
    if (entrada == NULL)
    {
        printf("\nErro ao abrir o arquivo \"RING.RLB\"!\n\n");
        return 0;
    }

    // Carrega o arquivo para a memória.
    fseek(entrada, 0, SEEK_END);    // Vai para o fim do arquivo.
    fim = ftell(entrada);           // Pega a posição final (tamanho do arquivo).
    fseek(entrada, 0, SEEK_SET);    // Vai para o início do arquivo.
    b = (char*)malloc(fim);                // Aloca memória dinâmica para os dados.
    fread(b, fim, 1, entrada);      // Coloca os dados no espaço alocado.
    fclose(entrada);                // Fecha o arquivo.

    // Laço para varrer todo o arquivo.
    for (pos = 0; pos < fim;)
    {
        // Começa o processo caso encontrado um "TEXT" e depois um NULL.
        if (b[pos] == 'T' && b[pos + 1] == 'E' && b[pos + 2] == 'X' && b[pos + 3] == 'T' && b[pos + 4] == '\0')
        {
            pos += 5;

            while (1)
            {
                printar_linha_na_saida(saida, b, &pos);

                // Teste para caso tenha um código desconhecido(2) após a última string.
                if (b[pos + 2] == '\0')
                {
                    pos += 3;
                    continue;
                }
                // Teste para caso tenha um código desconhecido(3) após a última string.
                if (b[pos + 3] == '\0')
                {
                    pos += 4;
                    continue;
                }
                // Teste para caso tenha um código desconhecido(4) após a última string.
                if (b[pos + 4] == '\0')
                {
                    pos += 5;
                    continue;
                }
                // Teste para caso tenha um "TMI-" logo após a última string.
                if (b[pos] == 'T' && b[pos + 1] == 'M' && b[pos + 2] == 'I' && b[pos + 3] == '-')
				{
                    break;
				}
                // Teste para caso tenha um "(tag1)TEXT" logo após a última string.
                if (b[pos + 1] == 'T' && b[pos + 2] == 'E' && b[pos + 3] == 'X' && b[pos + 4] == 'T' && b[pos + 5] == '\0')
                {
                    pos += 6;
                    continue;
                }
                // Teste para caso tenha um "(tag2)TEXT" logo após a última string.
                if (b[pos + 2] == 'T' && b[pos + 3] == 'E' && b[pos + 4] == 'X' && b[pos + 5] == 'T' && b[pos + 6] == '\0')
                {
                    pos += 7;
                    continue;
                }
                // Teste para caso tenha um "(tag3)TEXT" logo após a última string.
                if (b[pos + 3] == 'T' && b[pos + 4] == 'E' && b[pos + 5] == 'X' && b[pos + 6] == 'T' && b[pos + 7] == '\0')
                {
                    pos += 8;
                    continue;
                }
                // Teste para caso tenha um "(tag4)TEXT" logo após a última string.
                if (b[pos + 4] == 'T' && b[pos + 5] == 'E' && b[pos + 6] == 'X' && b[pos + 7] == 'T' && b[pos + 8] == '\0')
                {
                    pos += 9;
                    continue;
                }
            }
        }

        pos++;
    }
    fprintf(saida, "//Fim");
    fclose(saida);

    return 1;
}
