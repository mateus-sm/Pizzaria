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
void cadastrarPedido(void);

void exibirCliente(void);
void exibirMotoqueiro(void);
void exibirPizza(void);
void exibirPedidos(void);

int buscaCodigo(char file[50], int cod);
int buscaCPF(char file[50], char texto[50]);
int buscaTelefone(char file[50], char texto[50]);

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
				cadastrarPedido();
				break;	

			case 'E':
				exibirCliente();
				break;	

			case 'F':
				exibirMotoqueiro();
				break;

			case 'G':
				exibirPizza();
				break;

			case 'H':
				exibirPedidos();
				break;			
		}
			
	} while(op != 27);
}

int buscaTelefone(char file[50], char texto[50]) {
	TpCliente aux;

	FILE *ptr = fopen(file, "rb");

	if (ptr == NULL) {
		printf("ERRO de abertura\n");
	} else {
		fread(&aux, sizeof(TpCliente), 1, ptr);

		while(!feof(ptr) && strcmp(texto, aux.telefone) != 0) {
			fread(&aux, sizeof(TpCliente), 1, ptr);
		}

		if (strcmp(aux.telefone, texto) == 0) {
			return 1;
		} else {
			return -1;
		}	

		fclose(ptr);	
	}

}

int buscaCPF(char file[50], char texto[50]) {
	TpMotoqueiro aux;

	FILE *ptr = fopen(file, "rb");

	if (ptr == NULL) {
		printf("ERRO de abertura\n");
	} else {
		fread(&aux, sizeof(TpMotoqueiro), 1, ptr);

		while(!feof(ptr) && strcmp(texto, aux.cpf) != 0) {
			fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
		}

		if (strcmp(aux.cpf, texto) == 0) {
			return 1;
		} else {
			return -1;
		}	

		fclose(ptr);
	}

}

int buscaCodigo(char file[50], int cod) {
	TpPizzas aux;

	FILE *ptr = fopen(file, "rb");

	if (ptr == NULL) {
		printf("ERRO de abertura\n");
	} else {
		fread(&aux, sizeof(TpPizzas), 1, ptr);

		while(!feof(ptr) && aux.codigo != cod) {
			fread(&aux, sizeof(TpPizzas), 1, ptr);
		}

		if (aux.codigo == cod) {
			return 1;
		} else {
			return -1;
		}	
	}

}

void cadastrarPedido(void) {
	TpPedidos aux;
	int flag;
	FILE *ptrarquivo = fopen("Pedidos.dat", "ab");
	 
	printf("Insira o NUMERO do Pedido:\n");
	fflush(stdin);
	scanf("%d", &aux.numero);
	
	while (aux.numero > 0) {
		printf("Insira o TELEFONE do Cliente:\n");
		fflush(stdin);
		gets(aux.telefone);

		flag = buscaTelefone("Clientes.dat", aux.telefone);
		while (flag != 1 && strlen(aux.telefone) > 0) {
			printf("Insira o TELEFONE do Cliente:\n");
			fflush(stdin);
			gets(aux.telefone);

			flag = buscaTelefone("Clientes.dat", aux.telefone);
		}

		if (strlen(aux.telefone) > 0) {
			printf("Insira o CODIGO dessa Pizza:\n");
			scanf("%d", &aux.codigo);

			flag = buscaCodigo("Pizzas.dat", aux.codigo);
			while (flag != 1 && aux.codigo > 0) {
				printf("Insira o CODIGO dessa Pizza:\n");
				scanf("%d", &aux.codigo);

				flag = buscaCodigo("Pizzas.dat", aux.codigo);
			}			

			if (aux.codigo > 0) {
				printf("Digite o CPF do Motoqueiro\n");
				fflush(stdin);
				gets(aux.cpf);
				
				flag = buscaCPF("Motoqueiros.dat", aux.cpf);
				while (flag != 1 && strlen(aux.cpf) > 0) {
					printf("Digite o CPF do Motoqueiro\n");
					fflush(stdin);
					gets(aux.cpf);

					flag = buscaCPF("Motoqueiros.dat", aux.cpf);
				}

				if (strlen(aux.cpf) > 0) {
					strcpy(aux.situacao, "Em preparacao"); 				
					
					printf("Insira a DATA do Pedido: [dd mm aaaa]\n");
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);

					fwrite(&aux, sizeof(TpPedidos), 1, ptrarquivo);	

					printf("\nInsira o NUMERO do Pedido:\n");
					fflush(stdin);
					scanf("%d", &aux.numero);
				}
			}	
		}
	}
	
	clrscr();
	fclose(ptrarquivo);
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

void exibirPedidos(void) {
	TpPedidos aux;
	FILE *ptrarquivo = fopen("Pedidos.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpPedidos), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			printf("NUMERO: %d\n", aux.numero);
			printf("TELEFONE: %s\n", aux.telefone);
			printf("CODIGO: %d\n", aux.codigo);
			printf("CPF: %s\n", aux.cpf);
			printf("SITUACAO: %s\n", aux.situacao);
			printf("DATA DO PEDIDO: %d/%d/%d\n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
			fread(&aux, sizeof(TpPedidos), 1, ptrarquivo);
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
	printf("[D] Cadastrar PEDIDOS\n");
	printf("[E] Exibir CLIENTES\n");
	printf("[F] Exibir MOTOQUEIROS\n");
	printf("[G] Exibir PIZZAS\n");
	printf("[H] Exibir PEDIDOS\n");
	
	return toupper(getche());
}
