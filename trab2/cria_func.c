/* Bruno Azambuja Carvalho 2310956 3WC */
/* Eduardo Eugênio de Souza 2310822 3WC */
#include "cria_func.h"
#include <stdio.h>

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    unsigned char *p = codigo;

    // Prólogo
    *p++ = 0x55;                  // push   %rbp
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xe5; // mov    %rsp, %rbp

    int num_fixos = 0; // conta a quantidade de parametros que foram fixados
    // Configurar parâmetros
    for (int i = 0; i < n; i++) {
        switch (params[i].orig_val) {
            case PARAM:
                // Usar registradores na ordem rdi, rsi, rdx
                break;
            case FIX:
              // Mover valor constante para o registrador correspondente
              num_fixos++;
              switch (i){
                case 0:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xbf; // mov para o edi
                  } else{
                    *p++ = 0x48; *p++ = 0xc7; *p++ = 0xc7;
                  }
                  break;
                case 1:
                  *p++ = 0xbe; // mov para o esi
                  break;

                case 2:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xba; // mov para o edx
                  } else{
                    *p++ = 0x48; *p++ = 0xc7; *p++ = 0xc2; // mov para o rdx
                  }
                  break;

              }
              *((int *)p) = params[i].valor.v_int;  p += 4;
              
                break;
            case IND:
                // Carregar valor indireto de memória
                num_fixos++;

                break;
        }
    }

    // Chamada à função original
    *p++ = 0x48; *p++ = 0xb8;             // mov $endereço, %rax
    *((void **)p) = f; p += 8;
    *p++ = 0xff; *p++ = 0xd0;             // call *%rax

    // Epílogo
    *p++ = 0xc9;                  // leave
    *p++ = 0xc3;                  // ret
}
