/* Bruno Azambuja Carvalho 2310956 3WC */
/* Eduardo Eugênio de Souza 2310822 3WC */
#include "cria_func.h"
#include <stdio.h>

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    unsigned char *p = codigo;

    // Prólogo
    *p++ = 0x55;                  // push   %rbp
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xe5; // mov    %rsp, %rbp

    int numFixos = 0;
  
    // Configurar parâmetros
    for (int i = 0; i < n; i++) {
        switch (params[i].orig_val) {
            case PARAM:
              // Usar registradores na ordem rdi, rsi, rdx
              switch(numFixos){
                case 1:
                  if(i == 1){
                    if (params[i].tipo_val == INT_PAR){
                      *p++ = 0x89; *p++ = 0xfe; // mov edi para o esi
                    } else{
                      printf("A");
                      *p++ = 0x48; *p++ = 0x89; *p++ = 0xfe; // mov rdi para o rsi
                    }
                  } else if (i == 2){
                    if (params[i].tipo_val == INT_PAR){
                      *p++ = 0x89; *p++ = 0xf2; // mov esi para o edx
                    } else{
                      printf("B");

                      *p++ = 0x48; *p++ = 0x89; *p++ = 0xf2; // mov rsi para o rdx
                    }
                  }
                  break;
                case 2:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0x89; *p++ = 0xfa; // mov edi para o edx
                  } else{
                    printf("C");

                    *p++ = 0x48; *p++ = 0x89; *p++ = 0xfa; // mov rdi para o rdx
                  }
                  break;
              }
              break;
            case FIX:
              // somar numero de fixos para ajustar proximos PARAM
              numFixos++;
              break;
            case IND:
              // somar numero de fixos para ajustar proximos PARAM
              numFixos++;
              break;
        }
    }

    for (int i = 0; i < n; i++) {
        switch (params[i].orig_val) {
            case PARAM:
              //PARAM já foi lidado
              break;
            case FIX:
              // Mover valor constante para o registrador correspondente
              switch (i){
                case 0:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xbf; // mov para o edi
                  } else{
                    *p++ = 0x48; *p++ = 0xc7; *p++ = 0xc7; // moc para o rdi
                  }
                  break;
                case 1:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xbe; // mov para o esi
                  } else{
                    *p++ = 0x48; *p++ = 0xc7; *p++ = 0xc6; // mov para o rsi
                  }
                  break;

                case 2:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xba; // mov para o edx
                  } else{
                    *p++ = 0x48; *p++ = 0xc7; *p++ = 0xc2; // mov para o rdx
                  }
                  break;
              }

              if (params[i].tipo_val == INT_PAR){
                *((int *)p) = params[i].valor.v_int;  p += 4; // armazena o valor inteiro no registrador correspondente
              } else {
                *((void **)p) = params[i].valor.v_ptr;  p += 4; // armazena o endereço do ponteiro no registrador correspondente
              }

              break;
            case IND:
                // Carregar valor indireto de memória
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
