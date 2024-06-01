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
	char status;
};

struct TpMotoqueiro{
	TpData data;
	char cpf[20]; //Chave primaria
	char telefone[20], nome[50], endereco[50];
	char status;

};

struct TpPizza{
	int codigo; //Chave primaria
    float valor;
	char descricao[30];
	char status;

};

struct TpPedido{
	TpData dataPedido;
    int numero; //Chave primaria
    char telefone[20];
    int codigo;
    char cpf[20];
	char situacao[30];
	char status;

};

//Cadastro
void cadastrarCliente(void);
void cadastrarMotoqueiro(void);
void cadastrarPizza(void);
void cadastrarPedido(void);
//Auxiliares de Cadastro
int validarCPF(char ncpf[15]);
int validarInt(char str[11]);

//Exibição
void exibirCliente(void);
void exibirMotoqueiro(void);
void exibirPizza(void);
void exibirPedidos(void);

//Alteração
void alterarCliente(void);
void alterarMotoqueiro(void);
void alterarPizza(void);
void alterarPedido(void);

//Exclus�o L�gica
void exclusaoLogicaCliente(void);
void exclusaoLogicaMotoqueiro(void);
void exclusaoLogicaPizza(void);
void exclusaoLogicaPedido(void);

//Exclusão F�sica
void exclusaoFisicaCliente(void);
void exclusaoFisicaMotoqueiro(void);
void exclusaoFisicaPizza(void);
void exclusaoFisicaPedido(void);

//Metodos de Busca
int buscaBinariaCodigo(FILE *ptr, int cod);
int buscaCPF(FILE *ptr, char texto[50]);
int buscaSentinelaTelefone(FILE *ptr, char nome[30]);
int buscaSeqIndexadaPedido(FILE *ptr, int num);
int buscaPedido(FILE *ptr, int pedido);

//Metodos de Ordenação
void ordenacaoExaustivaMotoqueiro(void);
void insercaoDiretaCliente(void);
void bubbleSortPedido(void);
void selecaoDiretaPizza(void);
//void ordenacaoExaustivaCliente(void);
//void ordenacaoExaustivaPizza(void);
//void ordenacaoExaustivaPedido(void);

//Relatorios
void motoqueiroPorData(void);
void filtrarLetra(void);
void rankPizzas(void);
void relatorioCliente(void);
void estadoPizza(void);
//Auxiliares de Relatorios
void exibirFiltro(FILE *ptr, char letra);
float buscaPreco(FILE *ptrpizza, int cod);

//Estatisticas
void pizzaMaisPedida(void);
void pizzaMenosPedida(void);
void clienteMaisConsome(void);
void motoqueiroMenosExperiente(void);

//Menus
char menu(void);
char menuNum(void);
char menuCad(void);
char menuExib(void);
char menuAlt(void);
char menuExclLF(void);
char menuExcl(void);
char menuRel(void);
char menuEst(void);


int main(void){
	char op;
	
	do {
		op = menuNum();
		clrscr();
		
		switch(op){
			case '1':
				op = menuCad();

				switch (op) {
					case '1':
						cadastrarCliente();
						break;
						
					case '2':
						cadastrarMotoqueiro();
						break;
						
					case '3':
						cadastrarPizza();
						break;
						
					case '4':
						cadastrarPedido();
						break;
				}

			break;

			case '2':
				op = menuExib();

				switch (op) {
					case '1':
						exibirCliente();
						break;	

					case '2':
						ordenacaoExaustivaMotoqueiro();
						exibirMotoqueiro();
						break;

					case '3':
						exibirPizza();
						break;

					case '4':
						exibirPedidos();
						break;
				}

			break;

			case '3':
				op = menuAlt();

				switch (op) {
					case '1':
						alterarCliente();
						break;	
						
					case '2':
						alterarMotoqueiro();
						break;	
						
					case '3':
						alterarPizza();
						break;
						
					case '4':
						alterarPedido();
						break;
				}

			break;

			case '4':
				op = menuExclLF();

				switch (op) {
					case '1':
						op = menuExcl();
						
						switch(op){
							case '1':
								exclusaoFisicaCliente();
								break;
							
							case '2':
								exclusaoFisicaMotoqueiro();
								break;
							
							case '3':
								exclusaoFisicaPizza();
								break;
							
							case '4':
								exclusaoFisicaPedido();
								break;
						}
								
					case '2':
						op = menuExcl();
						
						switch(op){
							case '1':
								exclusaoLogicaCliente();
								break;
							
							case '2':
								exclusaoLogicaMotoqueiro();
								break;
							
							case '3':
								exclusaoLogicaPizza();
								break;
							
							case '4':
								exclusaoLogicaPedido();
								break;		
						}
				}

			break;

			case '5':
				op = menuRel();

				switch (op) {
					case '1':
						estadoPizza();
					break;

					case '2':
						filtrarLetra();
					break;

					case '3':
						relatorioCliente();
					break;

					case '4':
						motoqueiroPorData();
					break;

					case '5':
						rankPizzas();
					break;
				}
			break;

			case '6':
				op = menuEst();
					switch (op) {
					case '1':
						pizzaMaisPedida();
					break;

					case '2':
						pizzaMenosPedida();
					break;

					case '3':
						clienteMaisConsome();
					break;

					case '4':
						motoqueiroMenosExperiente();
					break;
				}
			break;
		}

	} while(op != 27);
}

