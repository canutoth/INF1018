/*
Julia Tadeu Neves de Azevedo - 2312392 - 3WA
Theo Jesus Canuto de Sousa   - 2311293 - 3WA
*/

#include <stdio.h>
#include "cria_func.h"
#include <string.h>
#include <stdint.h>

#define TAM_BYTEePTR 8
#define MASCARA 0xff
#define TAM_INT 4

// enum tipo_val 0 ponteiro, 1 int
// enum orig_val 0 param, 1 fix, 2 ind

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]){
    int i = 0;
    unsigned char FIX [] = {0xbf, 0xbe, 0xba};
    unsigned char IND [] = {0x38, 0x30, 0x10};
    unsigned char PARAM_PILHA_BYTES [] = {0xf8, 0xf0, 0xe8};
    unsigned char PARAM_PILHA_REG [] = {0x7d, 0x75, 0x55};
    unsigned char inicio[] = {
        0x55, 0x48, 0x89, 0xe5,  // inicio padrao
        0x48, 0x83, 0xec, 0x20,  // 32 bytes pra pilha
        0x48, 0x89, 0x7d, 0xf8,  // %rdi na pilha
        0x48, 0x89, 0x75, 0xf0,  // %rsi na pilha
        0x48, 0x89, 0x55, 0xe8   // %rdx na pilha
    };
    memcpy(codigo, inicio, sizeof(inicio));
    i += sizeof(inicio);

    // logica PARAM
    // se ele nao tem PARAM ainda, guardar no r/edi
    // se tem 1 guardar no r/esi
    // se tem 2 guardar no r/edx
    int qtdPARAM = 0; 
    
    for (int j = 0; j < n; j ++){
        if (params[j].orig_val == 1) { // FIX
            if (params[j].tipo_val){
                // instrucoes de um movq de um endereco fixo pra reg 64bits
                codigo[i++] = 0x48;
                codigo[i++] = FIX[j];
                // endereco em little endian:
                uintptr_t endereco_v_ptr = (uintptr_t)params[j].valor.v_ptr;
                for (int k = 0; k < TAM_BYTEePTR; k++) {
                    codigo[i++] = (endereco_v_ptr >> (k * TAM_BYTEePTR)) &MASCARA;
                }
            }
            else {
                codigo[i++] = FIX[j]; // movl de um valor fixo pra reg 32bits
                // valor em little endian:
                for (int k = 0; k < TAM_INT; k++) {
                    codigo[i++] = (params[j].valor.v_int >> (k * TAM_BYTEePTR)) &MASCARA;
                }
                
            }
        }
        else if (params[j].orig_val == 2){ // IND
            // movq de um endereco fixo pra %r8
            codigo[i++] = 0x49;
            codigo[i++] = 0xb8;

            memcpy(&codigo[i], &params[j].valor.v_ptr, sizeof(void *));
            i += sizeof(void *);
            
            if (params[j].tipo_val){
                // movq de (%r8) pra reg 64bits
                codigo[i++] = 0x49;
            }
            else {
                // movl (%r8) pra reg 32bits
                codigo[i++] = 0x41;
            }
            codigo[i++] = 0x8b;
            codigo[i++] = IND[j];
        }
        else { // PARAM
            // instrucao que nao tem em inteiro se for ponteiro
            if (params[j].tipo_val){
                codigo[i++] = 0x48;         
            }
            codigo[i++] = 0x8b;
            codigo[i++] = PARAM_PILHA_REG[j];
            codigo[i++] = PARAM_PILHA_BYTES[qtdPARAM];
            qtdPARAM ++;
        }
    }

    // movq endereco da funcao f pro %rax
    codigo[i++] = 0x48;
    codigo[i++] = 0xb8;
    memcpy(&codigo[i], &f, sizeof(void *));
    i += sizeof(void *);

    unsigned char fim[] = {
        0xff, 0xd0, // call *%rax
        0xc9, // leave
        0xc3 // ret
    };
    memcpy(&codigo[i], fim, sizeof(fim));
    i += sizeof(fim);

    printf("%p\n", f);
	for (int k = 0; k < i; k++) {
        printf("%02x\t", codigo[k]);
    }
    printf("\n");

    return;
}