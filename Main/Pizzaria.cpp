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
	char telefone[10]; //Chave primaria
	char cep[8], nome[50], endereco[50], cidade[30];
};

struct TpMotoqueiro{
	TpData data;
	int cpf[11]; //Chave primaria //alterei pra INT para fazer a valida��o
	char telefone[11], nome[30], endereco[50];
};

struct TpPizzas{
	int codigo; //Chave primaria
    float preco;
	char descricao[30];
};

struct TpPedidos{
	TpData dataPedido;
    int numero; //Chave primaria
    char telefone[11];
    int codigo;
    int cpf[11]; //alterei pra INT para fazer a valida��o
	char situacao[30];
};

int validarCPF(int ncpf[15]);
void cadastrarCliente(void);
void cadastrarMotoqueiro(void);
void exibirCliente(void);
void exibirMotoqueiro(void);
char menu(void);


int main(void){
	char op;
	
	do {
		op = menu();
		clrscr();
		
		switch(op){
			case 'A':
				cadastrarCliente();
				break;
				
			case 'B':
				cadastrarMotoqueiro();
				break;
				
			case 'C':
				exibirCliente();
				break;
				
			case 'D':
				exibirMotoqueiro();
				break;			
		}
			
	} while(op != 27);
}

int validarCPF(int ncpf[15]) {
	int i = 0, j = 10;
	int dig1, dig2;
	int soma = 0, resto;
	
	while (i < 9) {
		soma += ncpf[i] * j;
		i++;
		j--;
	}
	
	resto = soma % 11;
	if (resto < 2) // se resto < 2 o priemiro digito tem que ser = 0
		dig1 = 0;
	else  // se nao o digito tem que ser igual ao resto -11
		dig1 = 11 - resto;
	
	
	if (ncpf[9] != dig1) //cpf inv�lido
		return 0;
	else {
		i = 0, j = 11, soma = 0;
	
		while (i < 10) {
			soma += ncpf[i] * j;
			i++;
			j--;
		}
	
		resto = soma % 11;
		if (resto < 2)
			dig2 = 0;
		else
			dig2 = 11 - resto;
		
	}

	if (ncpf[10] != dig2)
		return 0;
	else
		return 1;
}

//ainda tenho que fazer a valida��o do n� telefone
void cadastrarCliente(void) {
	TpCliente aux;
	FILE *ptrarquivo = fopen("arquivopizzaria.dat", "ab");
	 
	printf("Insira o TELEFONE do cliente que deseja cadastrar:\n");
	fflush(stdin);
	gets(aux.telefone);
	
	while (strcmp(aux.telefone, "\0") != 0) {
		printf("Insira o NOME desse cliente:\n");
		gets(aux.nome);
		printf("Insira o ENDERECO desse cliente:\n");
		gets(aux.endereco);
		printf("Insira a CIDADE desse cliente:\n");
		gets(aux.cidade);
		printf("Insira o CEP desse cliente:\n");
		gets(aux.cep);
		
		fwrite(&aux, sizeof(TpCliente), 1, ptrarquivo);
		
		printf("\nInsira o TELEFONE do cliente que deseja cadastrar:\n");
		gets(aux.telefone);
		fflush(stdin);
	}
	
	clrscr();
	fclose(ptrarquivo);
}

void cadastrarMotoqueiro(void) {
	TpMotoqueiro aux;
	int flag;
	
	FILE *ptrarquivo = fopen("arquivopizzaria.dat", "ab");
	 
	printf("Insira o CPF do motoqueiro que deseja cadastrar:\n");
	for (int i = 0; i < 11; i++)
		scanf("%d", &aux.cpf[i]);
	flag = validarCPF(aux.cpf);

	//valida��o do CPF
	while (flag != 1 && aux.cpf[0] != 0) {
		printf("CPF inv�lido, insira um CPF v�lido:\n");
		scanf("%d", &aux.cpf);
		flag = validarCPF(aux.cpf);
	}
	
	while (aux.cpf != 0) {
		printf("Insira o NOME desse motoqueiro:\n");
		fflush(stdin);
		gets(aux.nome);
		printf("Insira o ENDERECO desse motoqueiro:\n");
		gets(aux.endereco);
		printf("Insira o TELEFONE desse motoqueiro:\n");
		gets(aux.telefone);
		printf("Insira a DATA DE ADMISSAO desse motoqueiro: [dd mm aaaa]\n");
		scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
		
		fwrite(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		
		printf("Insira o CPF do motoqueiro que deseja cadastrar:\n");
		for (int i = 0; i < 11; i++)
			scanf("%d", &aux.cpf[i]);
		flag = validarCPF(aux.cpf);
		//valida��o do CPF
		while (flag != 1 && aux.cpf[0] != 0) {
			printf("CPF inv�lido, insira um CPF v�lido:\n");
			for (int i = 0; i < 11; i++)
				scanf("%d", &aux.cpf[i]);
			flag = validarCPF(aux.cpf);
		}
	}
	
	clrscr();
	fclose(ptrarquivo);
}

void exibirCliente(void) {
	TpCliente aux;
	FILE *ptrarquivo = fopen("arquivopizzaria.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpCliente), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			printf("TELEFONE: %s\n", aux.telefone);
			printf("NOME: %s\n", aux.nome);
			printf("ENDERECO: %s\n", aux.endereco);
			printf("CIDADE: %s\n", aux.cidade);
			printf("CEP: %s\n", aux.cep);
			fread(&aux, sizeof(TpCliente), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

void exibirMotoqueiro(void) {
	TpMotoqueiro aux;
	FILE *ptrarquivo = fopen("arquivopizzaria.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else {
		fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		while (!feof(ptrarquivo)){
			printf("CPF: %d\n", aux.cpf);
			printf("NOME: %s\n", aux.nome);
			printf("ENDERECO: %s\n", aux.endereco);
			printf("TELEFONE: %s\n", aux.telefone);
			printf("DATA DE ADMISSAO: %d/%d/%d\n", aux.data.d, aux.data.m, aux.data.a);
			fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

char menu(void) {
	printf("# # # # MENU # # # # \n");
	printf("[A] Cadastrar CLIENTES\n");
	printf("[B] Cadastrar MOTOQUEIROS\n");
	printf("[C] Exibir CLIENTES\n");
	printf("[D] Exibir MOTOQUEIROS\n");
	
	return toupper(getche());
}