void rankPizzas(void) {
	clrscr();
	TpPedido aux;
	TpPizza auxPizza;
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb+");
	int pos, TL, i;

	fseek(ptrPizza, 0, 2);
	int loop = ftell(ptrPizza) / sizeof(TpPizza);
	//printf("\nLoop = %d\n", loop);

	printf("### Rank de pizzas ###");
	while (loop > 0) {
		//Colocar todas as pizzas em uma matriz
		fseek(ptr, 0, 2);
		int TF = ftell(ptr) / sizeof(TpPedido);

		char listaPizzas[TF][1];
		fseek(ptr, 0, 0);
		fread(&aux, sizeof(TpPedido), 1, ptr);
		TL = 0;
		while(!feof(ptr)) {
			if (aux.status == 'A') {
				listaPizzas[TL][0] = aux.codigo;
				TL++;
			}
			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		//Ver quantas vezes cada pizza aparece
		int atual, count, maior, vezes = 0;
		fseek(ptrPizza, 0, 0);
		fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
		while (!feof(ptrPizza)) {
			if (auxPizza.status == 'A') {
				for (int j = 0; j < TL; j++) {
					if (j == 0) {
						atual = auxPizza.codigo;
						count = 0;
						if (listaPizzas[j][0] == atual) {
							count++;
						}
					} else {
						if (listaPizzas[j][0] == atual) {
							count++;
						}
					}
				}

				if (count > vezes) {
					maior = atual;
					vezes = count;
				}
			}

			//Debug de informaçoes
			//printf("\nPizza analisada: %s Apareceu %d vezes\nCod da Pizza que mais apareceu %d Vezes que ela apareceu %d", auxPizza.descricao, count, maior, vezes); getch();
			fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
		}

		pos = buscaBinariaCodigo(ptrPizza, maior);
		if (pos != -1) {
			fseek(ptrPizza, pos, 0);
			fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

			fseek(ptrPizza, pos, 0);
			auxPizza.status = 'E';
			fwrite(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

			fseek(ptrPizza, pos, 0);
			fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

			printf("\n%s - %d pedido(s)", auxPizza.descricao, vezes);			
		}

		loop--;
	}

	//printf("\nTeste\n");
	fseek(ptrPizza, 0, 0);  
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza); 
	i = 0;
	while (!feof(ptrPizza)) { 
		if (auxPizza.status == 'E') {
			auxPizza.status = 'A';
			fseek(ptrPizza, i * sizeof(TpPizza), 0);
			fwrite(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
			fseek(ptrPizza, (i + 1) * sizeof(TpPizza), 0);
		}
		fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
		i++;
	}

	getch();

	fclose(ptr);
	fclose(ptrPizza);
}

int verificaIntervaloData(int diai, int mesi, int anoi, int diaf, int mesf, int anof, int diafiltro, int mesfiltro, int anofiltro){
	if(anofiltro >= anoi && anofiltro <= anof){											//verifica se esta dentro do ano
		if(mesfiltro >= mesi && mesfiltro <= mesf){										//verifica se esta dentro do mes
			if(diafiltro >= diai && diafiltro <= diaf)									//verifica se esta dentro do dia
				return 1;
			else if(diafiltro < diai && (mesfiltro > mesi || anofiltro > anoi))
				return 1;
			else if(diafiltro > diaf && (mesfiltro < mesf || anofiltro < anof))			//se o dia for maior que final, verifica se o mes
				return 1;
		}else if(mesfiltro < mesi && anofiltro > anoi){									//se o mes for menor que o inicial, verifica se o ano é maior ao inicial
			if(diafiltro >= diai && diafiltro <= diaf)									//verifica se esta dentro do dia
				return 1;
			else if(diafiltro < diai && (mesfiltro > mesi || anofiltro > anoi))
				return 1;
			else if(diafiltro > diaf && (mesfiltro < mesf || anofiltro < anof))			//se o dia for maior que final, verifica se o mes é menor que final ou se o ano é menor que o final
				return 1;
		}else if(mesfiltro > mesf && anofiltro < anof){									//se o mes for menor que o final, verifica se o ano é menor ao final
			if(diafiltro >= diai && diafiltro <= diaf)									//verifica se esta dentro do dia
				return 1;
			else if(diafiltro < diai && (mesfiltro > mesi || anofiltro > anoi))
				return 1;
			else if(diafiltro > diaf && (mesfiltro < mesf || anofiltro < anof))
				return 1;
		}	
	}
	return -1;
}

int qtdEntregas(char cpf[30], int diai, int mesi, int anoi, int diaf, int mesf, int anof, int diafiltro, int mesfiltro, int anofiltro){
	TpPedido aux;
	int cont;

	FILE *ptr = fopen("Pedidos.dat", "rb+");

	if(ptr == NULL)
		printf("ERRO DE ABERTURA\n");
	else{
		fseek(ptr, 0 , 0);
		cont = 0;
		fread(&aux, sizeof(TpPedido), 1, ptr);
		while(!feof(ptr)){
			if(verificaIntervaloData(diai, mesi, anoi, diaf, mesf, anof, diafiltro, mesfiltro, anofiltro) != -1)
				if(stricmp(aux.cpf, cpf) == 0 && stricmp(aux.situacao, "Entregue") == 0)
					cont++;
			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		fclose(ptr);
		return cont; 
	}
}

void motoqueiroPorData(void){
	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	TpMotoqueiro aux;
	TpData datai, dataf;
	int entregas;

	if(ptr == NULL)
		printf("Erro de abertura\n");
	else {
		printf("\nInsira a data inicial:\n");
		scanf("%d %d %d", &datai.d,&datai.m,&datai.a);
		printf("Insira a data final:\n");
		scanf("%d %d %d", &dataf.d,&dataf.m,&dataf.a);

		fseek(ptr, 0 , 0);
		fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
		while(!feof(ptr)){
			if(verificaIntervaloData(datai.d, datai.m, datai.a, dataf.d, dataf.m, dataf.a, aux.data.d, aux.data.m, aux.data.a) != -1){
				printf("\nMOTOQUEIRO: %s\n", aux.nome);
				entregas = qtdEntregas(aux.cpf,datai.d, datai.m, datai.a, dataf.d, dataf.m, dataf.a, aux.data.d, aux.data.m, aux.data.a);
            	printf("ENTREGAS REALIZDAS:%d\n", entregas);
			}
			fread(&aux, sizeof(TpMotoqueiro), 1, ptr);	
		}

		fclose(ptr);
	}	
	getch();
}

int validarNumTelefone(char telefone[30]){
	int digito;
	//numero de telefone deve conter entre 10 e 11 digitos
	if(strlen(telefone) - 1 < 10 || strlen(telefone) - 1 > 11)
		return -1;
	//validacao dos DDS // varia de 11 ate 99 // seguindo a sequencia 11 ate 19 // 21 ate 29 // 31 ate 29
	digito = telefone[0] - 48;
	if(digito < 1 || digito > 9)
		return -1;

	digito = telefone[1] - 48;	
	if(digito < 1 || digito > 9)
		return -1;  

	return 1;
}

int verificaClienteCadastrado(char tel[30]){
	int flag;
	FILE *ptr = fopen("Clientes.dat", "rb+");
	if(ptr != NULL)
		flag = buscaSentinelaTelefone(ptr, tel);
	else
		flag = -1;
	
	fclose(ptr);
	return flag;
}

int verificaMotoqueiroCadastrado(char cpf[30]){
	int flag;
	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	if(ptr != NULL)
		flag = buscaCPF(ptr, cpf);
	else
		flag = -1;

	fclose(ptr);
	return flag;
}

int verificaCodPizzaCadastrado(int cod){
	int flag;
	FILE *ptr = fopen("Pizzas.dat", "rb+");
	if(ptr != NULL)
		flag = buscaBinariaCodigo(ptr, cod);
	else
		flag = -1;

	fclose(ptr);
	return flag;
}

int verificaNumPedidoCadastrado(int num){
	int flag;
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	if(ptr != NULL)
		flag = buscaSeqIndexadaPedido(ptr, num);
	else
		flag = -1;

	fclose(ptr);
	return flag;
}

void motoqueiroMenosExperiente(void) {
	TpPedido aux;
	TpMotoqueiro auxMotoqueiro;

	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrMotoqueiro = fopen("Motoqueiros.dat", "rb+");
	int pos;

	//Colocar todos os motoqueiros em uma matriz
	fseek(ptr, 0, 2);
	int TF = ftell(ptr) / sizeof(TpPedido);

	char listaMotoqueiros[TF][30];
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	int TL = 0;
	while(!feof(ptr)) {
		if (aux.status == 'A' && strcmp(aux.situacao, "Entregue") == 0) {
			strcpy(listaMotoqueiros[TL], aux.cpf);
			TL++;
		}
		fread(&aux, sizeof(TpPedido), 1, ptr);
	}

	//Debug de informaçoes
	//printf("\nQuantidade de entregas: %d\nValor de i: %d\n", TF, TL);
	//printf("Frequencia de motoqueiros:\n");
	//for (int j = 0; j < TL; j++) {
	//	pos = buscaCPF(ptrMotoqueiro, listaMotoqueiros[j]);
	//	fseek(ptrMotoqueiro, pos, 0);
	//	fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);

	//	printf("CPF: %s - %s\n", listaMotoqueiros[j], auxMotoqueiro.nome);
	//}

	//Pegar Motoqueiro por Motoqueiro e verificar
	int count, vezes = 999;
	char atual[30], menor[30];
	fseek(ptrMotoqueiro, 0, 0);
	fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);
	while (!feof(ptrMotoqueiro)) {
		if (auxMotoqueiro.status == 'A') {
			for (int j = 0; j < TL; j++) {
				if (j == 0) {
					strcpy(atual, auxMotoqueiro.cpf);
					count = 0;
					if (strcmp(listaMotoqueiros[j], atual) == 0) {
						count++;
					}
				} else {
					if (strcmp(listaMotoqueiros[j], atual) == 0) {
						count++;
					}
				}
			}

			if (count < vezes) {
				strcpy(menor, atual);
				vezes = count;
			}
		}

		//Debug de informaçoes
		//printf("\nMotoqueiro analisado: %s - Apareceu %d vezes\nCPF que mais apareceu %s - Vezes que ele apareceu %d", auxMotoqueiro.nome, count, menor, vezes); getch();
		fread(&auxMotoqueiro, sizeof(TpCliente), 1, ptrMotoqueiro);
	}

	//Mostrar os valores achados
	pos = buscaCPF(ptrMotoqueiro, menor);
	fseek(ptrMotoqueiro, pos, 0);
	fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);

	if (vezes == 999) {
		vezes = 0; //Gambiarra para caso o entregador que tiver menos entregas tiver 0
	}
	printf("\nMotoqueiro menos experiente: %s - %d entrega(s)", auxMotoqueiro.nome, vezes);

	getch();
	fclose(ptr);
	fclose(ptrMotoqueiro);
}

void clienteMaisConsome(void) {
	TpPedido aux;
	TpCliente auxCliente;

	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrCliente = fopen("Clientes.dat", "rb+");
	int pos;

	//Colocar todos os clientes em uma matriz
	fseek(ptr, 0, 2);
	int TF = ftell(ptr) / sizeof(TpPedido);

	char listaClientes[TF][30];
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	int TL = 0;
	while(!feof(ptr)) {
		if (aux.status == 'A') {
			strcpy(listaClientes[TL], aux.telefone);
			TL++;
		}
		fread(&aux, sizeof(TpPedido), 1, ptr);
	}

	//Debug de informaçoes
	//printf("\nQuantidade de pedidos: %d\nValor de i: %d\n", TF, TL);
	//printf("Frequencia de clientres:\n");
	//for (int j = 0; j < TL; j++) {
	//	pos = buscaSentinelaTelefone(ptrCliente, listaClientes[j]);
	//	fseek(ptrCliente, pos, 0);
	//	fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);

	//	printf("Tel: %s - %s\n", listaClientes[j], auxCliente.nome);
	//}

	//Pegar Cliente por cliente e verificar
	int count, vezes = 0;
	char atual[30], maior[30];
	fseek(ptrCliente, 0, 0);
	fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);
	while (!feof(ptrCliente)) {
		if (auxCliente.status == 'A') {
			for (int j = 0; j < TL; j++) {
				if (j == 0) {
					strcpy(atual, auxCliente.telefone);
					count = 0;
					if (strcmp(listaClientes[j], atual) == 0) {
						count++;
					}
				} else {
					if (strcmp(listaClientes[j], atual) == 0) {
						count++;
					}
				}
			}

			if (count > vezes) {
				strcpy(maior, atual);
				vezes = count;
			}
		}

		//Debug de informaçoes
		//printf("\nCliente analisado: %s Apareceu %d vezes\nTEL que mais apareceu %s Vezes que ele apareceu %d", auxCliente.nome, count, maior, vezes); getch();
		fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);
	}

	//Mostrar os valores achados
	pos = buscaSentinelaTelefone(ptrCliente, maior);
	fseek(ptrCliente, pos, 0);
	fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);

	printf("\nCliente que mais pediu: %s - %d pedido(s)", auxCliente.nome, vezes);

	getch();
	fclose(ptr);
	fclose(ptrCliente);
}

void pizzaMaisPedida(void) {
	TpPedido aux;
	TpPizza auxPizza;
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb+");
	int pos, TL;

	//Colocar todas as pizzas em uma matriz
	fseek(ptr, 0, 2);
	int TF = ftell(ptr) / sizeof(TpPedido);

	char listaPizzas[TF][1];
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	TL = 0;
	while(!feof(ptr)) {
		if (aux.status == 'A') {
			listaPizzas[TL][0] = aux.codigo;
			TL++;
		}
		fread(&aux, sizeof(TpPedido), 1, ptr);
	}

	//Debug de informaçoes
	//printf("\nQuantidade de pedidos: %d\nValor de i: %d\n", TF, TL);
	//printf("Pizzas pedidas:\n");
	//for (int j = 0; j < TL; j++) {
	//	pos = buscaBinariaCodigo(ptrPizza, listaPizzas[j][0]);
	//	fseek(ptrPizza, pos, 0);
	//	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

	//	printf("Codigo: %d - %s\n", listaPizzas[j][0], auxPizza.descricao);
	//}

	//Ver quantas vezes cada pizza aparece
	int atual, count, maior, vezes = 0;
	fseek(ptrPizza, 0, 0);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
	while (!feof(ptrPizza)) {
		if (auxPizza.status == 'A') {
			for (int j = 0; j < TL; j++) {
				if (j == 0) {
					atual = auxPizza.codigo;
					count = 0;
					if (listaPizzas[j][0] == atual) {
						count++;
					}
				} else {
					if (listaPizzas[j][0] == atual) {
						count++;
					}
				}
			}

			if (count > vezes) {
				maior = atual;
				vezes = count;
			}
		}

		//Debug de informaçoes
		//printf("\nPizza analisada: %s Apareceu %d vezes\nCod da Pizza que mais apareceu %d Vezes que ela apareceu %d", auxPizza.descricao, count, maior, vezes); getch();
		fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
	}

	pos = buscaBinariaCodigo(ptrPizza, maior);
	fseek(ptrPizza, pos, 0);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

	printf("\nPizza mais pedida: %s - %d pedido(s)", auxPizza.descricao, vezes);

	getch();

	fclose(ptr);
	fclose(ptrPizza);
}

void pizzaMenosPedida(void) {
	TpPedido aux;
	TpPizza auxPizza;
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb+");
	int pos, TL;

	//Colocar todas as pizzas em uma matriz
	fseek(ptr, 0, 2);
	int TF = ftell(ptr) / sizeof(TpPedido);

	char listaPizzas[TF][1];
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	TL = 0;
	while(!feof(ptr)) {
		if (aux.status == 'A') {
			listaPizzas[TL][0] = aux.codigo;
			TL++;
		}
		fread(&aux, sizeof(TpPedido), 1, ptr);
	}

	//Ver quantas vezes cada pizza aparece
	int atual, count, menor, vezes = 999;
	fseek(ptrPizza, 0, 0);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
	while (!feof(ptrPizza)) {
		if (auxPizza.status == 'A') {
			for (int j = 0; j < TL; j++) {
				if (j == 0) {
					atual = auxPizza.codigo;
					count = 0;
					if (listaPizzas[j][0] == atual) {
						count++;
					}
				} else {
					if (listaPizzas[j][0] == atual) {
						count++;
					}
				}
			}

			if (count < vezes) {
				menor = atual;
				vezes = count;
			}			
		}

		//printf("\nPizza analisada: %s Apareceu %d vezes\nCod da Pizza que menos apareceu %d Vezes que ela apareceu %d", auxPizza.descricao, count, menor, vezes); getch();
		fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);
	}

	pos = buscaBinariaCodigo(ptrPizza, menor);
	fseek(ptrPizza, pos, 0);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

	printf("\nPizza menos pedida: %s - %d pedido(s)", auxPizza.descricao, vezes);	

	getch();

	fclose(ptr);
	fclose(ptrPizza);
}

