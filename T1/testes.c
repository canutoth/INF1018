#include "converteutf832.h"
#include <stdio.h>

int main(void) {
    FILE* teste_simbolos_8_32 = fopen("utf8_peq.txt", "rb");
    FILE* teste_peq_8_32 = fopen("utf8_textoP.txt", "rb");
    FILE* teste_grande_8_32 = fopen("utf8_textoG.txt", "rb");
    FILE* saida_simbolos_8_32 = fopen("utf32_out_peq.txt", "wb");
    FILE* saida_peq_8_32 = fopen("utf32_out_textoP.txt", "wb");
    FILE* saida_grande_8_32 = fopen("utf32_out_texto_G.txt", "wb");
    FILE* teste_bom_errado = fopen("utf32_com_bom_errado.txt", "rb");
    FILE* saida_bom_errado = fopen("utf32_out_bom_errado.txt", "wb");
    FILE* teste_peq32 = fopen("utf32_peq.txt", "rb");
    FILE* utf8_out_peq = fopen("utf8_out_peq.txt", "wb");

    convUtf32p8(teste_bom_errado, saida_bom_errado);
    convUtf32p8(teste_peq32, utf8_out_peq);
    convUtf8p32(teste_simbolos_8_32, saida_simbolos_8_32);
    convUtf8p32(teste_peq_8_32, saida_peq_8_32);
    convUtf8p32(teste_grande_8_32, saida_grande_8_32);
}
