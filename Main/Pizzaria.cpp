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

void alterarCliente(void);
void alterarMotoqueiro(void);
void alterarPizza(void);
void alterarPedidos(void);

int buscaCodigo(char file[50], int cod);
int buscaCPF(char file[50], char texto[50]);
int buscaTelefone(char file[50], char texto[50]);
int buscaPedido(char file[50], int pedido);

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
			
			case 'I':
				alterarCliente();
				break;	
				
			case 'J':
				alterarMotoqueiro();
				break;	
				
			case 'K':
				alterarPizza();
				break;
				
			case 'L':
				alterarPedidos();
				break;
		}
			
	} while(op != 27);
}

int buscaPedido(char file[50], int pedido){
	TpPedidos aux;

	FILE *ptr = fopen(file, "rb");

	if (ptr == NULL) {
		printf("ERRO de abertura\n");
	} else {
		fread(&aux, sizeof(TpPedidos), 1, ptr);

		while(!feof(ptr) && aux.numero != pedido) {
			fread(&aux, sizeof(TpPedidos), 1, ptr);
		}

		if (aux.numero == pedido) {
			return ftell(ptr) - sizeof(TpPedidos);
		} else {
			return -1;
		}	
		
		fclose(ptr);
	}

}

void alterarPedido(void){
	TpPedidos aux;
	int flag;
	char op;
	
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura \n");
	else{
		printf("Insira o NUMERO do Pedido que desja ALTERAR: \n");
		fflush(stdin);
		scanf("%d",&aux.numero);
		
		flag = buscaPedido("Pedidos.dat", aux.numero);
		
		while (flag == -1 && aux.numero > 0){
			printf("Insira um NUMERO do pedido cadastrado: \n");
			fflush(stdin);
			scanf("%d",&aux.numero);
			
			flag = buscaPedido("Pedidos.dat", aux.numero);
		}
		
		if(aux.numero > 0){
			fseek(ptr, flag, 0);
			printf("O que deseja ALTERAR?\n");
			printf("[A] NUMERO\n");
			printf("[B] TELEFONE\n");
			printf("[C] CODIGO DA PIZZA\n");
			printf("[D] CPF DO MOTOQUEIRO\n");
			printf("[E] SITUACAO\n");
			printf("[F] DATA DO PEDIDO\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("Insira o novo NUMERO do pedido: \n");
				scanf("%d", &aux.numero);
				
				while(aux.numero <= 0){
					printf("Insira um numero VALIDO: \n");
					scanf("%d", &aux.numero);
				}
				
				fwrite(&aux, sizeof(TpPedidos), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("Insira o novo TELEFONE do pedido: \n");
				fflush(stdin);
				gets(aux.telefone);
				flag = buscaTelefone("Clientes.dat", aux.telefone);
				
				while(strlen(aux.telefone) <= 0 || flag == -1){
					printf("Insira um telefone CADASTRADO: \n");
					fflush(stdin);
					gets(aux.telefone);
					flag = buscaTelefone("Clientes.dat", aux.telefone);
				}
				
				fwrite(&aux, sizeof(TpPedidos), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("Insira o novo CODIGO DA PIZZA do pedido \n");
				scanf("%d", &aux.codigo);
				flag = buscaCodigo("Pizzas.dat", aux.codigo);
				
				while(aux.codigo < 0 || flag == -1){
					printf("Insira um codigo da pizza CADASTRADO \n");
					scanf("%d", &aux.codigo);
					flag = buscaCodigo("Pizzas.dat", aux.codigo);
				}
				
				fwrite(&aux, sizeof(TpPedidos), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("Insira o novo CPF DO MOTOQUEIRO do pedido \n");
				fflush(stdin);
				gets(aux.cpf);
				flag = buscaCPF("Motoqueiros.dat", aux.cpf);
				
				while(strlen(aux.cpf) <= 0 || flag == -1){
					printf("Insira um cpf CADASTRADO: \n");
					fflush(stdin);
					gets(aux.cpf);
					flag = buscaCPF("Motoqueiros.dat", aux.cpf);
				}
				
				fwrite(&aux, sizeof(TpPedidos), 1, ptr);
				printf("Dados ALTERADOS\n");
			} else if(op == 'E'){
				printf("Para qual SITUACAO do pedido voce deseja alterar: \n");
				printf("[A] Em preparacao \n");
				printf("[B] Em rota de entrega \n");
				printf("[C] Entregue \n");
				printf("[D] Cancelado \n");
				
				op = toupper(getche());
				
				if(op == 'A')
					strcpy(aux.situacao,"Em preparacao");
				else if(op == 'B')
					strcpy(aux.situacao,"Em rota de entrega");
				else if(op == 'C')
					strcpy(aux.situacao,"Entregue");
				else
					strcpy(aux.situacao,"Cancelado");
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'F'){
				printf("Insira a nova DATA DO PEDIDP: [dd mm aaaa]\n");
				scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.m);
				
				while(aux.dataPedido.d > 31 || aux.dataPedido.d < 1 || aux.dataPedido.m > 12 || aux.dataPedido.m < 1 || aux.dataPedido.a > 2024 || aux.dataPedido.a < 1){
					printf("Insira uma data VALIDA\n");
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.m);
				}
				
				fwrite(&aux, sizeof(TpPedidos), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else
				printf("Alteração de dados CANCELADA\n");
		}
		
		getch();
		fclose(ptr);
	}
	
}
void alterarPizza(void){
	TpPizzas aux;
	int flag;
	char op;
	
	FILE *ptr = fopen("Pizzas.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura \n");
	else{
		printf("Insira o CODIGO da Pizza que desja ALTERAR: \n");
		fflush(stdin);
		scanf("%d",&aux.codigo);	
		flag = buscaCodigo("Pizzas.dat", aux.codigo);
		
		while (flag == -1 && aux.codigo > 0){
			printf("Insira um CODIGO cadastrado: \n");
			fflush(stdin);
			scanf("%d",&aux.codigo);
			flag = buscaCodigo("Pizzas.dat", aux.codigo);

		}
		
		if(aux.codigo > 0){
			fseek(ptr, flag, 0);
			printf("O que deseja ALTERAR?\n");
			printf("[A] CODIGO\n");
			printf("[B] DESCRICAO\n");
			printf("[C] VALOR\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("Insira o novo CODIGO: \n");
				scanf("%d", &aux.codigo);
				
				while(aux.codigo <= 0){
					printf("Insira um codigo VALIDO: \n");
					scanf("%d", &aux.codigo);
				}
				
				fwrite(&aux, sizeof(TpPizzas), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("Insira a nova DESCRICAO: \n");
				fflush(stdin);
				gets(aux.descricao);
				
				while(strlen(aux.descricao) <= 0){
					printf("Insira uma descricao VALIDA: \n");
					gets(aux.descricao);
				}
				
				fwrite(&aux, sizeof(TpPizzas), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("Insira o novo VALOR: \n");
				scanf("%f", &aux.valor);
				
				while(aux.valor <= 0){
					printf("Insira um valor VALIDO: \n");
					scanf("%f", &aux.valor);
				}
				
				fwrite(&aux, sizeof(TpPizzas), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else
				printf("Alteração de dados CANCELADA\n");
		}
		
		getch();
		fclose(ptr);
	}
	
}

void alterarMotoqueiro(void){
	TpMotoqueiro aux;
	int flag;
	char op;
	
	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("Insira o CPF do Motoqueiro que desja ALTERAR:\n");
		fflush(stdin);
		gets(aux.cpf);
		flag = buscaCPF("Motoqueiros.dat", aux.cpf);
		
		while (flag == -1 && strlen(aux.cpf) > 0) {
			printf("Insira um CPF cadastrado:\n");
			fflush(stdin);
			gets(aux.cpf);
	
			flag = buscaCPF("Motoqueiros.dat", aux.telefone);
		}
		
		if(strlen(aux.cpf) > 0){
			fseek(ptr, flag, 0);
			printf("O que deseja ALTERAR?\n");
			printf("[A] CPF\n");
			printf("[B] NOME\n");
			printf("[C] ENDERECO\n");
			printf("[D] TELEFONE\n");
			printf("[E] DATA DE ADMISSAO\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("Insira o novo CPF: \n");
				gets(aux.cpf);
				flag = validarCPF(aux.cpf);
				
				while(strlen(aux.cpf) <= 0 || flag != 1){
					printf("Insira um cpf VALIDO: \n");
					gets(aux.cpf);
					flag = validarCPF(aux.cpf);
				}
				
				while (strlen(aux.cpf) < 0 || aux.cpf)
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("Insira o novo NOME: \n");
				gets(aux.nome);
				
				while(strlen(aux.nome) <= 0){
					printf("Insira um nome VALIDO: \n");
					gets(aux.nome);
				}
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("Insira o novo ENDERECO: \n");
				gets(aux.endereco);
				
				while(strlen(aux.endereco) <= 0){
					printf("Insira um endereco VALIDO: \n");
					gets(aux.endereco);
				}
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("Insira o novo TELEFONE: \n");
				gets(aux.telefone);
				
				while(strlen(aux.telefone) <= 0){
					printf("Insira um telefone VALIDO: \n");
					gets(aux.telefone);
				}
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'E'){
				printf("Insira a nova DATA DE ADMISSAO: [dd mm aaaa]\n");
				scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.m);
				
				while(aux.data.d > 31 || aux.data.d < 1 || aux.data.m > 12 || aux.data.m < 1 || aux.data.a > 2024 || aux.data.a < 1){
					printf("Insira uma data VALIDA\n");
					scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.m);
				}
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else
				printf("Alteração de dados CANCELADA\n");
			
		}
		
		getch();
		fclose(ptr);
	}
	
}

void alterarCliente(void){
	TpCliente aux;
	int flag;
	char op;
	
	FILE *ptr = fopen("Clientes.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("Insira o TELEFONE do Cliente que desja ALTERAR:\n");
		fflush(stdin);
		gets(aux.telefone);
		flag = buscaTelefone("Clientes.dat", aux.telefone);
		
		while (flag == -1 && strlen(aux.telefone) > 0) {
			printf("Insira um TELEFONE cadastrado:\n");
			fflush(stdin);
			gets(aux.telefone);
	
			flag = buscaTelefone("Clientes.dat", aux.telefone);
		}
		
		if(strlen(aux.telefone) > 0){
			fseek(ptr, flag, 0);
			printf("O que deseja ALTERAR?\n");
			printf("[A] TELEFONE\n");
			printf("[B] NOME\n");
			printf("[C] ENDERECO\n");
			printf("[D] CIDADE\n");
			printf("[E] CEP\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("Insira o novo TELEFONE: \n");
				gets(aux.telefone);
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("Insira o novo NOME: \n");
				gets(aux.nome);
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("Insira o novo ENDERECO: \n");
				gets(aux.endereco);
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("Insira a nova CIDADE: \n");
				gets(aux.cidade);
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else if(op == 'E'){
				printf("Insira o novo CEP: \n");
				gets(aux.cep);
				
				fwrite(&aux, sizeof(TpCliente), 1, ptr);
				printf("Dados ALTERADOS\n");
			}else
				printf("Alteração de dados CANCELADA\n");
			
		}
		
		getch();
		fclose(ptr);
	}
		
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
			return ftell(ptr) - sizeof(TpCliente);
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
			return ftell(ptr) - sizeof(TpMotoqueiro);
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
			return ftell(ptr) - sizeof(TpPizzas);
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
		while (flag == -1 && strlen(aux.telefone) > 0) {
			printf("Insira um TELEFONE cadastrado:\n");
			fflush(stdin);
			gets(aux.telefone);

			flag = buscaTelefone("Clientes.dat", aux.telefone);
		}

		if (strlen(aux.telefone) > 0) {
			printf("Insira o CODIGO dessa Pizza:\n");
			scanf("%d", &aux.codigo);

			flag = buscaCodigo("Pizzas.dat", aux.codigo);
			while (flag == -1 && aux.codigo > 0) {
				printf("Insira o CODIGO dessa Pizza:\n");
				scanf("%d", &aux.codigo);

				flag = buscaCodigo("Pizzas.dat", aux.codigo);
			}			

			if (aux.codigo > 0) {
				printf("Digite o CPF do Motoqueiro\n");
				fflush(stdin);
				gets(aux.cpf);
				
				flag = buscaCPF("Motoqueiros.dat", aux.cpf);
				while (flag == -1 && strlen(aux.cpf) > 0) {
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
	
	if ((ncpf[9] - 48) != dig1) //cpf invï¿½lido
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

//ainda tenho que fazer a validaï¿½ï¿½o do nï¿½ telefone
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
	while (flag == -1 && strlen(aux.cpf) > 0) {
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
		while (flag == -1 && strlen(aux.cpf) > 0) {
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
	printf("[I] Alterar CLIENTES\n");
	printf("[J] Alterar MOTOQUEIROS\n");
	printf("[K] Alterar PIZZAS\n");
	printf("[L] Alterar PEDIDOS\n");
	
	
	return toupper(getche());
}