void exclusaoLogicaPedido(void){
	TpPedido aux;
	int num, flag;
	
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("\nDigite o NUMERO DO PEDIDO que deseja excluir: \n");
		fflush(stdin);
		scanf("%d",&num);
		
		flag = buscaSeqIndexadaPedido(ptr, num);
		
		while (flag == -1 && num > 0){
			printf("Insira um numero do pedido CADASTRADO: \n");
			fflush(stdin);
			scanf("%d",&num);
		
			flag = buscaSeqIndexadaPedido(ptr, num);
		}
		
		if(num > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpPedido), 1, ptr);
			fseek(ptr, flag, 0);	

			printf("---> Dados do PEDIDO <---\n");
			printf("Numero: %d\n", aux.numero);
			printf("Telefone: %s\n", aux.telefone);
			printf("Codigo da pizza: %d\n", aux.codigo);
			printf("CPF: %s\n", aux.cpf);
			printf("Situacao: %s\n", aux.situacao);
			printf("Data do pedido: %d/%d/%d \n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
			printf("STATUS: %c\n", aux.status);
			
			printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
			if(toupper(getche()) == 'Y'){
				aux.status = 'I';
				fwrite(&aux,sizeof(TpPedido), 1, ptr);
				printf("\nPedido excluido com sucesso\n");
			} else
				printf("\nExclusao nao realizada\n");
		}
		
		fclose(ptr);
		getch();
		clrscr();
	}
}

int verificaCodPedido(FILE *ptr, int cod) {
	TpPedido aux;

	fseek(ptr, 0, 0);

	fread(&aux, sizeof(TpPedido), 1, ptr);
	while(!feof(ptr) && (aux.codigo != cod || aux.status != 'A')) 
		fread(&aux, sizeof(TpPedido), 1, ptr);
	
	if(aux.codigo == cod && aux.status == 'A')
		return 1;
	else
		return -1;
}

void exclusaoLogicaPizza(void){
	TpPizza aux;
	int cod, flag;
	
	FILE *ptr = fopen("Pizzas.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("\nDigite o CODIGO DA PIZZA que deseja excluir: \n");
		fflush(stdin);
		scanf("%d",&cod);
		
		flag = buscaBinariaCodigo(ptr, cod);
		
		while (flag == -1 && cod > 0){
			printf("Insira um codigo da pizza CADASTRADO: \n");
			fflush(stdin);
			scanf("%d",&cod);
		
			flag = buscaBinariaCodigo(ptr, cod);
		}

		flag = verificaCodPedido(ptr, cod);
		
		if (flag == 1) {
			if(cod > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpPizza), 1, ptr);
				fseek(ptr, flag, 0);	

				printf("---> Dados da PIZZA <---\n");
				printf("CODIGO: %d\n", aux.codigo);
				printf("DESCRICAO: %s\n", aux.descricao);
				printf("VALOR: %.2f\n", aux.valor);
				printf("STATUS: %c\n", aux.status);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpPizza), 1, ptr);
					printf("\nPizza excluida com sucesso\n");
				} else
					printf("\nExclusao nao realizada\n");
			}			
		} else {
			printf("Pizza cadastrada com pedido ativo!\nExclusao nao realizada\n");
		}
		
		fclose(ptr);
		getch();
		clrscr();
	}
}

int verificaCPFPedido(FILE *ptr, char cpf[30]) {
	TpPedido aux;

	fseek(ptr, 0, 0);


	fread(&aux, sizeof(TpPedido), 1, ptr);
	while(!feof(ptr) && (stricmp(aux.cpf, cpf) != 0 || aux.status != 'A')) 
		fread(&aux, sizeof(TpPedido), 1, ptr);
	
	if(stricmp(aux.cpf, cpf) == 0 && aux.status == 'A')
		return 1;
	else
		return -1;
}

void exclusaoLogicaMotoqueiro(void){
	TpMotoqueiro aux;
	char cpf[30];
	int flag;
	
	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("\nDigite o CPF do motoqueiro que deseja excluir: \n");
		fflush(stdin);
		gets(cpf);
		
		flag = buscaCPF(ptr, cpf);
		
		while (flag == -1 && strlen(cpf) > 0){
			printf("Insira um CPF CADASTRADO: \n");
			fflush(stdin);
			gets(cpf);
		
			flag = buscaCPF(ptr, cpf);
		}

		flag = verificaCPFPedido(ptr, cpf);
		
		if (flag == 1) {
			if(strlen(cpf) > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpMotoqueiro), 1, ptr);
				fseek(ptr, flag, 0);	

				printf("---> Dados do MOTOQUEIRO <---\n");
				printf("CPF: %s\n", aux.cpf);
				printf("NOME: %s\n", aux.nome);
				printf("ENDERECO: %s\n", aux.endereco);
				printf("TELEFONE: %s\n", aux.telefone);
				printf("DATA DE ADMISSAO: %d/%d/%d\n\n", aux.data.d, aux.data.m, aux.data.a);
				printf("STATUS: %c\n", aux.status);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpMotoqueiro), 1, ptr);
					printf("\nMotoqueiro excluido com sucesso\n");
				} else
					printf("\nExclusao nao realizada\n");
			}			
		} else {
			printf("Motoqueiro cadastrado com pedido ativo!\nExclusao nao realizada\n");
		}

		
		fclose(ptr);
		getch();
		clrscr();
	}
}

int verificaTelPedido(FILE *ptr, char tel[30]) {
	TpPedido aux;

	fseek(ptr, 0, 0);

	fread(&aux, sizeof(TpPedido), 1, ptr);
	while(!feof(ptr) && (stricmp(aux.telefone, tel) != 0 || aux.status != 'A')) 
		fread(&aux, sizeof(TpPedido), 1, ptr);
	
	if(stricmp(aux.telefone, tel) == 0 && aux.status == 'A')
		return 1;
	else
		return -1;

}

void exclusaoLogicaCliente(void){
	TpCliente aux;
	char tel[30];
	int flag;
	
	FILE *ptr = fopen("Clientes.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("\nDigite o TELEFONE do cliente que deseja excluir: \n");
		fflush(stdin);
		gets(tel);
		
		flag = buscaSentinelaTelefone(ptr, tel);
		
		while (flag == -1 && strlen(tel) > 0){
			printf("Insira um telefone CADASTRADO: \n");
			fflush(stdin);
			gets(tel);
		
			flag = buscaSentinelaTelefone(ptr, tel);
		}

		flag = verificaTelPedido(ptr, tel);

		if (flag == 1) {
			if(strlen(tel) > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpCliente), 1, ptr);
				fseek(ptr, flag, 0);	

				printf("---> Dados do CLIENTE <---\n");
				printf("TELEFONE: %s\n", aux.telefone);
				printf("NOME: %s\n", aux.nome);
				printf("CIDADE: %s\n", aux.cidade);
				printf("ENDERECO: %s\n", aux.endereco);
				printf("CEP: %s\n", aux.cep);
				printf("STATUS: %c\n", aux.status);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpCliente), 1, ptr);
					printf("\nTelefone excluido com sucesso\n");
				} else
					printf("\nExclusao nao realizada\n");
			}
		} else {
			printf("Cliente cadastrado com pedido ativo!\nExclusao nao realizada\n");
		}

		fclose(ptr);
		getch();
		clrscr();
	}
}

void relatorioCliente(void) {
	TpPedido aux;
	TpCliente aux2;
	TpPizza aux3;

	FILE *ptrcliente = fopen("Clientes.dat", "rb+");
	FILE *ptrpedido = fopen("Pedidos.dat", "rb+");
	FILE *ptrpizza = fopen("Pizzas.dat", "rb+");

	int pos, count = 0, tamanhoPedidos, flag, countLista = 0;
	float valor, total = 0;
	char telAtual[20];

	fseek(ptrpedido, 0, 2);
	tamanhoPedidos = ftell(ptrpedido) / sizeof(TpPedido);

	char listaTel[tamanhoPedidos][30];

	//Pegar numero de um cliente
	//Pesquisar em todos os pedidos esse numero
	//Pegar o preco da pizza em cada um deles
	//Imprimir e repetir

	if (ptrcliente == NULL || ptrpedido == NULL || ptrpizza == NULL) {
		printf("ERRO de abertura\n");
	} else {
		while (count < tamanhoPedidos) {
			total = 0, flag = 0;
			//Pegar numero de um cliente
			fseek(ptrpedido, 0, 0);
			fread (&aux, sizeof(TpPedido), 1, ptrpedido);		
			while (!feof(ptrpedido) && !flag) {
				
				if (strcmp(telAtual, aux.telefone) != 0 && aux.status == 'A') {
					strcpy(telAtual, aux.telefone);

					for (int j = 0; j < countLista; j++) { // Checar se o num atual ja foi o atual anteriormente
						if (strcmp(listaTel[j], telAtual) == 0) {
							flag = 1;
						}
					}	

					if (flag == 1) {
						flag = 0;
					} else {
						flag = 1;
						strcpy(listaTel[countLista], telAtual);
						countLista++;							
					}					


				}

				fread (&aux, sizeof(TpPedido), 1, ptrpedido);
			}

			//Informaçoes
			printf("\nTELEFONE: %s\n", telAtual);
			pos = buscaSentinelaTelefone(ptrcliente, telAtual);
			fseek(ptrcliente, pos, 0);
			fread(&aux2, sizeof(TpCliente), 1, ptrcliente);
			printf("NOME: %s\n", aux2.nome);
			printf("Pizzas pedidas: \n");
			
			//Buscar detalhes do pedido
			fseek(ptrpedido, 0, 0);
			fseek(ptrcliente, 0, 0);
			//Passar por todos os pedidos, ver se o cliente é o atual, se for buscar valor da pizza
			fread (&aux, sizeof(TpPedido), 1, ptrpedido);	
			while (!feof(ptrpedido)) {

				if (strcmp(telAtual, aux.telefone) == 0) {
					//Se o tel atual for igual ao do pedido lido precisa-se buscar o valor
					valor = buscaPreco(ptrpizza, aux.codigo);
					total += valor;
					count++;

					//Imprimir pizza
					pos = buscaBinariaCodigo(ptrpizza, aux.codigo);
					fseek(ptrpizza, pos, 0);
					fread(&aux3, sizeof(TpPizza), 1, ptrpizza);
					printf("1x %s - R$ %.2f\n", aux3.descricao, valor);
				}
				
				fread(&aux, sizeof(TpPedido), 1, ptrpedido);
			}

			printf("Total gasto = R$ %.2f\n\n", total);			
		}

		getch();

		fclose(ptrcliente);
		fclose(ptrpedido);
		fclose(ptrpizza);
	}
}

