#include <stdio.h>
#include <stdlib.h>
//+-----------------------------------------------+
//|   Ferramenta para tradu��o do game Ringworld. |
//|                                               |
//|   A vers�o ALPHA(0.8.1) atual faz somente a   |
//| retirada dos dados do arquivo "RING.RLB".     |
//|                                               |
//+-----------------------------------------------+
//
// Dados relevantes para entendimento do c�digo:
//
// In�cio de string: (tag*)TEXT(NULL)
// tag1: S Q M H C P E O
// tag2: FL SK PO
// tag3: CHF CDR BAT
// tag4: GAME
//
// C�digos desconhecidos(2): CR SL QR QU ML PR
// C�digos desconhecidos(3): CDR FLL POR
// C�digos desconhecidos(4): CHFL
//

// Caracteres especiais.
char n =	'\n';	// Quebra de linha.

//  M�todo que imprime uma string no arquivo, al�m de atualizar a posi��o
//da refer�ncia passada por par�metro ("pos").
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
    FILE *entrada, *saida;	// Arquivos de entrada e sa�da.
    char *b;				// Ponteiro para buffer.
    unsigned int fim, pos;	// Refer�ncias para �ndices de acesso.

    // Abre o arquivo com os dados e cria o de tradu��o.
    entrada = fopen("RING.RLB", "rb");
    saida = fopen("TRADU��O.txt", "w");

    // Exe��o para caso n�o exista um "RING.RLB" na pasta do programa.
    if (entrada == NULL)
    {
        printf("\nErro ao abrir o arquivo \"RING.RLB\"!\n\n");
        return 0;
    }

    // Carrega o arquivo para a mem�ria.
    fseek(entrada, 0, SEEK_END);    // Vai para o fim do arquivo.
    fim = ftell(entrada);           // Pega a posi��o final (tamanho do arquivo).
    fseek(entrada, 0, SEEK_SET);    // Vai para o in�cio do arquivo.
    b = (char*)malloc(fim);                // Aloca mem�ria din�mica para os dados.
    fread(b, fim, 1, entrada);      // Coloca os dados no espa�o alocado.
    fclose(entrada);                // Fecha o arquivo.

    // La�o para varrer todo o arquivo.
    for (pos = 0; pos < fim;)
    {
        // Come�a o processo caso encontrado um "TEXT" e depois um NULL.
        if (b[pos] == 'T' && b[pos + 1] == 'E' && b[pos + 2] == 'X' && b[pos + 3] == 'T' && b[pos + 4] == '\0')
        {
            pos += 5;

            while (1)
            {
                printar_linha_na_saida(saida, b, &pos);

                // Teste para caso tenha um c�digo desconhecido(2) ap�s a �ltima string.
                if (b[pos + 2] == '\0')
                {
                    pos += 3;
                    continue;
                }
                // Teste para caso tenha um c�digo desconhecido(3) ap�s a �ltima string.
                if (b[pos + 3] == '\0')
                {
                    pos += 4;
                    continue;
                }
                // Teste para caso tenha um c�digo desconhecido(4) ap�s a �ltima string.
                if (b[pos + 4] == '\0')
                {
                    pos += 5;
                    continue;
                }
                // Teste para caso tenha um "TMI-" logo ap�s a �ltima string.
                if (b[pos] == 'T' && b[pos + 1] == 'M' && b[pos + 2] == 'I' && b[pos + 3] == '-')
				{
                    break;
				}
                // Teste para caso tenha um "(tag1)TEXT" logo ap�s a �ltima string.
                if (b[pos + 1] == 'T' && b[pos + 2] == 'E' && b[pos + 3] == 'X' && b[pos + 4] == 'T' && b[pos + 5] == '\0')
                {
                    pos += 6;
                    continue;
                }
                // Teste para caso tenha um "(tag2)TEXT" logo ap�s a �ltima string.
                if (b[pos + 2] == 'T' && b[pos + 3] == 'E' && b[pos + 4] == 'X' && b[pos + 5] == 'T' && b[pos + 6] == '\0')
                {
                    pos += 7;
                    continue;
                }
                // Teste para caso tenha um "(tag3)TEXT" logo ap�s a �ltima string.
                if (b[pos + 3] == 'T' && b[pos + 4] == 'E' && b[pos + 5] == 'X' && b[pos + 6] == 'T' && b[pos + 7] == '\0')
                {
                    pos += 8;
                    continue;
                }
                // Teste para caso tenha um "(tag4)TEXT" logo ap�s a �ltima string.
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
