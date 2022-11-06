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
int valor;

/* ----- FUNÇÕES AUXILIARES ----- */

// Gera um número aleatório de 1 à 20
int gerarRandomico (){

    return rand()%20;
}

// The child thread will execute this function
int *transferencia(void *arg){
  int i = (intptr_t)arg; //ID de cada filósofo

  //Timer Fixo de 5 segundos
  sleep(3); //Filósofo irá comer por 5 segundos

  printf("\n-- Transferência do nº %d -- \n", i + 1);

  valor = gerarRandomico();
  printf( "Transferindo %d para a conta c2\n", valor );
	
	if (from.saldo >= valor){ // 2
		from.saldo -= valor;
		to.saldo += valor;
	}
  valor = gerarRandomico();
  printf( "Transferindo %d para a conta c1\n", valor );
  if (to.saldo >= valor){ // 2
		to.saldo -= valor;
		from.saldo += valor;
	}
	
	printf("Transferência concluída com sucesso!\n");
	printf("Saldo de c1: %d\n", from.saldo);
	printf("Saldo de c2: %d\n", to.saldo);
	
	return 0;
}

int main(){
	void* stack;
	//pid_t pid;
	int status;
	pthread_t contas[numero_threads]; //Vetor de transferencias como Threads
	
	// Allocate the stack
	stack = malloc( FIBER_STACK );
	
	if (stack == 0){
		perror("malloc: could not allocate stack");
		exit(1);
	}
	
	// Todas as contas começam com saldo 100
	from.saldo = 100;
	to.saldo = 100;

  //Cria as contas como threads
	for (int i = 0; i < numero_threads; i++){
		// Call the clone system call to create the child thread
		//pid = clone( &transferencia, (char*) stack + FIBER_STACK, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
		
		//if (pid == -1){
			//perror( "clone" );
			//exit(2);
		//}

    //Cria cada conta executando o método transferencia e salva o status de criação
    sleep(1);
    status = pthread_create(&contas[i], NULL, transferencia, (void*)(intptr_t)i);

    //Verifica se a criação foi bem-sucedida 
    if(status != 0){
      printf("Erro na transferência %d\n", i + 1);
    } else{
      printf("A transferência %d foi iniciada\n", i + 1);
    }
	}

  //Espera cada thread (filósofo) terminar
    for(int i = 0; i < numero_threads; i++){
	
	//Realiza o join de cada filósofo e salva o status da operação
        status = pthread_join(contas[i], NULL);
        
        //Verifica se a operação foi bem-sucedida
        if(status != 0){
            printf("O filósofo morreu à mesa %d\n", status);
        }
    }

	// Free the stack
	free( stack );
	
	printf("Transferências concluídas e memória liberada.\n");
	
	return 0;
}