float buscaPreco(FILE *ptrpizza, int cod) {
	TpPizza aux;
	int pos;

	pos = buscaBinariaCodigo(ptrpizza, cod);
	
	fseek(ptrpizza, pos, 0);
	fread(&aux, sizeof(TpPizza), 1, ptrpizza);
	//printf("\nValor achado: %f\n", aux.valor);

	return aux.valor;
}

void selecaoDiretaPizza(void) {
	TpPizza A, B;
	FILE *ptr = fopen("Pizzas.dat", "rb+");

	fseek(ptr, 0, 2);
	int tamanho = ftell(ptr) / sizeof(TpPizza);

	int maior, pos, i;

	while (tamanho > 0) {
		fseek(ptr, 0, 0);//Ir para primeiro reg
		fread(&A, sizeof(TpPizza), 1, ptr);//Ler conteudo
		maior = A.codigo;

		//Achar maior registro
		pos = 0;
		for (i = 0; i < tamanho; i++) {
			fseek(ptr, i * sizeof(TpPizza), 0);//Ir para primeiro reg
			fread(&A, sizeof(TpPizza), 1, ptr);//Ler conteudo
			//printf("Registro: %d, codigo: %d\n", i, A.codigo);

			//Comparar
			if (maior < A.codigo) {
				//printf("%d eh maior que %d\n", A.codigo, maior);
				maior = A.codigo;
				pos = i;
				//printf("maior %d pos %d\n", maior, pos);
			}
		}

		//Colocar maior na ultima posição
		fseek(ptr, (tamanho - 1) * sizeof(TpPizza), 0); //Pegar ultimo reg
		fread(&A, sizeof(TpPizza), 1, ptr);
		//printf("Ultima posicao contem: %d\n", A.codigo);

		fseek(ptr, pos * sizeof(TpPizza), 0); //Pegar maior reg
		fread(&B, sizeof(TpPizza), 1, ptr);
		//printf("Maior posicao contem: %d\n", B.codigo);

		if (pos < tamanho - 1) {
			fseek(ptr, (tamanho - 1) * sizeof(TpPizza), 0);
			fwrite(&B, sizeof(TpPizza), 1, ptr);
			//printf("%d colocado na pos %d", B.codigo, (tamanho - 1));

			fseek(ptr, pos * sizeof(TpPizza), 0);
			fwrite(&A, sizeof(TpPizza), 1, ptr);
			//printf(" %d colocado na pos %d\n", A.codigo, pos);
			//printf("Trocou\n\n");	
		}

		tamanho--;
	}
	
	fclose(ptr);
}

void bubbleSortPedido(void) {
	TpPedido A, B;
	FILE *ptr = fopen("Pedidos.dat", "rb+");

	fseek(ptr, 0, 2);
	int tamanho = ftell(ptr) / sizeof(TpPedido);
	int qtdA, qtdB;

	while (tamanho > 0) {
		for (int i = 0; i < tamanho - 1; i++) {
			//Ler primeiro e segundo registros do arquivo
			qtdA = i + 1;
			fseek(ptr, qtdA * sizeof(TpPedido), 0);
			fread(&A, sizeof(TpPedido), 1, ptr);
			//printf("\nPrimeiro registro: %d\n", A.numero);
			
			qtdB = qtdA - 1;
			fseek(ptr, qtdB * sizeof(TpPedido), 0);
			fread(&B, sizeof(TpPedido), 1, ptr);
			//printf("Segundo registro: %d\n", B.numero);

			//Comparar
			if (B.numero > A.numero) {
				//Trocar
				//Ir para primeira pos
				fseek(ptr, qtdA * sizeof(TpPedido), 0);
				fwrite(&B, sizeof(TpPedido), 1, ptr);

				//Ir para segunda e copiar a primeira
				fseek(ptr, qtdB * sizeof(TpPedido), 0);
				fwrite(&A, sizeof(TpPedido), 1, ptr);
			}
		}

		tamanho--;
	}
	
	fclose(ptr);
}

void insercaoDiretaCliente(void) {
	TpCliente A, B, aux;

	FILE *ptr = fopen("Clientes.dat", "rb+");

	int quantidade;

	fseek(ptr, 0, 2);
	quantidade = ftell(ptr) / sizeof(TpCliente);
	//quantidade++;
	//printf("Tamanho total eh %d quantidade eh %d", ftell(ptr), quantidade);

	int qtdA = quantidade - 1;
	fseek(ptr, qtdA * sizeof(TpCliente), 0);
	fread(&A, sizeof(TpCliente), 1, ptr);
	//printf("\nUltimo registro: %s\n", A.nome);
	
	int qtdB = qtdA - 1;
	fseek(ptr, qtdB * sizeof(TpCliente), 0);
	fread(&B, sizeof(TpCliente), 1, ptr);
	//printf("Penultimo registro: %s\n", B.nome);

	while(qtdB >= 0 && stricmp(A.nome, B.nome) < 0) {
		//aux = B;
		fseek(ptr, qtdB * sizeof(TpCliente), 0); //Foi para penultima posição
		fwrite(&A, sizeof(TpCliente), 1, ptr); //coloca o conteudo da ultima na penultima

		fseek(ptr, qtdA * sizeof(TpCliente), 0);
		fwrite(&B, sizeof(TpCliente), 1, ptr);

		qtdA--;
		fseek(ptr, qtdA * sizeof(TpCliente), 0);
		fread(&A, sizeof(TpCliente), 1, ptr);
		//printf("\nUltimo registro da segunda iteracao: %s\n", A.nome);
		
		qtdB--;
		fseek(ptr, qtdB * sizeof(TpCliente), 0);
		fread(&B, sizeof(TpCliente), 1, ptr);
		//printf("Penultimo registro da segunda iteracao: %s\n", B.nome);
	}

	fclose(ptr);
}

void ordenacaoExaustivaCliente(void){
	int a, b, qtde;
	TpCliente regA, regB;
	
	FILE *ptrarquivo = fopen("Clientes.dat", "rb+");
	
	if(ptrarquivo == NULL)
		printf("ERRO na abertura\n");
	else{
		fseek(ptrarquivo,0, 2); //manda o ponteiro para o final
		qtde = ftell(ptrarquivo) / sizeof(TpCliente); //descobre a quantidade de registros
		for(a = 0 ; a < qtde - 1; a++)
			for(b = a + 1; b < qtde ; b++){
				
				fseek(ptrarquivo, a * sizeof(TpCliente), 0);
				fread(&regA, sizeof(TpCliente), 1, ptrarquivo);
				fseek(ptrarquivo, b * sizeof(TpCliente), 0);
				fread(&regB, sizeof(TpCliente), 1, ptrarquivo);
				
				if(stricmp(regA.nome, regB.nome) > 0){ //se o registro A for maior que o registro B // faz a troca	
					//escreve RegA em B
					fseek(ptrarquivo, b * sizeof(TpCliente), 0);
					fwrite(&regA, sizeof(TpCliente), 1, ptrarquivo);
					
					//escreve RegB em A
					fseek(ptrarquivo, a * sizeof(TpCliente), 0);
					fwrite(&regB, sizeof(TpCliente), 1, ptrarquivo);
				}
			}
			
		fclose(ptrarquivo);
	}
}

void ordenacaoExaustivaMotoqueiro(void){
	int a, b, qtde;
	TpMotoqueiro regA, regB;
	
	FILE *ptrarquivo = fopen("Motoqueiros.dat", "rb+");
	
	if(ptrarquivo == NULL)
		printf("ERRO na abertura\n");
	else{
		fseek(ptrarquivo,0, 2); //manda o ponteiro para o final
		qtde = ftell(ptrarquivo) / sizeof(TpMotoqueiro); //descobre a quantidade de registros
		for(a = 0 ; a < qtde - 1; a++)
			for(b = a + 1; b < qtde ; b++){
				
				fseek(ptrarquivo, a * sizeof(TpMotoqueiro), 0);
				fread(&regA, sizeof(TpMotoqueiro), 1, ptrarquivo);
				fseek(ptrarquivo, b * sizeof(TpMotoqueiro), 0);
				fread(&regB, sizeof(TpMotoqueiro), 1, ptrarquivo);
				
				if(stricmp(regA.nome, regB.nome) > 0){ //se o registro A for maior que o registro B // faz a troca	
					//escreve RegA em B
					fseek(ptrarquivo, b * sizeof(TpMotoqueiro), 0);
					fwrite(&regA, sizeof(TpMotoqueiro), 1, ptrarquivo);
					
					//escreve RegB em A
					fseek(ptrarquivo, a * sizeof(TpMotoqueiro), 0);
					fwrite(&regB, sizeof(TpMotoqueiro), 1, ptrarquivo);
				}
			}
			
		fclose(ptrarquivo);
	}
}

void ordenacaoExaustivaPizza(void){
	int a, b, qtde;
	TpPizza regA, regB;
	
	FILE *ptrarquivo = fopen("Pizzas.dat", "rb+");
	
	if(ptrarquivo == NULL)
		printf("ERRO na abertura\n");
	else{
		fseek(ptrarquivo,0, 2); //manda o ponteiro para o final
		qtde = ftell(ptrarquivo) / sizeof(TpPizza); //descobre a quantidade de registros
		for(a = 0 ; a < qtde - 1; a++)
			for(b = a + 1; b < qtde ; b++){
				
				fseek(ptrarquivo, a * sizeof(TpPizza), 0);
				fread(&regA, sizeof(TpPizza), 1, ptrarquivo);
				fseek(ptrarquivo, b * sizeof(TpPizza), 0);
				fread(&regB, sizeof(TpPizza), 1, ptrarquivo);
				
				if(regA.codigo > regB.codigo){ //se o registro A for maior que o registro B // faz a troca	
					//escreve RegA em B
					fseek(ptrarquivo, b * sizeof(TpPizza), 0);
					fwrite(&regA, sizeof(TpPizza), 1, ptrarquivo);
					
					//escreve RegB em A
					fseek(ptrarquivo, a * sizeof(TpPizza), 0);
					fwrite(&regB, sizeof(TpPizza), 1, ptrarquivo);
				}
			}
			
		fclose(ptrarquivo);
	}

}

void ordenacaoExaustivaPedido(void){
	int a, b, qtde;
	TpPedido regA, regB;
	
	FILE *ptrarquivo = fopen("Pedidos.dat", "rb+");
	
	if(ptrarquivo == NULL)
		printf("ERRO na abertura\n");
	else{
		fseek(ptrarquivo,0, 2); //manda o ponteiro para o final
		qtde = ftell(ptrarquivo) / sizeof(TpPedido); //descobre a quantidade de registros
		for(a = 0 ; a < qtde - 1; a++)
			for(b = a + 1; b < qtde ; b++){
				
				fseek(ptrarquivo, a * sizeof(TpPedido), 0);
				fread(&regA, sizeof(TpPedido), 1, ptrarquivo);
				fseek(ptrarquivo, b * sizeof(TpPedido), 0);
				fread(&regB, sizeof(TpPedido), 1, ptrarquivo);
				
				if(regA.numero > regB.numero){ //se o registro A for maior que o registro B // faz a troca	
					//escreve RegA em B
					fseek(ptrarquivo, b * sizeof(TpPedido), 0);
					fwrite(&regA, sizeof(TpPedido), 1, ptrarquivo);
					
					//escreve RegB em A
					fseek(ptrarquivo, a * sizeof(TpPedido), 0);
					fwrite(&regB, sizeof(TpPedido), 1, ptrarquivo);
				}
			}
			
		fclose(ptrarquivo);
	}
}

