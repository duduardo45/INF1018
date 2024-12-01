/* Bruno Azambuja Carvalho 2310956 3WC */
/* Eduardo Eugênio de Souza 2310822 3WC */
#include "cria_func.h"
#include <stdio.h>

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    unsigned char *p = codigo;

    // Prólogo
    *p++ = 0x55;                  // push   %rbp
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xe5; // mov    %rsp, %rbp

    int numFixos = 0; // contador de parametros que não são passados na chamada

    // Configurar parâmetros do tipo PARAM primeiro
    for (int i = 0; i < n; i++) {
        switch (params[i].orig_val) {
            case PARAM:
              // Usar registradores na ordem rdi, rsi, rdx
              switch(numFixos){
                // nao precisa fazer nada enquanto os argumentos sejam do tipo PARAM

                case 1: 
                  if(i == 1){ 
                    // se for o segundo precisa ver se o terceiro está livre e salvar
                    // o valor do segundo registrador antes de mover o argumento
                    if(params[2].tipo_val == PTR_PAR){
                      if (params[2].tipo_val == INT_PAR){
                        *p++ = 0x89; *p++ = 0xf2; // mov esi para o edx
                      } else{
                        *p++ = 0x48; *p++ = 0x89; *p++ = 0xf2; // mov rsi para o rdx
                      }
                    }
                    if (params[i].tipo_val == INT_PAR){
                      *p++ = 0x89; *p++ = 0xfe; // mov edi para o esi
                    } else{
                      *p++ = 0x48; *p++ = 0x89; *p++ = 0xfe; // mov rdi para o rsi
                    }
                  }
                  break;
                case 2:
                // caso onde os dois primeiros são fixos, basta mover o primeiro
                // recebido para o terceiro registrador
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0x89; *p++ = 0xfa; // mov edi para o edx
                  } else{
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
              switch (i){ // primeiro adiciona o binário da instrução
                case 0:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xbf; // mov para o edi
                  } else{
                    *p++ = 0x48; *p++ = 0xbf; // mov para o rdi
                  }
                  break;
                case 1:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xbe; // mov para o esi
                  } else{
                    *p++ = 0x48; *p++ = 0xbe; // mov para o rsi
                  }
                  break;

                case 2:
                  if (params[i].tipo_val == INT_PAR){
                    *p++ = 0xba; // mov para o edx
                  } else{
                    *p++ = 0x48; *p++ = 0xba; // mov para o rdx
                  }
                  break;
              }

              // para depois adicionar o valor constante na instrução
              if (params[i].tipo_val == INT_PAR){
                *((int *)p) = params[i].valor.v_int;  p += 4; // armazena o valor inteiro no registrador correspondente
              } else {
                *((void **)p) = params[i].valor.v_ptr; p += 8; // armazena o endereço do ponteiro no registrador correspondente
              }

              break;

            case IND: // Carregar valor indireto de memória
              // primeiro carrega a referência recebida pelo cria_func
              // em uma constante no codigo[], pra que essa constante
              // sirva de referencia dinâmica em tempo de execução

              // prólogo onde guarda a constante
              *p++ = 0x49; *p++ = 0xba; // mov $ponteiro, %r10
              *((void **)p) = params[i].valor.v_ptr; p += 8; // adiciona os dados do $ponteiro

              switch (i){ // desreferencia a constante para achar o valor da variavel indicada
                case 0:
                  if (params[i].tipo_val == INT_PAR){
                    // caso do valor ser inteiro
                    *p++ = 0x41; *p++ = 0x8b; *p++ = 0x3a; // mov (%r10), %edi
                  } else{
                    // caso do valor ser ponteiro
                    *p++ = 0x49; *p++ = 0x8b; *p++ = 0x3a; // mov (%r10), %rdi
                  }
                  break;

                case 1:
                  if (params[i].tipo_val == INT_PAR){
                    // caso do valor ser inteiro
                    *p++ = 0x41; *p++ = 0x8b; *p++ = 0x32; // mov (%r10), %esi

                  } else{
                    // caso do valor ser ponteiro
                    *p++ = 0x49; *p++ = 0x8b; *p++ = 0x32; // mov (%r10), %rsi
                  }
                  break;

                case 2:
                  if (params[i].tipo_val == INT_PAR){
                    // caso do valor ser inteiro
                    *p++ = 0x41; *p++ = 0x8b; *p++ = 0x12; // mov (%r10), %edx

                  } else{
                    // caso do valor ser ponteiro
                    *p++ = 0x49; *p++ = 0x8b; *p++ = 0x12; // mov (%r10), %rdx
                  }
                  break;

              }
              break;
        }
    }

    // Chamada à função original
    *p++ = 0x48; *p++ = 0xb8; // mov $endereço, %rax
    *((void **)p) = f; p += 8; // adiciona os dados de $endereco
    *p++ = 0xff; *p++ = 0xd0; // call *%rax

    // Epílogo
    *p++ = 0xc9; // leave
    *p++ = 0xc3; // ret
}
