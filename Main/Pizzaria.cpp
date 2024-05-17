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
	char telefone[20]; //Chave primaria
	char cep[15], nome[50], endereco[50], cidade[30];
};

struct TpMotoqueiro{
	TpData data;
	char cpf[20]; //Chave primaria
	char telefone[20], nome[50], endereco[50];
};

struct TpPizzas{
	int codigo; //Chave primaria
    float valor;
	char descricao[30];
};

struct TpPedidos{
	TpData dataPedido;
    int numero; //Chave primaria
    char telefone[20];
    int codigo;
    char cpf[20];
	char situacao[30];
};

int validarCPF(char ncpf[15]);
int validarInt(char str[11]);
void cadastrarCliente(void);
void cadastrarMotoqueiro(void);
void cadastrarPizza(void);
void exibirCliente(void);
void exibirMotoqueiro(void);
void exibirPizza(void);
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
				cadastrarPizza();
				break;
				
			case 'D':
				exibirCliente();
				break;	

			case 'E':
				exibirMotoqueiro();
				break;	

			case 'F':
				exibirPizza();
				break;			
		}
			
	} while(op != 27);
}

void cadastrarPizza(void) {
	TpPizzas aux;
	FILE *ptrarquivo = fopen("Pizzas.dat", "ab");
	 
	printf("Insira o CODIGO da Pizza:\n");
	fflush(stdin);
	scanf("%d", &aux.codigo);
	
	while (aux.codigo > 0) {
		printf("Insira a DESCRICAO dessa Pizza:\n");
		fflush(stdin);
		gets(aux.descricao);
		printf("Insira o VALOR dessa Pizza:\n");
		scanf("%f", &aux.valor);
		
		fwrite(&aux, sizeof(TpPizzas), 1, ptrarquivo);
		
		printf("\nInsira o CODIGO da Pizza:\n");
		fflush(stdin);
		scanf("%d", &aux.codigo);
	}
	
	clrscr();
	fclose(ptrarquivo);
}

void exibirPizza(void) {
	TpPizzas aux;
	FILE *ptrarquivo = fopen("Pizzas.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpPizzas), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			printf("CODIGO: %d\n", aux.codigo);
			printf("DESCRICAO: %s\n", aux.descricao);
			printf("VALOR: %.2f\n", aux.valor);
			fread(&aux, sizeof(TpPizzas), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

int validarCPF(char ncpf[15]) {
	int i = 0, j = 10;
	int dig1, dig2;
	int soma = 0, resto;
	
	//se algum caracter for < 0 ou > 9 //quebra o codigo 
	if(validarInt(ncpf) != 1){
		return 0;
	}
		
	while (i < 9){
		soma += (ncpf[i] - 48) * j;
		i++;
		j--;
	}
	
	resto = soma % 11;
	if (resto < 2) // se resto < 2 o priemiro digito tem que ser = 0
		dig1 = 0;
	else  // se nao o digito tem que ser igual ao resto -11
		dig1 = 11 - resto;
	
	if ((ncpf[9] - 48) != dig1) //cpf inv�lido
		return 0;
	else {
		i = 0, j = 11, soma = 0;
	
		while (i < 10) {
			soma += (ncpf[i] - 48) * j;
			i++;
			j--;
		}
	
		resto = soma % 11;
		if (resto < 2)
			dig2 = 0;
		else
			dig2 = 11 - resto;
		
	}
	
	if ((ncpf[10] - 48) != dig2)
		return 0;
	else
		return 1;
}

int validarInt(char str[11]){
	int i;
	int TL = strlen(str);
	
	for(i = 0 ; i < TL - 1 ; i++)
		if(str[i] < 48 || str[i] > 57)
			return 0;
	
	return 1;
}

//ainda tenho que fazer a valida��o do n� telefone
void cadastrarCliente(void) {
	TpCliente aux;
	FILE *ptrarquivo = fopen("Clientes.dat", "ab");
	 
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
	
	FILE *ptrarquivo = fopen("Motoqueiros.dat", "ab");
	 
	printf("Insira o CPF do motoqueiro que deseja cadastrar:\n");
	fflush(stdin);
	gets(aux.cpf);
	flag = validarCPF(aux.cpf);
	
	//validacao do CPF
	while (flag != 1 && strlen(aux.cpf) > 0) {
		printf("CPF invalido, insira um CPF valido:\n");
		fflush(stdin);
		gets(aux.cpf);
		flag = validarCPF(aux.cpf);
	}
	
	while (strlen(aux.cpf) > 0) {
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
		
		printf("\nInsira o CPF do motoqueiro que deseja cadastrar:\n");
		fflush(stdin);
		gets(aux.cpf);
		flag = validarCPF(aux.cpf);

		//validacao do CPF
		while (flag != 1 && strlen(aux.cpf) > 0) {
			printf("CPF invalido, insira um CPF valido:\n");
			fflush(stdin);
			gets(aux.cpf);
			flag = validarCPF(aux.cpf);
		}
	}
	
	clrscr();
	fclose(ptrarquivo);
}

void exibirCliente(void) {
	TpCliente aux;
	FILE *ptrarquivo = fopen("Clientes.dat", "rb");
	
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
	FILE *ptrarquivo = fopen("Motoqueiros.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else {
		fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		while (!feof(ptrarquivo)){
			printf("CPF: %s\n", aux.cpf);
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
	printf("[C] Cadastrar PIZZAS\n");
	printf("[D] Exibir CLIENTES\n");
	printf("[E] Exibir MOTOQUEIROS\n");
	printf("[F] Exibir PIZZAS\n");
	
	return toupper(getche());
}