void filtrarLetra(void) {
	TpCliente aux;
	char letra;

	FILE *ptr = fopen("Clientes.dat", "rb");

	fread(&aux, sizeof(TpCliente), 1, ptr);

	if (ptr == NULL) {
		printf("\nErro de abertura!");
	} else {
		printf("\nDigite a inicial que quer filtrar o nome dos clientes: \n");
		fflush(stdin);
		letra = getch();


		//Passar letra por parametro pois é o que pede no PDF
		exibirFiltro(ptr, letra);

		fclose(ptr);
	}

	getch();
}

void exibirFiltro(FILE *ptr, char letra) {
	TpCliente aux;
	int cont;

	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpCliente), 1, ptr);

	cont = 0;
	while(!feof(ptr)) {

		if (tolower(aux.nome[0]) == tolower(letra)) {
			if (cont == 0);
				printf("\n###Clientes que comecam com %c ###\n", toupper(letra));

			printf("Nome: %s\n", aux.nome);

			cont++;
		}

		fread(&aux, sizeof(TpCliente), 1, ptr);
	}

	if (cont == 0) {
		printf("Nao existem clientes com essa inicial");
	}
	
}

void estadoPizza(void) {
	TpPedido aux;
	TpPizza auxPizza;
	int cont, flag;
	FILE *ptr = fopen("Pedidos.dat", "rb");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb");

	fread(&aux, sizeof(TpPedido), 1, ptr);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

	if (ptr == NULL || ptrPizza == NULL) {
		printf("Erro de abertura!");
	} else {
		cont = 0;
		while (!feof(ptr)) {
			
			if (strcmp(aux.situacao, "Em preparacao") == 0) {
				if (cont == 0)
					printf("\n###Pizzas em preparacao###");

				flag = buscaBinariaCodigo(ptrPizza, aux.codigo);
				fseek(ptrPizza, flag, 0);
				fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

				printf("\nNumero do pedido: %d\n", aux.numero);
				//printf("Codigo da pizza: %d\n", aux.codigo);
				printf("Descricao: %s\n", auxPizza.descricao);
				printf("Descricao da pizza: %s\n", aux.situacao);
				printf("Valor: %.2f\n", auxPizza.valor);

				cont++;
			}

			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		if (cont == 0) {
			printf("\nNenhuma Pizza em Andamento");
		}

		fseek(ptr, 0, 0); //Volta ptr de pedidos pra fazer mais um loop
		fread(&aux, sizeof(TpPedido), 1, ptr); 
		cont = 0;
		while (!feof(ptr)) {
			
			if (strcmp(aux.situacao, "Em rota de entrega") == 0) {
				if (cont == 0)
					printf("\n###Pizzas em rota###");

				flag = buscaBinariaCodigo(ptrPizza, aux.codigo);
				fseek(ptrPizza, flag, 0);
				fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

				printf("\nNumero do pedido: %d\n", aux.numero);
				//printf("Codigo da pizza: %d\n", aux.codigo);
				printf("Descricao: %s\n", auxPizza.descricao);
				printf("Descricao da pizza: %s\n", aux.situacao);
				printf("Valor: %.2f\n", auxPizza.valor);

				cont++;
			}

			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		if (cont == 0) {
			printf("\nNenhuma Pizza em rota de entrega");
		}

		fclose(ptr);
		fclose(ptrPizza);
	}

	getch();
}

void exclusaoFisicaPedido(void){
	clrscr();
	TpPedido aux;
	int flag, auxnum;
	
	FILE *ptr = fopen("Pedidos.dat", "rb");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("Digite o NUMERO do pedido que deseja excluir: \n");
		fflush(stdin);
		scanf("%d", &auxnum);
		
		flag = buscaSeqIndexadaPedido(ptr, auxnum);
		
		while (flag == -1 && auxnum > 0){
			printf("Insira um numero do pedido CADASTRADO: \n");
			fflush(stdin);
			scanf("%d", &auxnum);
		
			flag = buscaSeqIndexadaPedido(ptr, auxnum);
		}
		
		if(auxnum > 0){
			fseek(ptr, flag, 0); //vai para a pos encontrada
			fread(&aux, sizeof(TpPedido), 1, ptr);
			printf("---> Dados do PEDIDO <---\n");
			printf("Numero: %d\n", aux.numero);
			printf("Telefone: %s\n", aux.telefone);
			printf("Codigo da pizza: %d\n", aux.codigo);
			printf("CPF: %s\n", aux.cpf);
			printf("Situacao: %s\n", aux.situacao);
			printf("Data do pedido: %d/%d/%d \n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
			
			printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
			
			if(toupper(getche()) == 'Y'){
				FILE *ptrnovo = fopen("novo.dat", "wb"); //wb permite criar o arquivo //se ja estiver criado o arquivo � zerado
				fseek(ptr, 0, 0);
				fread(&aux, sizeof(TpPedido), 1, ptr);
					
				while(!feof(ptr)){ //enquanto o arquivo p essoa n�o chegar no fim
					if(auxnum != aux.numero)
						fwrite(&aux, sizeof(TpPedido), 1, ptrnovo);
			
					fread(&aux, sizeof(TpPedido), 1, ptr);//ve se nao � EOF
				}
				
				//fecha e renomeia os arquivos
					fclose(ptr);
					fclose(ptrnovo);
					remove("Pedidos.dat");
					rename("novo.dat", "Pedidos.dat");
					printf("\nExclusao realizada com sucesso!\n");

			} else{
				printf("\nExclusao nao realizada\n");
				fclose(ptr);
			}
		}
		fclose(ptr);
		getch();
		clrscr();	
	}
}

void excluirClienteInativo(void) {
	TpCliente aux;
	FILE *ptr = fopen("Clientes.dat", "rb");

	if (ptr == NULL){
		printf("Erro de abertura\n");
	} else {
		FILE *ptrnovo = fopen("novo.dat", "wb"); //wb permite criar o arquivo //se ja estiver criado o arquivo � zerado
		fseek(ptr, 0, 0);
		fread(&aux, sizeof(TpCliente), 1, ptr);
			
		while(!feof(ptr)){ //enquanto o arquivo p essoa n�o chegar no fim
			if(aux.status != 'I')
				fwrite(&aux, sizeof(TpCliente), 1, ptrnovo);
	
			fread(&aux, sizeof(TpCliente), 1, ptr);//ve se nao � EOF
		}
		
		//fecha e renomeia os arquivos
		fclose(ptr);
		fclose(ptrnovo);
		remove("Clientes.dat");
		rename("novo.dat", "Clientes.dat");
		printf("\nExclusao de inativos realizada com sucesso!\n");	
	}
}

void exclusaoFisicaCliente(void){
	clrscr();
	TpCliente aux;
	int flag;
	char tel[30];

	FILE *ptr = fopen("Clientes.dat", "rb");
	
	if (ptr == NULL) {
		printf("Erro de abertura\n");
	} else {

		fclose(ptr);
		excluirClienteInativo();
		FILE *ptr = fopen("Clientes.dat", "rb");

		printf("Digite o TELEFONE do cliente que deseja excluir: \n");
		fflush(stdin);
		gets(tel);
		
		flag = buscaSentinelaTelefone(ptr, tel);
		while (flag == -1 && strlen(tel) > 0){
			printf("Insira um TELEFONE CADASTRADO: \n");
			fflush(stdin);
			gets(tel);
		
			flag = buscaSentinelaTelefone(ptr, tel);
		}

		if (verificaTelPedido(ptr, tel)  == -1) {
			if(strlen(tel) > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpCliente), 1, ptr);
				printf("---> Dados do CLIENTE <---\n");
				printf("Telefone: %s\n", aux.telefone);
				printf("Nome: %s\n", aux.nome);
				printf("Endereco: %s\n", aux.endereco);
				printf("Cidade: %s\n", aux.cidade);
				printf("Cep: %s\n", aux.cep);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				
				if(toupper(getche()) == 'Y'){
					FILE *ptrnovo = fopen("novo.dat", "wb"); //wb permite criar o arquivo //se ja estiver criado o arquivo � zerado
					fseek(ptr, 0, 0);
					fread(&aux, sizeof(TpCliente), 1, ptr);
						
					while(!feof(ptr)){ //enquanto o arquivo p essoa n�o chegar no fim
						if(strcmp(tel, aux.telefone) != 0)
							fwrite(&aux, sizeof(TpCliente), 1, ptrnovo);
				
						fread(&aux, sizeof(TpCliente), 1, ptr);//ve se nao � EOF
					}
					
					//fecha e renomeia os arquivos
						fclose(ptr);
						fclose(ptrnovo);
						remove("Clientes.dat");
						rename("novo.dat", "Clientes.dat");
						printf("\nExclusao realizada com sucesso!\n");

				} else{
					printf("\nExclusao nao realizada\n");
					fclose(ptr);
				}
			}
		} else {
			printf("Cliente cadastrado com pedido ativo!\nExclusao nao realizada\n");
		}

		fclose(ptr);
		getch();
		clrscr();		
	}
}

void exclusaoFisicaMotoqueiro(void){
	clrscr();
	TpMotoqueiro aux;
	int flag;
	char cpf[30];

	FILE *ptr = fopen("Motoqueiros.dat", "rb");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("Digite o CPF do motoqueiro que deseja excluir: \n");
		fflush(stdin);
		gets(cpf);
		
		flag = buscaCPF(ptr, cpf);
		
		while (flag == -1 && strlen(cpf) > 0){
			printf("Insira um CPF CADASTRADO: \n");
			fflush(stdin);
			gets(cpf);
		
			flag = buscaCPF(ptr, cpf);
		}

		if (verificaCPFPedido(ptr, cpf) == -1) {
			if(strlen(cpf) > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
				printf("---> Dados do MOTOQUEIRO <---\n");
				printf("CPF: %s\n", aux.cpf);
				printf("Nome: %s\n", aux.nome);
				printf("Endereco: %s\n", aux.endereco);
				printf("Telefone: %s\n", aux.telefone);
				printf("Data de admissao: %d/%d/%d \n", aux.data.d, aux.data.m, aux.data.a);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				
				if(toupper(getche()) == 'Y'){
					FILE *ptrnovo = fopen("novo.dat", "wb"); //wb permite criar o arquivo //se ja estiver criado o arquivo � zerado
					fseek(ptr, 0, 0);
					fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
						
					while(!feof(ptr)){ //enquanto o arquivo p essoa n�o chegar no fim
						if(strcmp(cpf, aux.cpf) != 0)
							fwrite(&aux, sizeof(TpMotoqueiro), 1, ptrnovo);
				
						fread(&aux, sizeof(TpMotoqueiro), 1, ptr);//ve se nao � EOF
					}
					
					//fecha e renomeia os arquivos
						fclose(ptr);
						fclose(ptrnovo);
						remove("Motoqueiros.dat");
						rename("novo.dat", "Motoqueiros.dat");
						printf("\nExclusao realizada com sucesso!\n");

				} else{
					printf("\nExclusao nao realizada\n");
					fclose(ptr);
				}
			}			
		} else {
			printf("Motoqueiro cadastrado com pedido ativo!\nExclusao nao realizada\n");
		}
	
		fclose(ptr);
		getch();
		clrscr();	
	}
}

