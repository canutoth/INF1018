/*
Julia Tadeu Neves de Azevedo - 2312392 - 3WA
Theo Jesus Canuto de Sousa   - 2311293 - 3WA
*/

#include "converteutf832.h"
#include <stdio.h>
#include <errno.h>

int numBytesUtf8p32(char byte);
void escreveBomUtf8p32(FILE* arquivo_saida);
int verificar_bomUtf32p8(FILE* arquivo);
int ler_utf32(FILE* arq_entrada, int bom);
void escrever_utf8(FILE* arquivo_saida, int c);

// Funcao para converter UTF-8 para UTF-32
// 1 byte (0xxxxxxx):
// ASCII (so escrever)
// 2 bytes (110xxxxx 10xxxxxx):
// decodifica os 5 bits do primeiro byte e 6 bits dos demais.
// 3 bytes (1110xxxx 10xxxxxx 10xxxxxx):
// decodifica 4 bits do primeiro byte, 6 bits dos demais.
// 4 bytes (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx):
// decodifica 3 bits do primeiro byte, 6 bits dos demais.
// & extrai os bits relevantes de cada byte
// | combina os bits de todos os bytes

int convUtf8p32(FILE* arquivo_entrada, FILE* arquivo_saida) {
    int c, aux, numBytes;

    if (arquivo_entrada == NULL) {
        perror("Erro de Leitura :( ");
        return -1;
    }

    escreveBomUtf8p32(arquivo_saida);

    while ((c = getc(arquivo_entrada)) != EOF) {
        numBytes = numBytesUtf8p32(c);
        aux = c;

        if (numBytes == 1) {
            aux = c;
        }
        else if (numBytes == 2) {
            aux = (c & 0x1F) << 6;
            aux |= (getc(arquivo_entrada) & 0x3F);
        }
        else if (numBytes == 3) {
            aux = (c & 0x0F) << 12;
            aux |= (getc(arquivo_entrada) & 0x3F) << 6;
            aux |= (getc(arquivo_entrada) & 0x3F);
        }
        else if (numBytes == 4) {
            aux = (c & 0x07) << 18;
            aux |= (getc(arquivo_entrada) & 0x3F) << 12;
            aux |= (getc(arquivo_entrada) & 0x3F) << 6;
            aux |= (getc(arquivo_entrada) & 0x3F);
        }

        fputc(aux & 0xFF, arquivo_saida);
        fputc((aux >> 8) & 0xFF, arquivo_saida);
        fputc((aux >> 16) & 0xFF, arquivo_saida);
        fputc((aux >> 24) & 0xFF, arquivo_saida);

        if (ferror(arquivo_saida)) {
            perror("Erro de gravacao :( ");
            return -1;
        }
    }

    return 0;
}

// Funcao para converter UTF-32 para UTF-8
// 1 byte (xxxxxxxx):
// decodifica diretamente no UTF-8, escrevendo o byte unico.
// 2 bytes (xxxxxxxx xxxxxxxx):
// extrai e escreve o primeiro byte (110xxxxx) e o segundo (10xxxxxx).
// 3 bytes (xxxxxxxx xxxxxxxx xxxxxxxx):
// extrai e escreve os 3 bytes (1110xxxx 10xxxxxx 10xxxxxx).
// 4 bytes (xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx):
// extrai e escreve os 4 bytes (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx).

int convUtf32p8(FILE* arq_entrada, FILE* arq_saida) {
    int bom, c;

    if (arq_entrada == NULL) {
        perror("Erro de leitura :( ");
        return -1;
    }

    bom = verificar_bomUtf32p8(arq_entrada);
    if (bom == -1) {
        printf("Erro de BOM :( "); // printf e nao perror como no restante do codigo pois nao e um erro do sistema, e sim de uma demanda personalizada do codigo/funcao
        return -1;
    }

    while ((c = ler_utf32(arq_entrada, bom)) != EOF) {
        escrever_utf8(arq_saida, c);

        if (ferror(arq_saida)) {
            perror("Erro de gravacao :( ");
            return -1;
        }
    }

    return 0;
}

int numBytesUtf8p32(char byte) {
    unsigned char a = byte;

    if ((a & 0x80) == 0x00) return 1;
    else if ((a & 0xE0) == 0xC0) return 2;
    else if ((a & 0xF0) == 0xE0) return 3;
    else return 4;
}

void escreveBomUtf8p32(FILE* arquivo_saida) {
    fputc(0xFF, arquivo_saida);
    fputc(0xFE, arquivo_saida);
    fputc(0x00, arquivo_saida);
    fputc(0x00, arquivo_saida);
}

int verificar_bomUtf32p8(FILE* arquivo) {
    int bom = 0;
    bom |= getc(arquivo) << 24;
    bom |= getc(arquivo) << 16;
    bom |= getc(arquivo) << 8;
    bom |= getc(arquivo);

    if (bom == 0xFFFE0000) return 1;  // Big-endian
    if (bom == 0x0000FEFF) return 0;  // Little-endian
    return -1;  // BOM invalido
}

int ler_utf32(FILE* arq_entrada, int bom) {
    int c = getc(arq_entrada);

    if (c == EOF) {
        return EOF;
    }

    // Big-endian
    if (bom == 1) {
        c |= getc(arq_entrada) << 8;
        c |= getc(arq_entrada) << 16;
        c |= getc(arq_entrada) << 24;
    }
    // Little-endian
    else {
        c = c << 24;
        c |= getc(arq_entrada) << 16;
        c |= getc(arq_entrada) << 8;
        c |= getc(arq_entrada);
    }

    return c;
}

void escrever_utf8(FILE* arquivo_saida, int c) {
    int aux;

    if (c >= 0x10000 && c <= 0x10FFFF) {  // 4 bytes
        aux = (c >> 18 | 0xF0) & 0xFF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c >> 12 | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c >> 6 | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
    }
    else if (c >= 0x800 && c <= 0xFFFF) {  // 3 bytes
        aux = (c >> 12 | 0xE0) & 0xFF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c >> 6 | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
    }
    else if (c >= 0x80 && c <= 0x7FF) {  // 2 bytes
        aux = (c >> 6 | 0xC0) & 0xFF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
        aux = (c | 0x80) & 0xBF;
        fwrite(&aux, 1, sizeof(char), arquivo_saida);
    }
    else {  // 1 byte
        fwrite(&c, 1, sizeof(char), arquivo_saida);
    }
}
