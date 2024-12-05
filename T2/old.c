#include <stdio.h>
#include "cria_func.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]){
    int i = 0;
    unsigned char pegaParam [] = {0x7d, 0x75, 0x55};
    printf("%d\n", params[0].tipo_val);
    printf("%d\n", params[0].orig_val);
    printf("%d\n", params[1].tipo_val);
    printf("%d\n", params[1].orig_val);
    
    // prologo padrao
    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    // pega 32 bytes pra pilha
    codigo[i++] = 0x48;
    codigo[i++] = 0x83;
    codigo[i++] = 0xec;
    codigo[i++] = 0x20;

    // salvando %rdi
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0x7d;
    codigo[i++] = 0xf8;
    
    // salvando  %rsi
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0x75;
    codigo[i++] = 0xf0;

    // salvando %rdx
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0x55;
    codigo[i++] = 0xe8;

    // logica do PARAM. se ele nao tem nenhum param ainda, guardar no 1, se tem 1 guarda no 2, se tem 2 guarda no 3
    unsigned int qtdPARAM = 0; 
    
    for (int j = 0; j < n; j ++){
        if (params[j].orig_val == 1) { // FIX
            // se for inteiro
            if (params[j].tipo_val == 0){
                // movl valor, registrador inteiro
                printf("%d", params[j].valor.v_int);
                // codigo[i++] = 0xbf; // muda
                if (j==0){
                    //%edi
                    codigo[i++] = 0xbf;
                }
                else if (j==1){
                    // %esi
                    codigo[i++] = 0xbe;
                }
                else {
                    // %edx
                    codigo[i++] = 0xba;

                }
                codigo[i++] = (params[j].valor.v_int & 0xff);
                codigo[i++] = (params[j].valor.v_int >> 8) & 0xff;
                codigo[i++] = (params[j].valor.v_int >> 16) & 0xff;
                codigo[i++] = (params[j].valor.v_int >> 24) & 0xff;
            }
            // se for ponteiro
            else {
                // movq ponteiro-passado, %rdi
                // instrucoes de um movq de um endereco fixo pra %rdi
                codigo[i++] = 0x48;
                // codigo[i++] = 0xbf; // muda
                if (j==0){
                    //%edi
                    codigo[i++] = 0xbf;
                }
                else if (j==1){
                    // %esi
                    codigo[i++] = 0xbe;
                }
                else {
                    // %edx
                    codigo[i++] = 0xba;
                }
                // endereco em si
                uintptr_t endereco_v_ptr = (uintptr_t)params[j].valor.v_ptr;
                // transformar em little endian
                for (int l = 0; l < 8; l++) {
                    codigo[i++] = (endereco_v_ptr >> (l * 8)) & 0xff;
                }
                
            }
        }
        else if (params[j].orig_val == 2){ // IND
            // se for inteiro
            if (params[j].tipo_val == 0){
                // movq endereco, %r8
                codigo[i++] = 0x49;
                codigo[i++] = 0xb8;
                //fprintf(stderr, "DEGUB %d -- %p\n", __LINE__, params[j].valor.v_ptr);
                memcpy(&codigo[i], &params[j].valor.v_ptr, sizeof(void *));
                i += sizeof(void *);

                // movl (%r8), %edi
                codigo[i++] = 0x41;
                codigo[i++] = 0x8b;
                // codigo[i++] = 0x38; // muda
                if (j==0){
                    //%edi
                    codigo[i++] = 0x38;
                }
                else if (j==1){
                    // %esi
                    codigo[i++] = 0x30;
                }
                else {
                    // %edx
                    codigo[i++] = 0x10;
                }
            }
            // se for ponteiro
            else { // PTR_PAR
                // movq endereco, %r8
                codigo[i++] = 0x49;
                codigo[i++] = 0xb8;
                memcpy(&codigo[i], params[j].valor.v_ptr, sizeof(void *));
                i += sizeof(void *);

                // movq %r8, %rdi
                codigo[i++] = 0x4c;
                codigo[i++] = 0x89;
                // codigo[i++] = 0xc7; // muda
                if (j==0){
                    //%rdi
                    codigo[i++] = 0xc7;
                }
                else if (j==1){
                    // %rsi
                    codigo[i++] = 0xc6;
                }
                else {
                    // %rdx
                    codigo[i++] = 0xc2;
                }
            }
        }
        else { // PARAM * pausa dramatica * (PAM PAM PAAAAAAM)
            printf("%d\n", params[j].tipo_val);
            printf("%d\n", params[j].orig_val);
            // se for inteiro
            if (params[j].tipo_val == 0){

                codigo[i++] = 0x8b;
                codigo[i++] = pegaParam[j];

                if (qtdPARAM==0){
                    // -8(%rbp)
                    codigo[i++] = 0xf8;

                }
                else if (qtdPARAM==1){
                    // -16(%rbp)
                    codigo[i++] = 0xf0;
                }
                else {
                    // -24(%rbp)
                    codigo[i++] = 0xe8;
                }
            }
            // se for ponteiro
            else {

                codigo[i++] = 0x48;
                codigo[i++] = 0x8b;

                codigo[i++] = pegaParam[j];

                if (qtdPARAM==0){
                    // -8(%rbp)
                    codigo[i++] = 0xf8;
                }
                else if (qtdPARAM==1){
                    // -16(%rbp)
                    codigo[i++] = 0xf0;
                }
                else {
                    // -24(%rbp)
                    codigo[i++] = 0xe8;
                }               
            }
            qtdPARAM ++;
        }
    }

    // movq endereco da funcao f, %rax
    codigo[i++] = 0x48;
    codigo[i++] = 0xb8;
    memcpy(&codigo[i], &f, sizeof(void *));
    i += sizeof(void *);

    // call *%rax
    codigo[i++] = 0xff;
    codigo[i++] = 0xd0;

    // final padrao
    codigo[i++] = 0xc9;
    codigo[i++] = 0xc3;

    for (int k = 0; k < i; k++) {
        printf("%02x\t", codigo[k]);
    }
    printf("\n");

    return;
}