void exclusaoFisicaPizza(void){
	clrscr();
	TpPizza aux;
	int flag, auxcod;

	FILE *ptr = fopen("Pizzas.dat", "rb");
	
	if(ptr == NULL)
		printf("ERRO de abertura\n");
	else{
		printf("Digite o CODIGO DA PIZZA que deseja excluir: \n");
		fflush(stdin);
		scanf("%d",&auxcod);
		
		flag = buscaBinariaCodigo(ptr, auxcod);
		
		while (flag == -1 && auxcod > 0){
			printf("Insira um codigo da pizza CADASTRADO: \n");
			fflush(stdin);
			scanf("%d",&auxcod);
			
			flag = buscaBinariaCodigo(ptr, auxcod);
		}

		if(verificaCodPedido(ptr, auxcod) == -1) {
			if(auxcod > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpPizza), 1, ptr);
				printf("---> Dados da PIZZA <---\n");
				printf("Codigo: %d\n", aux.codigo);
				printf("Descricao: %s\n", aux.descricao);
				printf("Valor: %.2f\n", aux.valor);
				
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
				
				if(toupper(getche()) == 'Y'){
					FILE *ptrnovo = fopen("novo.dat", "wb"); //wb permite criar o arquivo //se ja estiver criado o arquivo � zerado
					fseek(ptr, 0, 0);
					fread(&aux, sizeof(TpPizza), 1, ptr);
						
					while(!feof(ptr)){ //enquanto o arquivo p essoa n�o chegar no fim
						if( aux.codigo != auxcod)
							fwrite(&aux, sizeof(TpPizza), 1, ptrnovo);
				
						fread(&aux, sizeof(TpPizza), 1, ptr);//ve se nao � EOF
					}
					
					//fecha e renomeia os arquivos
						fclose(ptr);
						fclose(ptrnovo);
						remove("Pizzas.dat");
						rename("novo.dat", "Pizzas.dat");
						printf("\nExclusao realizada com sucesso!\n");

				} else{
					printf("\nExclusao nao realizada\n");
					fclose(ptr);
				}
			}			
		} else {
			printf("Pizza cadastrada com pedido ativo!\nExclusao nao realizada\n");
		}
		
		fclose(ptr);
		getch();
		clrscr();	
	}
}

