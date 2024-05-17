#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

struct TpData{
	int d, m, a;
};

struct TpCliente{
	char telefone[11]; //Chave primaria
	char cep[8], nome[30], endereco[50], cidade[30];
};

struct TpMotoqueiro{
	TpData data;
	char cpf[15]; //Chave primaria
	char telefone, nome[30], endereco[50];
};

struct TpPizzas{
	int codigo; //Chave primaria
    float preco;
	char descricao[30];
};

struct TpPedidos{
	TpData datapedido;
    int numero; //Chave primaria
    char telefone[11];
    int codigo;
    char cpf[15];
	char situacao[30];
};