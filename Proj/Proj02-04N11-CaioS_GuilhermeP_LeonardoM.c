/*
  Projeto 02, Projeto Final - 04N11 - SO

  Nomes:
    Caio Sampaio Oliveira, TIA: 32195621;
    Guilherme Picoli Rodrigues, TIA: 32147317;
    Leonardo Henrique de Oliveira Matos, TIA: 32139561.

  Pré-requisito para a compilação:
    O programa é compatível o Sistema Operacional Linux; Foi utilizado a distribuição Ubuntu para o desenvolvimento do programa.

  Como compilar:
    Para compilar o programa "Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o compilador C GCC e o seguinte comando no terminal: gcc -g -Wall Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c -o Proj02-04N11-CaioS_GuilhermeP_LeonardoM.bin -Ipthread

  Como executar o programa:
    Para executar o programa "Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o seguinte comando o terminal: ./Proj02-04N11-CaioS_GuilhermeP_LeonardoM.bin

  Referências Bibliográficas:
    TANENBAUM, A. S. Sistemas Operacionais Modernos, 2ª Ed. São Paulo: Pearson Prentice Hall, 2005.
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>

/* ----- STRUCTS ----- */

struct c{
	int saldo;
};

/* ----- VARIÁVEIS GLOBAIS ----- */

#define FIBER_STACK 1024*64 // Pilha de 64KB
#define numero_threads 100
typedef struct c conta;
conta from, to;
int flag = 0;

/* ----- FUNÇÕES AUXILIARES ----- */

// Gera um número aleatório de 1 à 20
int gerarRandomico (){
    return rand()%101;
}

/* ----- FUNÇÕES PRINCIPAIS ----- */

// Realiza a transferência de valor de uma conta (from) para outra (to)
void *transferencia(void *arg){
  int i = (intptr_t)arg; //ID de cada transferência

  int valor = gerarRandomico();

  while (((valor > from.saldo) && (flag == 0)) || (valor==0)){
    valor = gerarRandomico();
  }

	if ((from.saldo >= valor) && (flag == 0)){

    printf("\n-- Transferência do nº %d -- \n\nTransferindo %d\n", i + 1, valor);

    from.saldo -= valor;
		to.saldo += valor;

    if (from.saldo < 0){
      to.saldo -= valor;
      from.saldo += valor;
    }

    if (from.saldo == 0){
      flag =1;
    }
	}

  while (((valor > to.saldo) && (flag == 1)) || (valor == 0)){
    valor = gerarRandomico();
  }

  if ((to.saldo >= valor) && (flag == 1)){

    printf("\n-- Transferência do nº %d -- \n\nTransferindo %d\n", i + 1, valor);

		to.saldo -= valor;
		from.saldo += valor;

    if (to.saldo < 0){
      from.saldo -= valor;
		  to.saldo += valor;
    }

    if(to.saldo == 0){
      flag =0;
    }
	}

  printf("Transferência %d concluída com sucesso!\nSaldo de c1: $%d\nSaldo de c2: $%d\n", i + 1, from.saldo, to.saldo);

  return  0;
}

/* ----- MAIN ----- */

// Programa Principal
int main(){
	void* stack;
	int status;
	pthread_t transferencias[numero_threads]; //Vetor de transferências como Threads

	//Aloca o stack
	stack = malloc(FIBER_STACK);

	if (stack == 0){
		perror("Erro no malloc: não foi possível o stack");
		exit(1);
	}

	//Todas as contas começam com saldo 100
	from.saldo = 100;
	to.saldo = 0;

  //Cria as transferências como threads
	for (int i = 0; i < numero_threads; i++){

    //Timer Fixo de 1 segundos
    //sleep(1);

    //Cria cada conta executando o método transferencia e salva o status de criação
    status = pthread_create(&transferencias[i], NULL, transferencia, (void*)(intptr_t)i);

    //Verifica se a criação foi bem-sucedida
    if(status != 0){
      printf("\nErro na transferência %d\n", i + 1);
    } else{
      printf("\nA transferência %d foi iniciada\n", i + 1);
    }
	}

  //Espera cada thread (transferência) terminar
  for(int i = 0; i < numero_threads; i++){

	  //Realiza o join de cada transferência e salva o status da operação
    status = pthread_join(transferencias[i], NULL);

    //Verifica se a operação foi bem-sucedida
    if(status != 0){
      printf("A transferência %d apresentou um erro inesperado\n", status);
    }
  }

	//Libera stack
	free(stack);

	printf("\nTransferências concluídas e memória liberada.\n");

	return 0;
}
