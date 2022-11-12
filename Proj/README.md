# Projeto 02, Projeto Final:

## O Grupo:

* Caio Sampaio Oliveira, TIA 32195621;
* Guilherme Picoli Rodrigues, TIA 32147317;
* Leonardo Henrique de Oliveira Matos, TIA 32139561.

## O Programa:

### Pré-requisito para a compilação:

  O programa é compatível o Sistema Operacional Linux;
Foi utilizado as distribuições Ubuntu para o desenvolvimento do programa.

### Como compilar o programa:

  Para compilar o programa "Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o compilador C GCC e o seguinte comando no terminal:
gcc -g -Wall Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c -o Proj02-04N11-CaioS_GuilhermeP_LeonardoM.bin -Ipthread

### Como executar o programa:

  Para executar o programa "Proj02-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o seguinte comando o terminal:
./Proj02-04N11-CaioS_GuilhermeP_LeonardoM.bin

### Como comprovar que os resultados propostos foram alcançados:

  O programa deve realizar transferências entre duas contas, uma conta _FROM_ e uma conta _TO_, e imprimir a confirmação de realização de transferências e o saldo das contas. Caso a conta _FROM_ zere o saldo, a conta _TO_ assume o papel de transferidor de saldo, tornando-se a conta _FROM_ e vice-versa. Assim as transferências, inclusive as simultâneas, devem ocorrer da seguinte maneira:
  
  -- Transferência do nº 98 -- 

Transferindo 1

Transferência 98 concluída com sucesso!

Saldo de c1: $99

Saldo de c2: $1


-- Transferência do nº 99 -- 

Transferindo 1

Transferência 99 concluída com sucesso!

Saldo de c1: $100

Saldo de c2: $0


-- Transferência do nº 100 -- 

Transferindo 70

Transferência 100 concluída com sucesso!

Saldo de c1: $30

### Funcionamento do programa:

Inicialmente, o programa cria cada transferência como uma thread. A cada criação de transferência (thread) é executado o método transferencia() com o ID de cada transferência e, consequentemente, cada transferência tentará transferir um valor, gerado aleatoriamente, de uma conta FROM (de transfere valores) para uma conta TO (que recebe valores).

Será verificado o saldo da conta FROM, e caso a ela esteja zerada, ocorre a transferência no caminho inverso, ou seja a conta TO assume o papel da conta FROM e passa a transferir dinheiro. O programa também verifica se a transferência deixou a conta negativa, e em caso afirmativo (a conta ficou negativa), o valor é retornado a conta.
