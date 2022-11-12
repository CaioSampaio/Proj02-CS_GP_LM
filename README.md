# Projeto 02, Projeto Final - 04N11 - SO

## Grupo:
* Caio Sampaio Oliveira, TIA 32195621;
* Guilherme Picoli Rodrigues, TIA 32147317;
* Leonardo Henrique de Oliveira Matos, TIA 32139561.

## O Projeto no Repositório:

* Para acessar o "Projeto 2, Projeto Final" entre na pasta: **/Proj**

##Funcionamento do programa:

Inicialmente, o programa cria cada transferência como uma thread. A cada criação de transferência (thread) é executado o método transferencia() com o ID de cada transferência e, consequentemente, cada transferência tentará transferir um valor, gerado aleatoriamente, de uma conta FROM (de transfere valores) para uma conta TO (que recebe valores).

Será verificado o saldo da conta FROM, e caso a ela esteja zerada, ocorre a transferência no caminho inverso, ou seja a conta TO assume o papel da conta FROM e passa a transferir dinheiro. O programa também verifica se a transferência deixou a conta negativa, e em caso afirmativo (a conta ficou negativa), o valor é retornado a conta.