void alterarPedido(void){
	clrscr();
	TpPedido aux;
	int flag;
	char op;
	
	FILE *ptrpedido = fopen("Pedidos.dat", "rb+");
	FILE *ptrcliente = fopen("Clientes.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");
	FILE *ptrpizza = fopen("Pizzas.dat", "rb+");
	
	if(ptrpedido == NULL)
		printf("ERRO de abertura \n");
	else{
		printf("Insira o NUMERO do Pedido que desja ALTERAR: \n");
		fflush(stdin);
		scanf("%d",&aux.numero);
		
		flag = buscaSeqIndexadaPedido(ptrpedido, aux.numero);
		
		while (flag == -1 && aux.numero > 0){
			printf("Insira um NUMERO do pedido cadastrado: \n");
			fflush(stdin);
			scanf("%d",&aux.numero);
			
			flag = buscaSeqIndexadaPedido(ptrpedido, aux.numero);
		}
		
		if(aux.numero > 0){
			fseek(ptrpedido, flag, 0);
			fread(&aux,sizeof(TpPedido), 1, ptrpedido);
			fseek(ptrpedido, flag, 0);

			printf("\n###Conteudo do Registro###\n");
			printf("NUMERO: %d\n", aux.numero);
			printf("TELEFONE: %s\n", aux.telefone);
			printf("CODIGO: %d\n", aux.codigo);
			printf("CPF: %s\n", aux.cpf);
			printf("SITUACAO: %s\n", aux.situacao);
			printf("DATA DO PEDIDO: %d/%d/%d\n\n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);

			printf("O que deseja ALTERAR?\n");
			printf("[A] NUMERO\n");
			printf("[B] TELEFONE\n");
			printf("[C] CODIGO DA PIZZA\n");
			printf("[D] CPF DO MOTOQUEIRO\n");
			printf("[E] SITUACAO\n");
			printf("[F] DATA DO PEDIDO\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("\nInsira o novo NUMERO do pedido: \n");
				scanf("%d", &aux.numero);
				
				while(aux.numero <= 0){
					printf("Insira um numero VALIDO: \n");
					scanf("%d", &aux.numero);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("\nInsira o novo TELEFONE do pedido: \n");
				fflush(stdin);
				gets(aux.telefone);
				flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
				
				while(strlen(aux.telefone) <= 0 || flag == -1){
					printf("Insira um telefone CADASTRADO: \n");
					fflush(stdin);
					gets(aux.telefone);
					flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("\nInsira o novo CODIGO DA PIZZA do pedido \n");
				scanf("%d", &aux.codigo);
				flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
				
				while(aux.codigo < 0 || flag == -1){
					printf("Insira um codigo da pizza CADASTRADO \n");
					scanf("%d", &aux.codigo);
					flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("\nInsira o novo CPF DO MOTOQUEIRO do pedido \n");
				fflush(stdin);
				gets(aux.cpf);
				flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				
				while(strlen(aux.cpf) <= 0 || flag == -1){
					printf("Insira um cpf CADASTRADO: \n");
					fflush(stdin);
					gets(aux.cpf);
					flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				}
				
				printf("Dados ALTERADOS\n");
			} else if(op == 'E'){
				printf("\nPara qual SITUACAO do pedido voce deseja alterar: \n");
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
				
				printf("\nDados ALTERADOS\n");
			}else if(op == 'F'){
				printf("\nInsira a nova DATA DO PEDIDP: [dd mm aaaa]\n");
				scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
				
				while(aux.dataPedido.d > 31 || aux.dataPedido.d < 1 || aux.dataPedido.m > 12 || aux.dataPedido.m < 1 || aux.dataPedido.a > 2024 || aux.dataPedido.a < 1){
					printf("Insira uma data VALIDA\n");
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
				}
				
				printf("\nDados ALTERADOS\n");
			}else
				printf("Alteracao de dados CANCELADA\n");
				
			fwrite(&aux, sizeof(TpPedido), 1, ptrpedido);

		}
		
		getch();
		fclose(ptrpedido);
		fclose(ptrpizza);
		fclose(ptrcliente);
		fclose(ptrmotoqueiro);
		clrscr();
	}
	
}

void alterarPizza(void){
	clrscr();
	TpPizza aux;
	int flag;
	char op;
	
	FILE *ptr = fopen("Pizzas.dat", "rb+");
	
	if(ptr == NULL)
		printf("ERRO de abertura \n");
	else{
		printf("Insira o CODIGO da Pizza que desja ALTERAR: \n");
		fflush(stdin);
		scanf("%d",&aux.codigo);	
		flag = buscaBinariaCodigo(ptr, aux.codigo);
		
		while (flag == -1 && aux.codigo > 0){
			printf("Insira um CODIGO cadastrado: \n");
			fflush(stdin);
			scanf("%d",&aux.codigo);
			flag = buscaBinariaCodigo(ptr, aux.codigo);

		}
		
		if(aux.codigo > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpPizza), 1, ptr);
			fseek(ptr, flag, 0);

			printf("\n###Conteudo do Registro###\n");
			printf("CODIGO: %d\n", aux.codigo);
			printf("DESCRICAO: %s\n", aux.descricao);
			printf("VALOR: %.2f\n\n", aux.valor);

			printf("O que deseja ALTERAR?\n");
			printf("[A] CODIGO\n");
			printf("[B] DESCRICAO\n");
			printf("[C] VALOR\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("\nInsira o novo CODIGO: \n");
				scanf("%d", &aux.codigo);
				
				while(aux.codigo <= 0){
					printf("Insira um codigo VALIDO: \n");
					scanf("%d", &aux.codigo);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("\nInsira a nova DESCRICAO: \n");
				fflush(stdin);
				gets(aux.descricao);
				
				while(strlen(aux.descricao) <= 0){
					printf("Insira uma descricao VALIDA: \n");
					gets(aux.descricao);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("\nInsira o novo VALOR: \n");
				scanf("%f", &aux.valor);
				
				while(aux.valor <= 0){
					printf("Insira um valor VALIDO: \n");
					scanf("%f", &aux.valor);
				}
				
				printf("Dados ALTERADOS\n");
			}else
				printf("\nAlteracao de dados CANCELADA\n");
			
			fwrite(&aux, sizeof(TpPizza), 1, ptr);

		}
		
		getch();
		fclose(ptr);
		clrscr();
	}
	
}

void alterarMotoqueiro(void){
	clrscr();
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
		flag = buscaCPF(ptr, aux.cpf);
		
		while (flag == -1 && strlen(aux.cpf) > 0) {
			printf("Insira um CPF cadastrado:\n");
			fflush(stdin);
			gets(aux.cpf);
	
			flag = buscaCPF(ptr, aux.cpf);
			//printf("\nO tamanho de um reg eh: %d e o ponteiro esta em: %d\n", sizeof(TpMotoqueiro), flag);
		}
		
		if(strlen(aux.cpf) > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpMotoqueiro), 1, ptr);
			fseek(ptr, flag, 0);	

			printf("\n###Conteudo do Registro###\n");
			printf("CPF: %s\n", aux.cpf);
			printf("NOME: %s\n", aux.nome);
			printf("ENDERECO: %s\n", aux.endereco);
			printf("TELEFONE: %s\n", aux.telefone);
			printf("DATA DE ADMISSAO: %d/%d/%d\n\n", aux.data.d, aux.data.m, aux.data.a);

			printf("O que deseja ALTERAR?\n");
			printf("[A] CPF\n");
			printf("[B] NOME\n");
			printf("[C] ENDERECO\n");
			printf("[D] TELEFONE\n");
			printf("[E] DATA DE ADMISSAO\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("\nInsira o novo CPF: \n");
				gets(aux.cpf);
				flag = validarCPF(aux.cpf);
				
				while(strlen(aux.cpf) <= 0 || flag != 1){
					printf("Insira um cpf VALIDO: \n");
					gets(aux.cpf);
					flag = validarCPF(aux.cpf);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("\nInsira o novo NOME: \n");
				gets(aux.nome);
				
				while(strlen(aux.nome) <= 0){
					printf("Insira um nome VALIDO: \n");
					gets(aux.nome);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("\nInsira o novo ENDERECO: \n");
				gets(aux.endereco);
				
				while(strlen(aux.endereco) <= 0){
					printf("Insira um endereco VALIDO: \n");
					gets(aux.endereco);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("\nInsira o novo TELEFONE: \n");
				gets(aux.telefone);
				
				while(strlen(aux.telefone) <= 0){
					printf("Insira um telefone VALIDO: \n");
					gets(aux.telefone);
				}
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'E'){
				printf("\nInsira a nova DATA DE ADMISSAO: [dd mm aaaa]\n");
				scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
				
				while(aux.data.d > 31 || aux.data.d < 1 || aux.data.m > 12 || aux.data.m < 1 || aux.data.a > 2024 || aux.data.a < 1){
					printf("Insira uma data VALIDA\n");
					scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
				}
				
				printf("Dados ALTERADOS\n");
			}else
				printf("\nAlteracao de dados CANCELADA\n");
				
			fwrite(&aux, sizeof(TpMotoqueiro), 1, ptr);

		}
		
		getch();
		fclose(ptr);
		clrscr();	
	}
	
}

void alterarCliente(void){
	clrscr();
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
		flag = buscaSentinelaTelefone(ptr, aux.telefone);
		
		while (flag == -1 && strlen(aux.telefone) > 0) {
			printf("Insira um TELEFONE cadastrado:\n");
			fflush(stdin);
			gets(aux.telefone);
	
			flag = buscaSentinelaTelefone(ptr, aux.telefone);
			//printf("\nO tamanho de um reg eh: %d e o ponteiro esta em: %d\n", sizeof(TpCliente), flag);
		}
		
		if(strlen(aux.telefone) > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpCliente), 1, ptr);
			fseek(ptr, flag, 0);

			printf("\n###Conteudo do Registro###\n");
			printf("TELEFONE: %s\n", aux.telefone);
			printf("NOME: %s\n", aux.nome);
			printf("ENDERECO: %s\n", aux.endereco);
			printf("CIDADE: %s\n", aux.cidade);
			printf("CEP: %s\n", aux.cep);

			printf("\nO que deseja ALTERAR?\n");
			printf("[A] TELEFONE\n");
			printf("[B] NOME\n");
			printf("[C] ENDERECO\n");
			printf("[D] CIDADE\n");
			printf("[E] CEP\n");
			
			op = toupper(getche());
			
			if(op == 'A'){
				printf("\nInsira o novo TELEFONE: \n");
				gets(aux.telefone);
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'B'){
				printf("\nInsira o novo NOME: \n");
				gets(aux.nome);
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'C'){
				printf("\nInsira o novo ENDERECO: \n");
				gets(aux.endereco);
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'D'){
				printf("\nInsira a nova CIDADE: \n");
				gets(aux.cidade);
				
				printf("Dados ALTERADOS\n");
			}else if(op == 'E'){
				printf("\nInsira o novo CEP: \n");
				gets(aux.cep);
				
				printf("Dados ALTERADOS\n");
			}else
				printf("\nAlteracao de dados CANCELADA\n");
				
			fwrite(&aux, sizeof(TpCliente), 1, ptr);
			
		}
		
		getch();
		fclose(ptr);
		clrscr();
	}
		
}

int buscaSeqIndexadaPedido(FILE *ptr, int num){
	TpPedido aux;

	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	
	while(!feof(ptr) && (aux.numero < num || aux.status != 'A'))
		fread(&aux, sizeof(TpPedido), 1, ptr);

	if(aux.numero == num && aux.status == 'A')
		return ftell(ptr) - sizeof(TpPedido);
	else	
		return -1;
}

int buscaSentinelaTelefone(FILE *ptr, char tel[30]){
	TpCliente aux;
	int tam, cont = 0;
	
	// Colocar numa struct o que voce quer usar para pesquisar, e sinalizar ela como lixo
	strcpy(aux.telefone, tel);
	aux.status = 'I';
	//printf("%s \n%c", aux.telefone, aux.status);

	// Colocar o que quer pesquisar em TL e calcular tamanho 
	fseek(ptr, 0, 2);
	tam = ftell(ptr) / sizeof(TpCliente);
	fwrite(&aux, sizeof(TpCliente), 1, ptr);
    
	// Voltar para o inicio e iniciar loop
    fseek(ptr, 0, 0);
    fread(&aux, sizeof(TpCliente), 1, ptr);
    while(!feof(ptr) && (stricmp(aux.telefone, tel) != 0 || aux.status != 'A')){
    	//printf("Telefone atual: %s Telefone Procurado: %s\n", aux.telefone, tel);
    	//getch();
    	fread(&aux, sizeof(TpCliente), 1, ptr);
    	cont++;
    	
    }
    
	if(stricmp(aux.telefone, tel) == 0 && aux.status == 'A')
        return ftell(ptr) - sizeof(TpCliente);
    else
        return -1;
}
	
int buscaPedido(FILE *ptr, int pedido){
	TpPedido aux;

	fseek(ptr, 0, 0);

	if (ptr == NULL) {
		printf("ERRO de abertura\n");
	}else {
		fread(&aux, sizeof(TpPedido), 1, ptr);

		while(!feof(ptr) && (aux.numero != pedido || aux.status != 'A')) {
			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		if (aux.numero == pedido && aux.status == 'A')
			return ftell(ptr) - sizeof(TpPedido);
		else 
			return -1;
		
		
	}

}

int buscaCPF(FILE *ptr, char texto[50]) {
	TpMotoqueiro aux;

	fseek(ptr, 0, 0);

	if (ptr == NULL)
		printf("ERRO de abertura\n");
	else
		fread(&aux, sizeof(TpMotoqueiro), 1, ptr);

		while(!feof(ptr) && (strcmp(texto, aux.cpf) != 0 || aux.status != 'A')) {
			fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
		}
		
		if(strcmp(aux.cpf, texto) == 0 && aux.status != 'I') 
			return ftell(ptr) - sizeof(TpMotoqueiro);
		else 
			return -1;

}

int buscaBinariaCodigo(FILE *ptr, int cod){
	TpPizza aux;
	int inicio = 0, fim, meio;
	
	fseek(ptr, 0, 2);
	fim = ftell(ptr) / sizeof(TpPizza); // recebe TL
	
	meio = (inicio + fim) / 2;
	
	fseek(ptr, meio * sizeof(TpPizza), 0);
	fread(&aux, sizeof(TpPizza), 1, ptr);
	while(inicio < fim && (aux.codigo != cod || aux.status != 'A')){
		
		if(cod > aux.codigo)
			inicio = meio + 1;
		else
			fim = meio - 1;
			
		meio = (inicio + fim) / 2;
		
		fseek(ptr, meio * sizeof(TpPizza), 0);
		fread(&aux, sizeof(TpPizza), 1, ptr);
	}
	
	if(aux.codigo == cod && aux.status == 'A')
		return ftell(ptr) - sizeof(TpPizza);
	else
		return -1;


}

void cadastrarPedido(void){
	clrscr();
	TpPedido aux;
	int flag;

	FILE *ptrpedido;
	FILE *ptrcliente = fopen("Clientes.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");
	FILE *ptrpizza = fopen("Pizzas.dat", "rb+");
	 
	printf("Insira o NUMERO do Pedido:\n");
	fflush(stdin);
	scanf("%d", &aux.numero);
	
	flag = verificaNumPedidoCadastrado(aux.numero);
	while(aux.numero > 0 && flag != -1){
		printf("Numero de pedido ja CADASTRADO, insira outro:\n");
		fflush(stdin);
		scanf("%d", &aux.numero);

		flag = verificaNumPedidoCadastrado(aux.numero);
	}

	while(aux.numero > 0 && flag == -1) { //pedido existe
		ptrpedido = fopen("Pedidos.dat", "ab");

		printf("Insira o TELEFONE do Cliente:\n");
		fflush(stdin);
		gets(aux.telefone);
		
		flag = buscaSentinelaTelefone(ptrcliente, aux.telefone); //busca telefone ate encontrar
		while (flag == -1 && strlen(aux.telefone) > 0) {
			printf("Insira um telefone do cliente CADASTRADO:\n");
			fflush(stdin);
			gets(aux.telefone);

			flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
		}

		//entra se telefone > 0
		if(strlen(aux.telefone) > 0) {
			printf("Insira o CODIGO dessa Pizza:\n");
			scanf("%d", &aux.codigo);

			flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
			while (flag == -1 && aux.codigo > 0) {
				printf("Insira um codigo CADASTRADO:\n");
				scanf("%d", &aux.codigo);

				flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
			}

			if(aux.codigo > 0){ // entra se o codigo > 0 e telefone > 0
				printf("Digite o CPF do Motoqueiro\n");
				fflush(stdin);
				gets(aux.cpf);
					
				flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				while (flag == -1 && strlen(aux.cpf) > 0) {
					printf("Digite um CPF do motoqueiro CADASTRADO\n");
					fflush(stdin);
					gets(aux.cpf);

					flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				}

				if(strlen(aux.cpf) > 0){ // entra se o cpf > 0 e codigo > 0 e telefone > 0
					strcpy(aux.situacao, "Em preparacao"); 				
						
					printf("Insira a DATA do Pedido: [dd mm aaaa]\n");
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
						
					aux.status = 'A';

					fwrite(&aux, sizeof(TpPedido), 1, ptrpedido);
					fclose(ptrpedido);					
					bubbleSortPedido();

					printf("\nInsira o NUMERO do Pedido:\n");
					fflush(stdin);
					scanf("%d", &aux.numero);

					flag = verificaNumPedidoCadastrado(aux.numero);
					while(aux.numero > 0 && flag != -1){
						printf("Numero de pedido ja CADASTRADO, insira outro:\n");
						fflush(stdin);
						scanf("%d", &aux.numero);

						flag = verificaNumPedidoCadastrado(aux.numero);
					}
				}else
					flag = 0;;	
			}else
				flag = 0;
		}else	 
			flag = 0;
	}
	clrscr();
	fclose(ptrpizza);
	fclose(ptrcliente);
	fclose(ptrmotoqueiro);
}
	
void cadastrarPizza(void) {
	clrscr();
	TpPizza aux;
	FILE *ptrarquivo;
	int flag;
	 
	printf("Insira o CODIGO da Pizza:\n");
	fflush(stdin);
	scanf("%d", &aux.codigo);
	
	flag = verificaCodPizzaCadastrado(aux.codigo);
	while(aux.codigo > 0 && flag != -1){
		printf("Codigo de pizza ja CADASTRADO, insira outro:\n");
		fflush(stdin);
		scanf("%d", &aux.codigo);

		flag = verificaCodPizzaCadastrado(aux.codigo);
	}

	while (aux.codigo > 0) {
		ptrarquivo = fopen("Pizzas.dat", "ab");
		printf("Insira a DESCRICAO dessa Pizza:\n");
		fflush(stdin);
		gets(aux.descricao);
		printf("Insira o VALOR dessa Pizza:\n");
		scanf("%f", &aux.valor);
		
		aux.status = 'A';

		fwrite(&aux, sizeof(TpPizza), 1, ptrarquivo);
		fclose(ptrarquivo);
		selecaoDiretaPizza();

		printf("\nInsira o CODIGO da Pizza:\n");
		fflush(stdin);
		scanf("%d", &aux.codigo);

		flag = verificaCodPizzaCadastrado(aux.codigo);
		while(aux.codigo > 0 && flag != -1){
			printf("Codigo de pizza ja CADASTRADO, insira outro:\n");
			fflush(stdin);
			scanf("%d", &aux.codigo);

			flag = verificaCodPizzaCadastrado(aux.codigo);
		}

	}
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

void cadastrarCliente(void) {
	clrscr();
	TpCliente aux;
	FILE *ptrarquivo;
	int flag, verif;
	
	printf("Insira o TELEFONE do cliente que deseja cadastrar:\n");
	fflush(stdin);
	gets(aux.telefone);

	flag = validarNumTelefone(aux.telefone);
	verif = verificaClienteCadastrado(aux.telefone);
	while((flag != 1 || verif != -1)  && strlen(aux.telefone) > 0) {
		printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro CPF:\n");
		fflush(stdin);
		gets(aux.telefone);
		flag = validarNumTelefone(aux.telefone);
		verif = verificaClienteCadastrado(aux.telefone);
	}
	
	while (strcmp(aux.telefone, "\0") != 0 && verif == -1) {
		ptrarquivo = fopen("Clientes.dat", "ab");

		printf("Insira o NOME desse cliente:\n");
		gets(aux.nome);
		printf("Insira o ENDERECO desse cliente:\n");
		gets(aux.endereco);
		printf("Insira a CIDADE desse cliente:\n");
		gets(aux.cidade);
		printf("Insira o CEP desse cliente:\n");
		gets(aux.cep);
		
		aux.status = 'A';
		
		fwrite(&aux, sizeof(TpCliente), 1, ptrarquivo);
		fclose(ptrarquivo);
		insercaoDiretaCliente();

		printf("\nInsira o TELEFONE do cliente que deseja cadastrar:\n");
		gets(aux.telefone);
		fflush(stdin);

		flag = validarNumTelefone(aux.telefone);
		verif = verificaClienteCadastrado(aux.telefone);
		while((flag != 1 || verif != -1)  && strlen(aux.telefone) > 0) {
			printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro CPF:\n");
			fflush(stdin);
			gets(aux.telefone);
			flag = validarNumTelefone(aux.telefone);
			verif = verificaClienteCadastrado(aux.telefone);
		}
	}
	clrscr();
}

void cadastrarMotoqueiro(void) {
	clrscr();
	TpMotoqueiro aux;
	FILE *ptrarquivo;
	int flag, verif;
		 
	printf("Insira o CPF do motoqueiro que deseja cadastrar:\n");
	fflush(stdin);
	gets(aux.cpf);

	flag = validarCPF(aux.cpf);
	verif = verificaMotoqueiroCadastrado(aux.cpf);
	while((flag != 1 || verif != -1)  && strlen(aux.cpf) > 0) {
		printf("CPF INVALIDO ou ja CADASTRADO, insira outro CPF:\n");
		fflush(stdin);
		gets(aux.cpf);
		flag = validarCPF(aux.cpf);
		verif = verificaMotoqueiroCadastrado(aux.cpf);
	}
	
	while(strlen(aux.cpf) > 0 && verif == -1) {
		ptrarquivo = fopen("Motoqueiros.dat", "ab");

		printf("Insira o NOME desse motoqueiro:\n");
		fflush(stdin);
		gets(aux.nome);
		printf("Insira o ENDERECO desse motoqueiro:\n");
		gets(aux.endereco);
		printf("Insira o TELEFONE desse motoqueiro:\n");
		gets(aux.telefone);
		flag = validarNumTelefone(aux.telefone);
		while(flag != 1 && strlen(aux.telefone) > 0){
			printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro CPF:\n");
			fflush(stdin);
			gets(aux.telefone);
			flag = validarNumTelefone(aux.telefone);
		}
		if(strlen(aux.telefone) > 0){
			printf("Insira a DATA DE ADMISSAO desse motoqueiro: [dd mm aaaa]\n");
			scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
			
			aux.status = 'A';

			fwrite(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
			fclose(ptrarquivo);

			printf("\nInsira o CPF do motoqueiro que deseja cadastrar:\n");
			fflush(stdin);
			gets(aux.cpf);

			flag = validarCPF(aux.cpf);
			verif = verificaMotoqueiroCadastrado(aux.cpf);
			while((flag != 1 || verif != -1)  && strlen(aux.cpf) > 0) {
				printf("CPF INVALIDO ou ja CADASTRADO, insira outro CPF:\n");
				fflush(stdin);
				gets(aux.cpf);
				flag = validarCPF(aux.cpf);
				verif = verificaMotoqueiroCadastrado(aux.cpf);
			}

		} else
			verif = 0;
	}
	ordenacaoExaustivaMotoqueiro();
	clrscr();
}

void exibirCliente(void) {
	clrscr();
	TpCliente aux;
	FILE *ptrarquivo = fopen("Clientes.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpCliente), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				printf("TELEFONE: %s\n", aux.telefone);
				printf("NOME: %s\n", aux.nome);
				printf("ENDERECO: %s\n", aux.endereco);
				printf("CIDADE: %s\n", aux.cidade);
				printf("CEP: %s\n", aux.cep);
				printf("STATUS: %c\n\n", aux.status);
			}
			fread(&aux, sizeof(TpCliente), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

void exibirMotoqueiro(void) {
	clrscr();
	TpMotoqueiro aux;
	FILE *ptrarquivo = fopen("Motoqueiros.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else {
		fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		while (!feof(ptrarquivo)){
			if(aux.status != 'I'){
				printf("CPF: %s\n", aux.cpf);
				printf("NOME: %s\n", aux.nome);
				printf("ENDERECO: %s\n", aux.endereco);
				printf("TELEFONE: %s\n", aux.telefone);
				printf("DATA DE ADMISSAO: %d/%d/%d\n", aux.data.d, aux.data.m, aux.data.a);
				printf("STATUS: %c\n\n", aux.status);

			}
			fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

void exibirPizza(void) {
	clrscr();
	TpPizza aux;
	FILE *ptrarquivo = fopen("Pizzas.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpPizza), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				printf("CODIGO: %d\n", aux.codigo);
				printf("DESCRICAO: %s\n", aux.descricao);
				printf("VALOR: %.2f\n", aux.valor);
				printf("STATUS: %c\n\n", aux.status);

			}
			fread(&aux, sizeof(TpPizza), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

void exibirPedidos(void) {
	clrscr();
	TpPedido aux;
	FILE *ptrarquivo = fopen("Pedidos.dat", "rb");
	
	if (ptrarquivo == NULL)
		printf("ERRO de abertura\n");
	else{
		fread (&aux, sizeof(TpPedido), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				printf("NUMERO: %d\n", aux.numero);
				printf("TELEFONE: %s\n", aux.telefone);
				printf("CODIGO: %d\n", aux.codigo);
				printf("CPF: %s\n", aux.cpf);
				printf("SITUACAO: %s\n", aux.situacao);
				printf("DATA DO PEDIDO: %d/%d/%d\n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
				printf("STATUS: %c\n\n", aux.status);

			}
			fread(&aux, sizeof(TpPedido), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

char menu(void) {
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[A] Cadastrar CLIENTES\n");
	printf("[B] Cadastrar MOTOQUEIROS\n");
	printf("[C] Cadastrar PIZZAS\n");
	printf("[D] Cadastrar PEDIDOS\n");
	textcolor(2);
	printf("[E] Exibir CLIENTES\n");
	printf("[F] Exibir MOTOQUEIROS\n");
	printf("[G] Exibir PIZZAS\n");
	printf("[H] Exibir PEDIDOS\n");
	textcolor(3);
	printf("[I] Alterar CLIENTES\n");
	printf("[J] Alterar MOTOQUEIROS\n");
	printf("[K] Alterar PIZZAS\n");
	printf("[L] Alterar PEDIDOS\n");
	textcolor(5);
	printf("[M] Excluir CLIENTES\n");
	printf("[N] Excluir MOTOQUEIROS\n");
	printf("[O] Excluir PIZZAS\n");
	printf("[P] Excluir PEDIDOS\n");
	textcolor(7);
	
	return toupper(getche());
}

char menuNum(void) {
	//clrscr();
	system("cls");
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[1] Cadastrar\n");
	textcolor(2);
	printf("[2] Exibir\n");
	textcolor(3);
	printf("[3] Alterar\n");
	textcolor(5);
	printf("[4] Excluir\n");
	textcolor(8);
	printf("[5] Relatorios\n");
	textcolor(9);
	printf("[6] Estatisticas\n");
	textcolor(7);

	return getche();
}

char menuCad(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[1] Cadastrar CLIENTES\n");
	printf("[2] Cadastrar MOTOQUEIROS\n");
	printf("[3] Cadastrar PIZZAS\n");
	printf("[4] Cadastrar PEDIDOS\n");
	textcolor(7);

	return getche();
}

char menuExib(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(2);
	printf("[1] Exibir CLIENTES\n");
	printf("[2] Exibir MOTOQUEIROS\n");
	printf("[3] Exibir PIZZAS\n");
	printf("[4] Exibir PEDIDOS\n");
	textcolor(7);

	return getche();
}

char menuAlt(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(3);
	printf("[1] Alterar CLIENTES\n");
	printf("[2] Alterar MOTOQUEIROS\n");
	printf("[3] Alterar PIZZAS\n");
	printf("[4] Alterar PEDIDOS\n");
	textcolor(7);

	return getche();
}

char menuExclLF(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(5);
	printf("[1] Excluir FISICAMENTE\n");
	printf("[2] Excluir LOGICAMENTE\n");
	textcolor(7);

	return getche();
}

char menuExcl(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(5);
	printf("[1] Excluir CLIENTES\n");
	printf("[2] Excluir MOTOQUEIROS\n");
	printf("[3] Excluir PIZZAS\n");
	printf("[4] Excluir PEDIDOS\n");
	textcolor(7);

	return getche();
}

char menuRel(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(8);
	printf("[1] Exibir Estado Pizza\n");
	printf("[2] Filtrar por letra\n");
	printf("[3] Relatorio de Clientes\n");
	printf("[4] Filtrar MOTOQUEIROS e SUAS ENTREGAS por DATA\n");
	printf("[5] Rank de Pizzas\n");
	textcolor(7);

	return getche();
}

char menuEst(void) {
	clrscr();
	printf("# # # # MENU # # # # \n");
	textcolor(9);
	printf("[1] Relatorio de Pizza mais pedida\n");
	printf("[2] Relatorio de Pizza menos pedida\n");
	printf("[3] Cliente que mais pede Pizza\n");
	printf("[4] Motoqueiro menos experiente\n");
	textcolor(7);

	return getche();
}
