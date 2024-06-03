//TRABALHO Pizzaria.cpp // KAIKY TREVISAN FERNANDES, MATEUS SILVA MACIEL
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
void qtdEntregas();
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
void entregasPorDia(void);
void pizzaMaisConsumida(void);

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

//Interface
void limparquadro(void);
void moldeMenuInicial(void);
void moldeMenuCadastro(void);
void moldeMenuExibir(void);
void moldeMenuAlterar(void);
void moldeMenuTipoExclusao(void);
void moldeMenuExcluir(void);
void moldeCadastrar(void);
void moldeMenuRelatorio(void);
void moldeMenuEstatisticas(void);
void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo);

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
						qtdEntregas();
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

					case '5':
						entregasPorDia();
					break;

					case '6':
						pizzaMaisConsumida();
					break;
				}
			break;
		}

	} while(op != 27);
}

void limparquadro(void){
	int l = 12, c = 9;
	
	while(c <= 22){
		gotoxy(l,c);
		printf("                                                               ");
		c++;
	}
}

void pizzaMaisConsumida(void) {
	TpPizza aux;
	TpPedido auxPedido;
	TpCliente auxCliente;

	FILE *ptr = fopen("Pizzas.dat", "rb+");
	FILE *ptrPedido = fopen("Pedidos.dat", "rb+");
	FILE *ptrCliente = fopen("Clientes.dat", "rb+");

	int cod, flag;

	limparquadro();
	if (ptr == NULL || ptrPedido == NULL || ptrCliente == NULL) {
        gotoxy(30, 10); printf("Erro ao abrir os arquivos.\n");
        if (ptr != NULL) fclose(ptr);
        if (ptrPedido != NULL) fclose(ptrPedido);
		if (ptrCliente != NULL) fclose(ptrCliente);
        return;
    }

	//Obter a pizza que sera trabalhada
	gotoxy(28, 10); printf("Digite o codigo da pizza: ");
	scanf("%d", &cod);
	flag = buscaBinariaCodigo(ptr, cod);
	while (flag == -1 && cod > 0) {
		limparquadro();
		gotoxy(20, 10); printf("Insira um codigo de pizza CADASTRADO: ");
		scanf("%d", &cod);
		flag = buscaBinariaCodigo(ptr, cod);
	}

	if (cod > 0) {
		//Colocar todas os cliente que pediram essa pizza em uma matriz
		fseek(ptrPedido, 0, 2);
		int TF = ftell(ptrPedido) / sizeof(TpPedido);
		int TL;

		char listaClientes[TF][30];
		fseek(ptrPedido, 0, 0);
		fread(&auxPedido, sizeof(TpPedido), 1, ptrPedido);
		TL = 0;
		
		while(!feof(ptrPedido)) {
			if (auxPedido.status == 'A' && auxPedido.codigo == cod) {
				strcpy(listaClientes[TL], auxPedido.telefone);
				TL++;
			}
			fread(&auxPedido, sizeof(TpPedido), 1, ptrPedido);
		}
		
		//Debug de informaçoes
		/*
		int pos;
		printf("\nQuantidade de pedidos: %d\nValor de i: %d\n", TF, TL);
		printf("Clientes que pediram a Pizza especificada:\n");
		for (int j = 0; j < TL; j++) {
			printf("Cliente: %s\n", listaClientes[j]);
		}
		*/

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

				//Debug de informaçoes
				//printf("\nCliente analisado: %s Apareceu %d vezes\nTEL que mais apareceu %s Vezes que ele apareceu %d", auxCliente.nome, count, maior, vezes); getch();				
			}

			fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);
		}

		//Mostrar os valores achados
		int pos;
		pos = buscaSentinelaTelefone(ptrCliente, maior);
		fseek(ptrCliente, pos, 0);
		fread(&auxCliente, sizeof(TpCliente), 1, ptrCliente);

		pos = buscaBinariaCodigo(ptr, cod);
		fseek(ptr, pos, 0);
		fread(&aux, sizeof(TpPizza), 1, ptr);

		limparquadro();
		if (vezes == 0) {
			gotoxy(22, 10); printf("%s nao foi pedida nenhuma vez", aux.descricao);
		} else {
			gotoxy(25, 10); printf("Cliente que mais pediu %s:", aux.descricao);
			gotoxy(25, 11); printf("%s - %d pedido(s)", auxCliente.nome, vezes);
		}
		
	}
	
	fclose(ptr);
	fclose(ptrPedido);
	fclose(ptrCliente);
	getch();
}

void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo){
	textcolor(frente);
	textbackground(fundo);
	
	gotoxy(colunai, linhai); 
	printf("%c", 201); //canto superior esquerdo
	gotoxy(colunaf, linhai); 
	printf("%c", 187);//canto superior direito
	gotoxy(colunai, linhaf); 
	printf("%c", 200); //canto inferior esquerdo
	gotoxy(colunaf, linhaf); 
	printf("%c", 188);//canto inferior direito
	
	
	for(int a = colunai + 1; a < colunaf; a++){ 
		gotoxy(a, linhai); printf("%c", 205); 			
		gotoxy(a, linhaf); printf("%c", 205);
	}

	for(int b = linhai + 1; b < linhaf; b++){
		gotoxy(colunai, b); printf("%c", 186);
		gotoxy(colunaf, b); printf("%c", 186);
	}
	
	
	//voltar cores de texto e fundo padrão
	textcolor(7);
	textbackground(0);
	
}

void moldeCadastrar(void){
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	gotoxy(33, 7); 
	printf("* * * PIZZARIA * * *");
			
}

void moldeMenuTipoExclusao(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(19,13,37,17,7,5); //ITEM 1 
	moldura(50,13,68,17,7,5); //ITEM 2

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuExcluir(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,5); //ITEM 1 
	moldura(49,10,67,14,7,5); //ITEM 2

	moldura(18,17,36,21,7,5); //ITEM 3 
	moldura(49,17,67,21,7,5); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuAlterar(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,3); //ITEM 1 
	moldura(49,10,67,14,7,3); //ITEM 2

	moldura(18,17,36,21,7,3); //ITEM 3 
	moldura(49,17,67,21,7,3); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * ALTERAR * * *");
}

void moldeMenuExibir(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,1); //ITEM 1 
	moldura(49,10,67,14,7,1); //ITEM 2

	moldura(18,17,36,21,7,1); //ITEM 3 
	moldura(49,17,67,21,7,1); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * EXIBIR * * *");
}

void moldeMenuCadastro(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,2); //ITEM 1 
	moldura(49,10,67,14,7,2); //ITEM 2

	moldura(18,17,36,21,7,2); //ITEM 3 
	moldura(49,17,67,21,7,2); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * CADASTRAR * * *");
}

void moldeMenuInicial(void){
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,7,6); //ITEM 1 
	moldura(34,10,51,14,7,6); //ITEM 2 
	moldura(57,10,73,14,7,6); //ITEM 3 

	moldura(12,17,28,21,7,6); //ITEM 4 
	moldura(34,17,51,21,7,6); //ITEM 5 
	moldura(57,17,73,21,7,6); //ITEM 6 

	gotoxy(33, 7); 
	printf("* * * PIZZARIA * * *");
			
}

void moldeMenuRelatorio(void) {
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,13,14); //ITEM 1 
	moldura(34,10,51,14,13,14); //ITEM 2 
	moldura(57,10,73,14,13,14); //ITEM 3 

	moldura(12,17,28,21,13,14); //ITEM 4 
	moldura(34,17,51,21,13,14); //ITEM 5 
	moldura(57,17,73,21,13,14); //ITEM 6 

	gotoxy(33, 7); 
	printf("* * * PIZZARIA * * *");
}

void moldeMenuEstatisticas(void) {
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,17,18); //ITEM 1 
	moldura(34,10,51,14,17,18); //ITEM 2 
	moldura(57,10,73,14,17,18); //ITEM 3 

	moldura(12,17,28,21,17,18); //ITEM 4 
	moldura(34,17,51,21,17,18); //ITEM 5 
	moldura(57,17,73,21,17,18); //ITEM 6 

	gotoxy(33, 7); 
	printf("* * * PIZZARIA * * *");
}

int pizzasPorDia(FILE *ptr, char cpf[30], int dia, int mes, int ano){
	TpPedido aux;
	int cont = 0;
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	while(!feof(ptr)){
		if(aux.dataPedido.d == dia && aux.dataPedido.m == mes && aux.dataPedido.a == ano)
			if(strcmp(aux.cpf, cpf) == 0)
				cont++;
		fread(&aux, sizeof(TpPedido), 1, ptr);	
	}

	return cont;
}

void entregasPorDia(void){
	TpPedido aux;
	TpMotoqueiro motoqueiro;
	TpData data;

	char nome[30];

	char cpf[50][30];
	int pizzaentregue[30];

	int i, j;
	int pos, posanterior;
	int flag;

	char cpfmaior[30];
	int maior;

	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");

	limparquadro();
	int x, y;
	if (ptrmotoqueiro == NULL || ptr == NULL) {
		gotoxy(30, 10); printf("ERRO DE ABERTURA");
	} else {
		fseek(ptr, 0 , 2);
		
		gotoxy(20, 10); printf("Insira a data que deseja verificar:");
		scanf("%d %d %d", &data.d,&data.m,&data.a);
		
		fseek(ptr, 0 , 0);
		fread(&aux, sizeof(TpPedido), 1, ptr);
		i = 0;
		while(!feof(ptr)){
			flag = 0;

			//verificar se o cpf buscado já apareceu
			for(j = 0; j < i ; j++){
				if(strcmp(aux.cpf, cpf[i]) == 0){
					flag = -1;
					j = i; //quebra do loop
				}
			}

			if(flag != -1){
				//coloca o cpf buscado na estrutura
				strcpy(cpf[i],aux.cpf);

				posanterior = ftell(ptr);
				pos = buscaCPF(ptrmotoqueiro, aux.cpf);
				if(pos != -1){
					fseek(ptrmotoqueiro, pos, 0);
					fread(&motoqueiro, sizeof(TpMotoqueiro), 1, ptrmotoqueiro);
					pizzaentregue[i] = pizzasPorDia(ptr, aux.cpf, data.d, data.m, data.a);
					i++;
				}
				fseek(ptr, posanterior, 0);
			}					
			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		//procurando maior quantidade de entregas
		maior = pizzaentregue[0];
		strcpy(cpfmaior, cpf[0]);
		for(j = 0; j < i; j++){
			if(pizzaentregue[j] > maior){
				maior = pizzaentregue[j];
				strcpy(cpfmaior, cpf[j]);
			}	
		}

		//buscando o nome daquela pos
		fseek(ptrmotoqueiro, 0, 0);
		fread(&motoqueiro, sizeof(TpMotoqueiro), 1, ptrmotoqueiro);
		while(!feof(ptrmotoqueiro)){
			if(strcmp(motoqueiro.cpf, cpfmaior) == 0)
				strcpy(nome, motoqueiro.nome);
			fread(&motoqueiro, sizeof(TpMotoqueiro), 1, ptrmotoqueiro);
		}
		
		limparquadro();
		x = 30, y = 10;
		if(maior != 0){
			gotoxy(x, y); printf("MOTOQUEIRO COM MAIS ENTREGAS:"); y++;
			gotoxy(x, y); printf("DATA: %d %d %d", data.d, data.m, data.a); y++;
			gotoxy(x, y); printf("NOME: %s", nome); y++;
			gotoxy(x, y); printf("ENTREGAS REALIZADAS: %d", maior); y++;
		} else {
			gotoxy(x, y);printf("NAO HOUVE ENTREGAS NESSA DATA");
		}

		fclose(ptr);
		fclose(ptrmotoqueiro);
		getch();
	}
}

void rankPizzas(void) {
	TpPedido aux;
	TpPizza auxPizza;
	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb+");
	int pos, TL, i;
	int x = 30, y = 10;

	fseek(ptrPizza, 0, 2);
	int loop = ftell(ptrPizza) / sizeof(TpPizza);
	//printf("\nLoop = %d\n", loop);

	limparquadro();
	gotoxy(x, y); printf("### Rank de pizzas ###"); y++;
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
			
			x = 27;
			gotoxy(x, y); printf("%s - %d pedido(s)", auxPizza.descricao, vezes);	y++;	
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

int qtdPizzas(FILE *ptr, char cpf[30], int diaini, int mesini, int anoini, int diafin, int mesfin, int anofin, int dfiltro, int mfiltro, int afiltro){
	TpPedido aux;
	int cont = 0;
	fseek(ptr, 0, 0);
	fread(&aux, sizeof(TpPedido), 1, ptr);
	while(!feof(ptr)){
		if(verificaIntervaloData(diaini, mesini, anoini, diafin, mesfin, anofin, dfiltro, mfiltro, afiltro))
			if(strcmp(aux.cpf, cpf) == 0 && strcmp(aux.situacao,"Entregue") == 0)
				cont++;
		fread(&aux, sizeof(TpPedido), 1, ptr);	
	}

	return cont;
}

void qtdEntregas(void){
	TpPedido aux;
	TpMotoqueiro motoqueiro;
	TpData datai, dataf;

	char nome[30];
	char cpfbuscado[50][30];

	int pizzas, pos, posanterior, loopcpf;
	int flag;
	int x = 30, y = 10;

	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");

	if (ptr == NULL || ptrmotoqueiro == NULL) {
		limparquadro();
		printf("ERRO DE ABERTURA\n");		
	} else {
		fseek(ptr, 0 , 2);

		limparquadro();
		gotoxy(x, y); printf("Insira a data inicial: "); y++;
		gotoxy(x, y); scanf("%d %d %d", &datai.d,&datai.m,&datai.a); y++;
		gotoxy(x, y); printf("Insira a data final:\n"); y++;
		gotoxy(x, y); scanf("%d %d %d", &dataf.d,&dataf.m,&dataf.a); y++;
		limparquadro();
		
		loopcpf = 0;
		fseek(ptr, 0 , 0);
		fread(&aux, sizeof(TpPedido), 1, ptr);
		while(!feof(ptr)){
			flag = 0;
			if(verificaIntervaloData(datai.d, datai.m, datai.a, dataf.d, dataf.m, dataf.a, aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a) != -1){
				//verificar se o cpf buscado já apareceu
				for(int j = 0; j < loopcpf ; j++){
					if(strcmp(aux.cpf, cpfbuscado[j]) == 0){
						flag = -1;
						j = loopcpf; //quebra do loop
					}
				}

				if(flag != -1){
					//coloca o cpf buscado na estrutura
					strcpy(cpfbuscado[loopcpf],aux.cpf); 
					loopcpf++;
					posanterior = ftell(ptr);
					pos = buscaCPF(ptrmotoqueiro, aux.cpf);
					if(pos != -1){
						fseek(ptrmotoqueiro, pos, 0);
						fread(&motoqueiro, sizeof(TpMotoqueiro), 1, ptrmotoqueiro);
						x = 33, y = 10;
						gotoxy(x, y); printf("MOTOQUEIRO: %s\n", motoqueiro.nome); y++;
						pizzas = qtdPizzas(ptr, aux.cpf, datai.d, datai.m, datai.a, dataf.d, dataf.m, dataf.a, aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
						gotoxy(x, y); printf("PIZZAS ENTREGUES: %d\n\n", pizzas); y++;

						gotoxy(49, 22); printf("ENTER para proxima pagina");
						getch();
					}
					fseek(ptr, posanterior, 0);
				}
			}					
			fread(&aux, sizeof(TpPedido), 1, ptr);
		}
		
		fclose(ptr);
		fclose(ptrmotoqueiro);
		getch();
	}
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
	TpMotoqueiro auxMotoqueiro;
    
    FILE *ptrMotoqueiro = fopen("Motoqueiros.dat", "rb+");
	int d, m, a, pos = 0, i = 0;
	int total;

	limparquadro();
	int x = 30, y = 10;
    if (ptrMotoqueiro == NULL) {
        gotoxy(x, y); printf("ERRO DE ABERTURA");
    } else {
        fseek(ptrMotoqueiro, 0, 0);
        fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);

        d = auxMotoqueiro.data.d;
        m = auxMotoqueiro.data.m;
        a = auxMotoqueiro.data.a;

        fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);
        while(!feof(ptrMotoqueiro)) {
			i++;
			if (auxMotoqueiro.status == 'A') {
				if (a <= auxMotoqueiro.data.a || 
					(a == auxMotoqueiro.data.a && m <= auxMotoqueiro.data.m) || 
					(a == auxMotoqueiro.data.a && m == auxMotoqueiro.data.m && d <= auxMotoqueiro.data.d)) {

					d = auxMotoqueiro.data.d;
					m = auxMotoqueiro.data.m;
					a = auxMotoqueiro.data.a;
					pos = i;
				}				
			}

            fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);
        }

        fseek(ptrMotoqueiro, pos * sizeof(TpMotoqueiro), 0);
        fread(&auxMotoqueiro, sizeof(TpMotoqueiro), 1, ptrMotoqueiro);
        gotoxy(x, y); printf("Motoqueiro menos experiente:"); y++;
        gotoxy(x, y); printf("Nome: %s", auxMotoqueiro.nome); y++;
        gotoxy(x, y); printf("Data de admissao: %d %d %d", auxMotoqueiro.data.d, auxMotoqueiro.data.m, auxMotoqueiro.data.a);
    }

	getch();
    fclose(ptrMotoqueiro);
}

void clienteMaisConsome(void) {
	TpPedido aux;
	TpCliente auxCliente;

	FILE *ptr = fopen("Pedidos.dat", "rb+");
	FILE *ptrCliente = fopen("Clientes.dat", "rb+");

	int pos;

	limparquadro();
	if (ptr == NULL || ptrCliente == NULL) {
        gotoxy(30, 10); printf("Erro ao abrir os arquivos.");
        if (ptr != NULL) fclose(ptr);
		if (ptrCliente != NULL) fclose(ptrCliente);
        return;
    }

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

	limparquadro();
	gotoxy(28, 10); printf("Cliente que mais pediu pizza:");
	gotoxy(28, 11); printf("%s - %d pedido(s)", auxCliente.nome, vezes);

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
	int x = 30, y = 10;

	limparquadro();
	if (ptr == NULL || ptrPizza == NULL) {
		gotoxy(x, y); printf("Erro ao abrir os arquivos.");
        if (ptr != NULL) fclose(ptr);
        if (ptrPizza != NULL) fclose(ptrPizza);
        return;
    }

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

	x--; gotoxy(x, y); printf("* * * Pizza mais pedida * * *"); y++;
	gotoxy(x, y); printf("%s - %d pedido(s)", auxPizza.descricao, vezes);

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
	int x = 30, y = 10;

	limparquadro();
	if (ptr == NULL || ptrPizza == NULL) {
        gotoxy(x, y); printf("Erro ao abrir os arquivos.");
        if (ptr != NULL) fclose(ptr);
        if (ptrPizza != NULL) fclose(ptrPizza);
        return;
    }

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

	x--; gotoxy(x, y); printf("* * * Pizza menos pedida * * *"); y++;
	gotoxy(x, y); printf("%s - %d pedido(s)", auxPizza.descricao, vezes);

	getch();
	fclose(ptr);
	fclose(ptrPizza);
}

void exclusaoLogicaPedido(void){
	TpPedido aux;
	int num, flag;
	int l = 16, c = 10;

	FILE *ptr = fopen("Pedidos.dat", "rb+");

	limparquadro();
	moldeCadastrar();
	
	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Digite o NUMERO DO PEDIDO que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d",&num);
		c++;
		
		flag = buscaSeqIndexadaPedido(ptr, num);
		
		while (flag == -1 && num > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um numero do pedido CADASTRADO: \n");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d",&num);
			c++;
		
			flag = buscaSeqIndexadaPedido(ptr, num);
		}
		
		if(num > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpPedido), 1, ptr);
			fseek(ptr, flag, 0);	

			l = 30, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("---> Dados do PEDIDO <---");
			c++;
			gotoxy(l, c);
			printf("Numero: %d", aux.numero);
			c++;
			gotoxy(l, c);
			printf("Telefone: %s", aux.telefone);
			c++;
			gotoxy(l, c);
			printf("Codigo da pizza: %d", aux.codigo);
			c++;
			gotoxy(l, c);
			printf("CPF: %s", aux.cpf);
			c++;
			gotoxy(l, c);
			printf("Situacao: %s", aux.situacao);
			c++;
			gotoxy(l, c);
			printf("Data do pedido: %d/%d/%d", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
			c++;
			gotoxy(l, c);
			printf("STATUS: %c", aux.status);
			c++;
			gotoxy(l, c);
			printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)\n");
			c++;
			if(toupper(getche()) == 'Y'){
				aux.status = 'I';
				fwrite(&aux,sizeof(TpPedido), 1, ptr);
				gotoxy(l, c);
				printf("Pedido excluido com sucesso");
			} else{
				gotoxy(l, c);
				printf("Exclusao nao realizada");
			}
			getch();
		}
		
		fclose(ptr);
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Pizzas.dat", "rb+");
	
	limparquadro();
	moldeCadastrar();

	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Digite o CODIGO DA PIZZA que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d",&cod);
		c++;

		flag = buscaBinariaCodigo(ptr, cod);
		
		while (flag == -1 && cod > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um codigo da pizza CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d",&cod);
			c++;
		
			flag = buscaBinariaCodigo(ptr, cod);
		}

		flag = verificaCodPedido(ptr, cod);
		
		if (flag == 1) {
			if(cod > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpPizza), 1, ptr);
				fseek(ptr, flag, 0);	

				l = 30, c = 10;
				limparquadro();
				gotoxy(l, c);
				printf("---> Dados da PIZZA <---");
				c++;
				gotoxy(l, c);
				printf("CODIGO: %d", aux.codigo);
				c++;
				gotoxy(l, c);
				printf("DESCRICAO: %s", aux.descricao);
				c++;
				gotoxy(l, c);
				printf("VALOR: %.2f", aux.valor);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;
				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpPizza), 1, ptr);
					gotoxy(l, c);
					printf("Pizza excluida com sucesso");
				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
				}
			}			
		} else {
			gotoxy(l, c);
			printf("Pizza cadastrada com pedido ativo!Exclusao nao realizada");
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	
	limparquadro();
	moldeCadastrar();

	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(l, c);
		printf("Digite o CPF do motoqueiro que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(cpf);
		c++;
		
		flag = buscaCPF(ptr, cpf);
		
		while (flag == -1 && strlen(cpf) > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um CPF CADASTRADO: \n");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(cpf);
			c++;
		
			flag = buscaCPF(ptr, cpf);
		}

		flag = verificaCPFPedido(ptr, cpf);
		
		if (flag == 1) {
			if(strlen(cpf) > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpMotoqueiro), 1, ptr);
				fseek(ptr, flag, 0);	

				l = 22, c =10;
				limparquadro();
				gotoxy(30, c);
				printf("---> Dados do MOTOQUEIRO <---");
				c++;
				gotoxy(l, c);
				printf("CPF: %s", aux.cpf);
				c++;
				gotoxy(l, c);
				printf("NOME: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("ENDERECO: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("TELEFONE: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("DATA DE ADMISSAO: %d/%d/%d", aux.data.d, aux.data.m, aux.data.a);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;
				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpMotoqueiro), 1, ptr);
					gotoxy(l, c);
					printf("Motoqueiro excluido com sucesso");
				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
				}
			}			
		} else {
			gotoxy(12, c);
			printf("Motoqueiro cadastrado com pedido ativo! Exclusao nao realizada");
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Clientes.dat", "rb+");
	
	limparquadro();
	moldeCadastrar();

	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(l, c);
		printf("Digite o TELEFONE do cliente que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(tel);
		c++;
		
		flag = buscaSentinelaTelefone(ptr, tel);
		
		while (flag == -1 && strlen(tel) > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um telefone CADASTRADO: \n");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(tel);
			c++;
		
			flag = buscaSentinelaTelefone(ptr, tel);
		}

		flag = verificaTelPedido(ptr, tel);

		if (flag == 1) {
			if(strlen(tel) > 0){
				fseek(ptr, flag, 0);
				fread(&aux,sizeof(TpCliente), 1, ptr);
				fseek(ptr, flag, 0);	

				l = 30, c =10;
				limparquadro();
				gotoxy(l, c);
				printf("---> Dados do CLIENTE <---");
				c++;
				gotoxy(l, c);
				printf("TELEFONE: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("NOME: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("CIDADE: %s", aux.cidade);
				c++;
				gotoxy(l, c);
				printf("ENDERECO: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("CEP: %s", aux.cep);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;

				if(toupper(getche()) == 'Y'){
					aux.status = 'I';
					fwrite(&aux,sizeof(TpCliente), 1, ptr);
					gotoxy(l, c);
					printf("Telefone excluido com sucesso");
				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
				}
			}
		} else {
			gotoxy(l, c);
			printf("Cliente cadastrado com pedido ativo!Exclusao nao realizada");
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
	int x, y;
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
		limparquadro();
		gotoxy(x, y); printf("ERRO de abertura\n");
	} else {
		while (count < tamanhoPedidos) {
			limparquadro();

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
			x = 30, y = 10;
			gotoxy(x, y); printf("TELEFONE: %s", telAtual); y++;
			pos = buscaSentinelaTelefone(ptrcliente, telAtual);
			fseek(ptrcliente, pos, 0);
			fread(&aux2, sizeof(TpCliente), 1, ptrcliente);
			gotoxy(x, y); printf("NOME: %s", aux2.nome); y++;
			gotoxy(x, y); printf("Pizzas pedidas: "); y++;
			
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
					gotoxy(x, y); printf("1x %s - R$ %.2f", aux3.descricao, valor); y++;
				}
				
				fread(&aux, sizeof(TpPedido), 1, ptrpedido);
			}

			gotoxy(x, y); printf("Total gasto = R$ %.2f\n\n", total); y++;
			gotoxy(49, 22); printf("ENTER para proxima pagina");
			getch();		
		}

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
		limparquadro();
		gotoxy(30, 10); printf("Erro de abertura!");
	} else {
		limparquadro();
		gotoxy(15, 10); printf("Digite a inicial que quer filtrar o nome dos clientes: ");
		fflush(stdin);
		letra = getche();

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
			gotoxy(25, 11); printf("###Clientes que comecam com %c ###", toupper(letra));
			gotoxy(25, 12); printf("Nome: %s", aux.nome);

			gotoxy(49, 22); printf("ENTER para proxima pagina");
			getch();
			cont++;
		}

		fread(&aux, sizeof(TpCliente), 1, ptr);
	}

	if (cont == 0) {
		gotoxy(23, 11); printf("Nao existem clientes com essa inicial");
	}
	
}

void estadoPizza(void) {
	TpPedido aux;
	TpPizza auxPizza;
	int cont, flag;
	int x, y;
	FILE *ptr = fopen("Pedidos.dat", "rb");
	FILE *ptrPizza = fopen("Pizzas.dat", "rb");

	fread(&aux, sizeof(TpPedido), 1, ptr);
	fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

	if (ptr == NULL || ptrPizza == NULL) {
		gotoxy(30, 10); printf("Erro de abertura!");
	} else {
		cont = 0;
		while (!feof(ptr)) {
			
			if (strcmp(aux.situacao, "Em preparacao") == 0) {
				limparquadro();
				x = 29, y = 10;
				gotoxy(x, y); printf("###Pizzas em preparacao###"); y++;

				flag = buscaBinariaCodigo(ptrPizza, aux.codigo);
				fseek(ptrPizza, flag, 0);
				fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

				gotoxy(x, y); printf("Numero do pedido: %d", aux.numero); y++;
				//printf("Codigo da pizza: %d\n", aux.codigo);
				gotoxy(x, y); printf("Descricao: %s", auxPizza.descricao); y++;
				gotoxy(x, y); printf("Descricao da pizza: %s", aux.situacao); y++;
				gotoxy(x, y); printf("Valor: %.2f", auxPizza.valor); y++;
				
				gotoxy(49, 22); printf("ENTER para proxima pagina");
				getch();
				cont++;
			}

			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		if (cont == 0) {
			gotoxy(30, 10); printf("Nenhuma Pizza em Andamento");
		}
		
		limparquadro();

		fseek(ptr, 0, 0); //Volta ptr de pedidos pra fazer mais um loop
		fread(&aux, sizeof(TpPedido), 1, ptr); 
		cont = 0;
		while (!feof(ptr)) {
			x = 29, y = 10;
			gotoxy(x, y); printf("###Pizzas em rota###");

			if (strcmp(aux.situacao, "Em rota de entrega") == 0) {
				limparquadro();
				x = 29, y = 10;
				gotoxy(x, y); printf("###Pizzas em rota###"); y++;
					
				flag = buscaBinariaCodigo(ptrPizza, aux.codigo);
				fseek(ptrPizza, flag, 0);
				fread(&auxPizza, sizeof(TpPizza), 1, ptrPizza);

				gotoxy(x, y); printf("Numero do pedido: %d", aux.numero); y++;
				//printf("Codigo da pizza: %d\n", aux.codigo);
				gotoxy(x, y); printf("Descricao: %s", auxPizza.descricao); y++;
				gotoxy(x, y); printf("Descricao da pizza: %s", aux.situacao); y++;
				gotoxy(x, y); printf("Valor: %.2f", auxPizza.valor); y++;

				gotoxy(49, 22); printf("ENTER para proxima pagina");
				getch();
				cont++;
			}

			fread(&aux, sizeof(TpPedido), 1, ptr);
		}

		if (cont == 0) {
			gotoxy(29, 11); printf("Nenhuma Pizza em rota de entrega");
		}

		fclose(ptr);
		fclose(ptrPizza);
	}

	getch();
}

void exclusaoFisicaPedido(void){
	TpPedido aux;
	int flag, auxnum;
	int l = 16, c = 10;

	FILE *ptr = fopen("Pedidos.dat", "rb");
	
	limparquadro();

	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Digite o NUMERO do pedido que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d", &auxnum);
		c++;
		
		flag = buscaSeqIndexadaPedido(ptr, auxnum);
		
		while (flag == -1 && auxnum > 0){
			gotoxy(l, c);
			printf("Insira um numero do pedido CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d", &auxnum);
			c++;
		
			flag = buscaSeqIndexadaPedido(ptr, auxnum);
		}
		
		if(auxnum > 0){
			fseek(ptr, flag, 0); //vai para a pos encontrada
			fread(&aux, sizeof(TpPedido), 1, ptr);

			l = 30, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("---> Dados do PEDIDO <---");
			c++;
			gotoxy(l, c);
			printf("Numero: %d", aux.numero);
			c++;
			gotoxy(l, c);
			printf("Telefone: %s", aux.telefone);
			c++;
			gotoxy(l, c);
			printf("Codigo da pizza: %d", aux.codigo);
			c++;
			gotoxy(l, c);
			printf("CPF: %s", aux.cpf);
			c++;
			gotoxy(l, c);
			printf("Situacao: %s", aux.situacao);
			c++;
			gotoxy(l, c);
			printf("Data do pedido: %d/%d/%d", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
			c++;
			gotoxy(l, c);
			printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
			c++;
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
					gotoxy(l, c);
					printf("Exclusao realizada com sucesso!");

			} else{
				gotoxy(l, c);
				printf("Exclusao nao realizada");
				c++;
				fclose(ptr);
			}
			getch();
		}

		fclose(ptr);
		clrscr();	
	}
}

void excluirClienteInativo(void) {
	TpCliente aux;
	FILE *ptr = fopen("Clientes.dat", "rb");
	int l = 16, c = 10;
	if (ptr == NULL){
		gotoxy(l, c);
		printf("Erro de abertura");
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
		gotoxy(l, c);
		printf("Exclusao de inativos realizada com sucesso!");	
	}
}

void exclusaoFisicaCliente(void){
	clrscr();
	TpCliente aux;
	int flag;
	char tel[30];
	int l = 16, c = 10;

	FILE *ptr = fopen("Clientes.dat", "rb");
	
	limparquadro();
	moldeCadastrar();

	if (ptr == NULL) {
		gotoxy(l, c);
		printf("Erro de abertura\n");
	} else {

		fclose(ptr);
		excluirClienteInativo();
		FILE *ptr = fopen("Clientes.dat", "rb");
		gotoxy(l, c);
		printf("Digite o TELEFONE do cliente que deseja excluir: \n");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(tel);
		c++;
		
		flag = buscaSentinelaTelefone(ptr, tel);
		while (flag == -1 && strlen(tel) > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um TELEFONE CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(tel);
			c++;
		
			flag = buscaSentinelaTelefone(ptr, tel);
		}

		if (verificaTelPedido(ptr, tel)  == -1) {
			if(strlen(tel) > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpCliente), 1, ptr);

				l = 30, c = 10;
				limparquadro();
				gotoxy(l, c);
				printf("---> Dados do CLIENTE <---");
				c++;
				gotoxy(l, c);
				printf("Telefone: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("Nome: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("Endereco: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("Cidade: %s", aux.cidade);
				c++;
				gotoxy(l, c);
				printf("Cep: %s", aux.cep);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;
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
						gotoxy(l, c);
						printf("Exclusao realizada com sucesso!");

				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
					fclose(ptr);
				}
			}
		} else {
			gotoxy(l, c);
			printf("Cliente cadastrado com pedido ativo!Exclusao nao realizada");
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Motoqueiros.dat", "rb");
	
	limparquadro();
	moldeCadastrar();

	if(ptr == NULL){
		printf("ERRO de abertura");
		gotoxy(l, c);
	}else{
		gotoxy(l, c);
		printf("Digite o CPF do motoqueiro que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(cpf);
		c++;
		
		flag = buscaCPF(ptr, cpf);
		
		while (flag == -1 && strlen(cpf) > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um CPF CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(cpf);
			c++;
		
			flag = buscaCPF(ptr, cpf);
		}

		if (verificaCPFPedido(ptr, cpf) == -1) {
			if(strlen(cpf) > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpMotoqueiro), 1, ptr);
				
				l = 22, c = 10;	
				limparquadro();
				gotoxy(30, c);
				printf("---> Dados do MOTOQUEIRO <---");
				c++;
				gotoxy(l, c);
				printf("CPF: %s", aux.cpf);
				c++;
				gotoxy(l, c);
				printf("Nome: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("Endereco: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("Telefone: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("Data de admissao: %d/%d/%d", aux.data.d, aux.data.m, aux.data.a);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;
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
						gotoxy(l, c);
						printf("Exclusao realizada com sucesso!");

				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
					fclose(ptr);
				}
			}			
		} else {
			gotoxy(12, c);
			printf("Motoqueiro cadastrado com pedido ativo!Exclusao nao realizada");
		}
	
		fclose(ptr);
		getch();
		clrscr();	
	}
}

void exclusaoFisicaPizza(void) {
	TpPizza aux;
	int flag, auxcod;
	int l = 16, c = 10;

	FILE *ptr = fopen("Pizzas.dat", "rb");
	
	limparquadro();

	if (ptr == NULL) {
		gotoxy(l, c);
		printf("ERRO de abertura");
	} else {
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Digite o CODIGO DA PIZZA que deseja excluir:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d",&auxcod);
		c++;

		flag = buscaBinariaCodigo(ptr, auxcod);
		
		while (flag == -1 && auxcod > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um codigo da pizza CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d",&auxcod);
			c++;
			
			flag = buscaBinariaCodigo(ptr, auxcod);
		}

		if(verificaCodPedido(ptr, auxcod) == -1) {
			if(auxcod > 0){
				fseek(ptr, flag, 0); //vai para a pos encontrada
				fread(&aux, sizeof(TpPizza), 1, ptr);

				l = 30, c = 10;
				limparquadro();
				gotoxy(l, c);
				printf("---> Dados da PIZZA <---");
				c++;
				gotoxy(l, c);
				printf("Codigo: %d", aux.codigo);
				c++;
				gotoxy(l, c);
				printf("Descricao: %s", aux.descricao);
				c++;
				gotoxy(l, c);
				printf("Valor: %.2f", aux.valor);
				c++;
				gotoxy(l, c);
				printf("Deseja prosseguir com a exclusao? (Y-Yes/N-No)");
				c++;
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
						gotoxy(l, c);
						printf("Exclusao realizada com sucesso!");

				} else{
					gotoxy(l, c);
					printf("Exclusao nao realizada");
					c++;
					fclose(ptr);
				}
			}			
		} else {
			gotoxy(l, c);
			printf("Pizza cadastrada com pedido ativo!Exclusao nao realizada");
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
	int l = 16, c = 10;

	FILE *ptrpedido = fopen("Pedidos.dat", "rb+");
	FILE *ptrcliente = fopen("Clientes.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");
	FILE *ptrpizza = fopen("Pizzas.dat", "rb+");
	
	moldeCadastrar();

	if(ptrpedido == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Insira o NUMERO do Pedido que desja ALTERAR: \n");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d",&aux.numero);
		c++;
		
		flag = buscaSeqIndexadaPedido(ptrpedido, aux.numero);
		
		while (flag == -1 && aux.numero > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um NUMERO do pedido cadastrado: \n");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d",&aux.numero);
			c++;
			
			flag = buscaSeqIndexadaPedido(ptrpedido, aux.numero);
		}
		
		if(aux.numero > 0){
			fseek(ptrpedido, flag, 0);
			fread(&aux,sizeof(TpPedido), 1, ptrpedido);
			fseek(ptrpedido, flag, 0);

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("###Conteudo do Registro###");
			c++;
			gotoxy(l, c);
			printf("NUMERO: %d", aux.numero);
			c++;
			gotoxy(l, c);
			printf("TELEFONE: %s", aux.telefone);
			c++;
			gotoxy(l, c);
			printf("CODIGO: %d", aux.codigo);
			c++;
			gotoxy(l, c);
			printf("CPF: %s", aux.cpf);
			c++;
			gotoxy(l, c);
			printf("SITUACAO: %s", aux.situacao);
			c++;
			gotoxy(l, c);
			printf("DATA DO PEDIDO: %d/%d/%d", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);

			gotoxy(49, 22);
			printf("ENTER para continuar");
			getch();

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("O que deseja ALTERAR?");
			c++;
			gotoxy(l, c);
			printf("[A] NUMERO");
			c++;
			gotoxy(l, c);
			printf("[B] TELEFONE");
			c++;
			gotoxy(l, c);
			printf("[C] CODIGO DA PIZZA");
			c++;
			gotoxy(l, c);
			printf("[D] CPF DO MOTOQUEIRO");
			c++;
			gotoxy(l, c);
			printf("[E] SITUACAO");
			c++;
			gotoxy(l, c);
			printf("[F] DATA DO PEDIDO");
			c++;

			op = toupper(getche());
			
			if(op == 'A'){
				gotoxy(l, c);
				printf("Insira o novo NUMERO do pedido: ");
				c++;				
				gotoxy(l, c);
				scanf("%d", &aux.numero);
				c++;
				
				while(aux.numero <= 0){
					gotoxy(l, c);
					printf("Insira um numero VALIDO:");
					c++;
					gotoxy(l, c);
					scanf("%d", &aux.numero);
					c++;
				}
				
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'B'){
				gotoxy(l, c);
				printf("Insira o novo TELEFONE do pedido:");
				c++;
				fflush(stdin);
				gotoxy(l, c);
				gets(aux.telefone);
				c++;
				flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
				
				while(strlen(aux.telefone) <= 0 || flag == -1){
					gotoxy(l, c);
					printf("Insira um telefone CADASTRADO:");
					c++;
					fflush(stdin);
					gotoxy(l, c);
					gets(aux.telefone);
					c++;
					flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'C'){
				gotoxy(l, c);
				printf("Insira o novo CODIGO DA PIZZA do pedido");
				c++;
				gotoxy(l, c);
				scanf("%d", &aux.codigo);
				c++;
				flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
				
				while(aux.codigo < 0 || flag == -1){
					gotoxy(l, c);
					printf("Insira um codigo da pizza CADASTRADO");
					c++;
					gotoxy(l, c);
					scanf("%d", &aux.codigo);
					c++;
					flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'D'){
				gotoxy(l, c);
				printf("Insira o novo CPF DO MOTOQUEIRO do pedido");
				c++;
				fflush(stdin);
				gotoxy(l, c);
				gets(aux.cpf);
				c++;
				flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				
				while(strlen(aux.cpf) <= 0 || flag == -1){
					gotoxy(l, c);
					printf("Insira um cpf CADASTRADO:");
					c++;
					fflush(stdin);
					gotoxy(l, c);
					gets(aux.cpf);
					c++;
					flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			} else if(op == 'E'){
				l = 30, c =10;
				limparquadro();
				gotoxy(18, c);
				printf("Para qual SITUACAO do pedido voce deseja alterar:");
				c++;
				gotoxy(l, c);
				printf("[A] Em preparacao");
				c++;
				gotoxy(l, c);
				printf("[B] Em rota de entrega");
				c++;
				gotoxy(l, c);
				printf("[C] Entregue");
				c++;
				gotoxy(l, c);
				printf("[D] Cancelado");
				c++;
				
				op = toupper(getch());
				
				if(op == 'A')
					strcpy(aux.situacao,"Em preparacao");
				else if(op == 'B')
					strcpy(aux.situacao,"Em rota de entrega");
				else if(op == 'C')
					strcpy(aux.situacao,"Entregue");
				else
					strcpy(aux.situacao,"Cancelado");
				
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'F'){
				gotoxy(l, c);
				printf("Insira a nova DATA DO PEDIDP: [dd mm aaaa]");
				c++;
				gotoxy(l, c);
				scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
				c++;

				while(aux.dataPedido.d > 31 || aux.dataPedido.d < 1 || aux.dataPedido.m > 12 || aux.dataPedido.m < 1 || aux.dataPedido.a > 2024 || aux.dataPedido.a < 1){
					gotoxy(l, c);
					printf("Insira uma data VALIDA");
					c++;
					gotoxy(l, c);
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else{
				gotoxy(l, c);
				printf("Alteracao de dados CANCELADA");
			}	
			fwrite(&aux, sizeof(TpPedido), 1, ptrpedido);
			getch();
		}
		
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Pizzas.dat", "rb+");
	
	moldeCadastrar();

	if (ptr == NULL) {
		gotoxy(l, c);
		printf("ERRO de abertura");
	} else {
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l, c);
		printf("Insira o CODIGO da Pizza que desja ALTERAR:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d",&aux.codigo);
		c++;	
		flag = buscaBinariaCodigo(ptr, aux.codigo);
		
		while (flag == -1 && aux.codigo > 0){
			l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um CODIGO cadastrado:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			scanf("%d",&aux.codigo);
			c++;
			flag = buscaBinariaCodigo(ptr, aux.codigo);

		}
		
		if(aux.codigo > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpPizza), 1, ptr);
			fseek(ptr, flag, 0);

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("###Conteudo do Registro###");
			c++;
			gotoxy(l, c);
			printf("CODIGO: %d", aux.codigo);
			c++;
			gotoxy(l, c);
			printf("DESCRICAO: %s", aux.descricao);
			c++;
			gotoxy(l, c);
			printf("VALOR: %.2f", aux.valor);

			gotoxy(49, 22);
			printf("ENTER para continuar");
			getch();

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("O que deseja ALTERAR?");
			c++;
			gotoxy(l, c);
			printf("[A] CODIGO");
			c++;
			gotoxy(l, c);
			printf("[B] DESCRICAO");
			c++;
			gotoxy(l, c);
			printf("[C] VALOR");
			c++;
			
			op = toupper(getche());
			
			if(op == 'A'){
				gotoxy(l, c);
				printf("Insira o novo CODIGO:");
				c++;
				gotoxy(l, c);
				scanf("%d", &aux.codigo);
				c++;;
				
				while(aux.codigo <= 0){
					gotoxy(l, c);
					printf("Insira um codigo VALIDO:");
					c++;
					gotoxy(l, c);
					scanf("%d", &aux.codigo);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'B'){
				gotoxy(l, c);
				printf("Insira a nova DESCRICAO: ");
				c++;
				fflush(stdin);
				gotoxy(l, c);
				gets(aux.descricao);
				c++;
				
				while(strlen(aux.descricao) <= 0){
					gotoxy(l, c);
					printf("Insira uma descricao VALIDA:");
					c++;
					gotoxy(l, c);
					gets(aux.descricao);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'C'){
				gotoxy(l, c);
				printf("Insira o novo VALOR:");
				c++;
				gotoxy(l, c);
				scanf("%f", &aux.valor);
				c++;
				
				while(aux.valor <= 0){
					gotoxy(l, c);
					printf("Insira um valor VALIDO:");
					c++;
					gotoxy(l, c);
					scanf("%f", &aux.valor);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else{
				gotoxy(l, c);
				printf("Alteracao de dados CANCELADA");
			}
			fwrite(&aux, sizeof(TpPizza), 1, ptr);
			getch();
		}
		
		fclose(ptr);
		clrscr();
	}
	
}

void alterarMotoqueiro(void){
	clrscr();
	TpMotoqueiro aux;
	int flag;
	char op;
	int l = 16, c = 10;
	
	FILE *ptr = fopen("Motoqueiros.dat", "rb+");
	
	moldeCadastrar();

	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(l, c);
		printf("Insira o CPF do Motoqueiro que desja ALTERAR:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.cpf);
		c++;
		flag = buscaCPF(ptr, aux.cpf);
		
		while (flag == -1 && strlen(aux.cpf) > 0) {
			int l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um CPF cadastrado:\n");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(aux.cpf);
	
			flag = buscaCPF(ptr, aux.cpf);
			//printf("\nO tamanho de um reg eh: %d e o ponteiro esta em: %d\n", sizeof(TpMotoqueiro), flag);
		}
		
		if(strlen(aux.cpf) > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpMotoqueiro), 1, ptr);
			fseek(ptr, flag, 0);	

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("###Conteudo do Registro###");
			c++;
			gotoxy(l, c);
			printf("CPF: %s", aux.cpf);
			c++;
			gotoxy(l, c);
			printf("NOME: %s", aux.nome);
			c++;
			gotoxy(l, c);
			printf("ENDERECO: %s", aux.endereco);
			c++;
			gotoxy(l, c);
			printf("TELEFONE: %s", aux.telefone);
			c++;
			gotoxy(l, c);
			printf("DATA DE ADMISSAO: %d/%d/%d", aux.data.d, aux.data.m, aux.data.a);

			gotoxy(49, 22);
			printf("ENTER para continuar");
			getch();

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("O que deseja ALTERAR?");
			c++;
			gotoxy(l, c);
			printf("[A] CPF");
			c++;
			gotoxy(l, c);
			printf("[B] NOME");
			c++;
			gotoxy(l, c);
			printf("[C] ENDERECO");
			c++;
			gotoxy(l, c);
			printf("[D] TELEFONE");
			c++;
			gotoxy(l, c);
			printf("[E] DATA DE ADMISSAO");
			c++;
			
			op = toupper(getche());
			
			if(op == 'A'){
				gotoxy(l, c);
				printf("Insira o novo CPF:");
				c++;
				gotoxy(l, c);
				gets(aux.cpf);
				c++;

				flag = validarCPF(aux.cpf);
				while(strlen(aux.cpf) <= 0 || flag != 1){
					gotoxy(l, c);
					printf("Insira um cpf VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.cpf);
					c++;
					flag = validarCPF(aux.cpf);
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'B'){
				printf("Insira o novo NOME:");
				c++;
				gotoxy(l, c);
				gets(aux.nome);
				c++;
				while(strlen(aux.nome) <= 0){
					gotoxy(l, c);
					printf("Insira um nome VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.nome);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'C'){
				gotoxy(l, c);
				printf("Insira o novo ENDERECO:");
				c++;
				gotoxy(l, c);
				gets(aux.endereco);
				c++;

				while(strlen(aux.endereco) <= 0){
					gotoxy(l, c);
					printf("Insira um endereco VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.endereco);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'D'){
				gotoxy(l, c);
				printf("Insira o novo TELEFONE: ");
				c++;
				gotoxy(l, c);
				gets(aux.telefone);
				c++;
				
				while(strlen(aux.telefone) <= 0){
					gotoxy(l, c);
					printf("Insira um telefone VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.telefone);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'E'){
				gotoxy(l, c);
				printf("Insira a nova DATA DE ADMISSAO: [dd mm aaaa]");
				c++;
				gotoxy(l, c);
				scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
				c++;
				
				while(aux.data.d > 31 || aux.data.d < 1 || aux.data.m > 12 || aux.data.m < 1 || aux.data.a > 2024 || aux.data.a < 1){
					gotoxy(l, c);
					printf("Insira uma data VALIDA");
					c++;
					gotoxy(l, c);
					scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else{
				gotoxy(l, c);
				printf("Alteracao de dados CANCELADA");
			}	
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
	int l = 16, c = 10;

	FILE *ptr = fopen("Clientes.dat", "rb+");

	limparquadro();
	moldeCadastrar();
	
	if(ptr == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		gotoxy(l, c);
		printf("Insira o TELEFONE do Cliente que desja ALTERAR:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.telefone);
		c++;
		flag = buscaSentinelaTelefone(ptr, aux.telefone);
		
		while (flag == -1 && strlen(aux.telefone) > 0) {
			int l = 16, c = 10;
			limparquadro();
			gotoxy(l, c);
			printf("Insira um TELEFONE cadastrado:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(aux.telefone);
	
			flag = buscaSentinelaTelefone(ptr, aux.telefone);
			//printf("\nO tamanho de um reg eh: %d e o ponteiro esta em: %d\n", sizeof(TpCliente), flag);
		}
		
		if(strlen(aux.telefone) > 0){
			fseek(ptr, flag, 0);
			fread(&aux,sizeof(TpCliente), 1, ptr);
			fseek(ptr, flag, 0);

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("###Conteudo do Registro###");
			c++;
			gotoxy(l, c);
			printf("TELEFONE: %s", aux.telefone);
			c++;
			gotoxy(l, c);
			printf("NOME: %s", aux.nome);
			c++;
			gotoxy(l, c);
			printf("ENDERECO: %s", aux.endereco);
			c++;
			gotoxy(l, c);
			printf("CIDADE: %s", aux.cidade);
			c++;
			gotoxy(l, c);
			printf("CEP: %s", aux.cep);

			gotoxy(49, 22);
			printf("ENTER para continuar");
			getch();

			l = 30, c =10;
			limparquadro();
			gotoxy(l, c);
			printf("O que deseja ALTERAR?");
			c++;
			gotoxy(l, c);
			printf("[A] TELEFONE");
			c++;
			gotoxy(l, c);
			printf("[B] NOME");
			c++;
			gotoxy(l, c);
			printf("[C] ENDERECO");
			c++;
			gotoxy(l, c);
			printf("[D] CIDADE");
			c++;
			gotoxy(l, c);
			printf("[E] CEP");
			c++;
			
			op = toupper(getche());
			
			if(op == 'A'){
				gotoxy(l, c);
				printf("Insira o novo TELEFONE: ");
				c++;
				gotoxy(l, c);
				gets(aux.telefone);
				c++;
				
				while(strlen(aux.telefone) <= 0){
					gotoxy(l, c);
					printf("Insira um telefone VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.telefone);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'B'){
				printf("Insira o novo NOME:");
				c++;
				gotoxy(l, c);
				gets(aux.nome);
				c++;
				while(strlen(aux.nome) <= 0){
					gotoxy(l, c);
					printf("Insira um nome VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.nome);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'C'){
				gotoxy(l, c);
				printf("Insira o novo ENDERECO:");
				c++;
				gotoxy(l, c);
				gets(aux.endereco);
				c++;

				while(strlen(aux.endereco) <= 0){
					gotoxy(l, c);
					printf("Insira um endereco VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.endereco);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'D'){
				gotoxy(l, c);
				printf("Insira o novo ENDERECO:");
				c++;
				gotoxy(l, c);
				gets(aux.cidade);
				c++;

				while(strlen(aux.cidade) <= 0){
					gotoxy(l, c);
					printf("Insira um endereco VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.cidade);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else if(op == 'E'){
				gotoxy(l, c);
				printf("Insira o novo ENDERECO:");
				c++;
				gotoxy(l, c);
				gets(aux.cep);
				c++;

				while(strlen(aux.cep) <= 0){
					gotoxy(l, c);
					printf("Insira um endereco VALIDO:");
					c++;
					gotoxy(l, c);
					gets(aux.cep);
					c++;
				}
				gotoxy(l, c);
				printf("Dados ALTERADOS");
			}else{
				gotoxy(l, c);
				printf("Alteracao de dados CANCELADA");
			}	
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
		
		if(strcmp(aux.cpf, texto) == 0 && aux.status == 'A') 
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
	int l = 25, c = 10;
	
	FILE *ptrpedido;
	FILE *ptrcliente = fopen("Clientes.dat", "rb+");
	FILE *ptrmotoqueiro = fopen("Motoqueiros.dat", "rb+");
	FILE *ptrpizza = fopen("Pizzas.dat", "rb+");
	
	moldeMenuCadastro();
	limparquadro();
	gotoxy(57, 22); printf("Digite 0 para sair");
	gotoxy(l, c);
	printf("Insira o NUMERO do Pedido:");
	c++;
	fflush(stdin);
	gotoxy(l, c);
	scanf("%d", &aux.numero);
	c++;
	
	flag = verificaNumPedidoCadastrado(aux.numero);
	while(aux.numero > 0 && flag != -1){
		limparquadro();
		l = 25, c = 10;
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l,c);
		printf("Numero de pedido ja CADASTRADO, insira outro:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d", &aux.numero);

		flag = verificaNumPedidoCadastrado(aux.numero);
	}

	gotoxy(57, 22); printf("                  ");
	while(aux.numero > 0 && flag == -1) { //pedido existe
		ptrpedido = fopen("Pedidos.dat", "ab");

		gotoxy(l, c);
		printf("Insira o TELEFONE do Cliente:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.telefone);
		c++;
		
		flag = buscaSentinelaTelefone(ptrcliente, aux.telefone); //busca telefone ate encontrar
		while (flag == -1 && strlen(aux.telefone) > 0) {
			limparquadro();
			l = 25, c = 10;
			gotoxy(l,c);
			printf("Insira um telefone do cliente CADASTRADO:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(aux.telefone);
			c++;

			flag = buscaSentinelaTelefone(ptrcliente, aux.telefone);
		}

		//entra se telefone > 0
		if(strlen(aux.telefone) > 0) {
			gotoxy(l, c);
			printf("Insira o CODIGO dessa Pizza:");
			c++;
			gotoxy(l, c);
			scanf("%d", &aux.codigo);
			c++;

			flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
			while (flag == -1 && aux.codigo > 0) {
				limparquadro();
				l = 25, c = 10;
				gotoxy(57, 22); printf("Digite 0 para sair");
				gotoxy(l,c);
				printf("Insira um codigo CADASTRADO:");
				c++;
				gotoxy(l, c);
				scanf("%d", &aux.codigo);
				c++;

				flag = buscaBinariaCodigo(ptrpizza, aux.codigo);
			}
			gotoxy(57, 22); printf("                  ");

			if(aux.codigo > 0){ // entra se o codigo > 0 e telefone > 0
				gotoxy(l, c);
				printf("Digite o CPF do Motoqueiro");
				c++;
				fflush(stdin);
				gotoxy(l, c);
				gets(aux.cpf);
				c++;
					
				flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				while (flag == -1 && strlen(aux.cpf) > 0){
					limparquadro();
					l = 25, c = 10;
					gotoxy(l,c);
					printf("Digite um CPF do motoqueiro CADASTRADO");
					c++;
					fflush(stdin);
					gotoxy(l, c);
					gets(aux.cpf);
					c++;

					flag = buscaCPF(ptrmotoqueiro, aux.cpf);
				}

				if(strlen(aux.cpf) > 0){ // entra se o cpf > 0 e codigo > 0 e telefone > 0
					strcpy(aux.situacao, "Em preparacao"); 				
					gotoxy(l, c);	
					printf("Insira a DATA do Pedido: [dd mm aaaa]");
					c++;
					gotoxy(l, c);
					scanf("%d %d %d", &aux.dataPedido.d, &aux.dataPedido.m, &aux.dataPedido.a);
					c++;
						
					aux.status = 'A';

					fwrite(&aux, sizeof(TpPedido), 1, ptrpedido);
					fclose(ptrpedido);					
					bubbleSortPedido();

					limparquadro();
					l = 25, c = 10;
					gotoxy(57, 22); printf("Digite 0 para sair");
					gotoxy(l,c);
					printf("Insira o NUMERO do Pedido:");
					c++;
					fflush(stdin);
					gotoxy(l,c);
					scanf("%d", &aux.numero);
					c++;

					flag = verificaNumPedidoCadastrado(aux.numero);
					while(aux.numero > 0 && flag != -1){
						limparquadro();
						l = 25, c = 10;
						gotoxy(57, 22); printf("Digite 0 para sair");
						gotoxy(l,c);
						printf("Numero de pedido ja CADASTRADO, insira outro:");
						c++;
						fflush(stdin);
						gotoxy(l, c);
						scanf("%d", &aux.numero);
						c++;

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
	int l = 25, c = 10;
	
	moldeCadastrar();
	limparquadro();
	gotoxy(57, 22); printf("Digite 0 para sair");
	gotoxy(l,c);
	printf("Insira o CODIGO da Pizza:");
	c++;
	fflush(stdin);
	gotoxy(l,c);
	scanf("%d", &aux.codigo);
	c++;
	
	flag = verificaCodPizzaCadastrado(aux.codigo);
	while(aux.codigo > 0 && flag != -1){
		limparquadro();
		l = 25, c = 10;
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l,c);
		printf("Codigo de pizza ja CADASTRADO, insira outro:");
		c++;
		fflush(stdin);
		gotoxy(l,c);
		scanf("%d", &aux.codigo);
		c++;

		flag = verificaCodPizzaCadastrado(aux.codigo);
	}

	while (aux.codigo > 0) {
		ptrarquivo = fopen("Pizzas.dat", "ab");

		gotoxy(l, c);
		printf("Insira a DESCRICAO dessa Pizza:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.descricao);
		c++;
		gotoxy(l, c);
		printf("Insira o VALOR dessa Pizza:");
		c++;
		gotoxy(l, c);
		scanf("%f", &aux.valor);
		
		aux.status = 'A';

		fwrite(&aux, sizeof(TpPizza), 1, ptrarquivo);
		fclose(ptrarquivo);
		selecaoDiretaPizza();

		limparquadro();
		l = 25, c = 10;
		gotoxy(57, 22); printf("Digite 0 para sair");
		gotoxy(l,c);
		printf("Insira o CODIGO da Pizza:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		scanf("%d", &aux.codigo);
		c++;

		flag = verificaCodPizzaCadastrado(aux.codigo);
		while(aux.codigo > 0 && flag != -1){
			limparquadro();
			l = 25, c = 10;
			gotoxy(57, 22); printf("Digite 0 para sair");
			gotoxy(l,c);
			printf("Codigo de pizza ja CADASTRADO, insira outro:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
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
	int l = 16, c = 10;

	limparquadro();
	moldeCadastrar();
	
	gotoxy(l,c);
	printf("Insira o TELEFONE do cliente que deseja cadastrar:");
	c++;
	fflush(stdin);
	gotoxy(l,c);
	gets(aux.telefone);
	c++;

	flag = validarNumTelefone(aux.telefone);
	verif = verificaClienteCadastrado(aux.telefone);
	while((flag != 1 || verif != -1)  && strlen(aux.telefone) > 0) {
		limparquadro();
		l = 16, c = 10;
		gotoxy(14,c);
		printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro TELEFONE:");
		c++;
		fflush(stdin);
		gotoxy(l,c);
		gets(aux.telefone);
		c++;
		flag = validarNumTelefone(aux.telefone);
		verif = verificaClienteCadastrado(aux.telefone);
	}
	
	while (strcmp(aux.telefone, "\0") != 0 && verif == -1) {
		ptrarquivo = fopen("Clientes.dat", "ab");
		
		gotoxy(l,c);
		printf("Insira o NOME desse cliente:");
		c++;
		gotoxy(l,c);
		gets(aux.nome);
		c++;
		gotoxy(l,c);
		printf("Insira o ENDERECO desse cliente:");
		c++;
		gotoxy(l,c);
		gets(aux.endereco);
		c++;
		gotoxy(l,c);
		printf("Insira a CIDADE desse cliente:");
		c++;
		gotoxy(l,c);
		gets(aux.cidade);
		c++;
		gotoxy(l,c);
		printf("Insira o CEP desse cliente:");
		c++;
		gotoxy(l,c);
		gets(aux.cep);
		c++;
		
		aux.status = 'A';
		
		fwrite(&aux, sizeof(TpCliente), 1, ptrarquivo);
		fclose(ptrarquivo);
		insercaoDiretaCliente();
		
		limparquadro();
		l = 16, c = 10;
		gotoxy(l,c);
		printf("Insira o TELEFONE do cliente que deseja cadastrar:");
		c++;
		fflush(stdin);
		gotoxy(l,c);
		gets(aux.telefone);
		c++;
		
		flag = validarNumTelefone(aux.telefone);
		verif = verificaClienteCadastrado(aux.telefone);
		while((flag != 1 || verif != -1)  && strlen(aux.telefone) > 0) {
			limparquadro();
			l = 16, c = 10;
			gotoxy(14,c);
			printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro TELEFONE:");
			c++;
			fflush(stdin);
			gotoxy(l,c);
			gets(aux.telefone);
			c++;
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
	int l = 19, c = 10;

	limparquadro();
	moldeCadastrar();
	
	gotoxy(l,c);
	printf("Insira o CPF do motoqueiro que deseja cadastrar:");
	c++;
	fflush(stdin);
	gotoxy(l, c);
	gets(aux.cpf);
	c++;

	flag = validarCPF(aux.cpf);
	verif = verificaMotoqueiroCadastrado(aux.cpf);
	while((flag != 1 || verif != -1)  && strlen(aux.cpf) > 0) {
		l = 19, c = 10;
		limparquadro();
		gotoxy(l,c);
		printf("CPF INVALIDO ou ja CADASTRADO, insira outro CPF:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.cpf);
		c++;
		flag = validarCPF(aux.cpf);
		verif = verificaMotoqueiroCadastrado(aux.cpf);
	}
	
	while(strlen(aux.cpf) > 0 && verif == -1) {
		ptrarquivo = fopen("Motoqueiros.dat", "ab");

		gotoxy(l, c);
		printf("Insira o NOME desse motoqueiro:");
		c++;
		fflush(stdin);
		gotoxy(l, c);
		gets(aux.nome);
		c++;
		gotoxy(l, c);
		printf("Insira o ENDERECO desse motoqueiro:");
		c++;
		gotoxy(l, c);
		gets(aux.endereco);
		c++;
		gotoxy(l, c);
		printf("Insira o TELEFONE desse motoqueiro:");
		c++;
		gotoxy(l, c);
		gets(aux.telefone);
		c++;

		flag = validarNumTelefone(aux.telefone);
		while(flag != 1 && strlen(aux.telefone) > 0){
			limparquadro();
			l = 16, c = 10;
			gotoxy(14,c);
			printf("TELEFONE INVALIDO ou ja CADASTRADO, insira outro TELEFONE:");
			c++;
			fflush(stdin);
			gotoxy(l, c);
			gets(aux.telefone);
			c++;
			flag = validarNumTelefone(aux.telefone);
		}
		if(strlen(aux.telefone) > 0){
			gotoxy(l, c);
			printf("Insira a DATA DE ADMISSAO desse motoqueiro: [dd mm aaaa]");
			c++;
			gotoxy(l, c);
			scanf("%d %d %d", &aux.data.d, &aux.data.m, &aux.data.a);
			
			aux.status = 'A';

			fwrite(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
			fclose(ptrarquivo);
			
			limparquadro();
			l = 16, c = 10;
			gotoxy(19,c);
			printf("Insira o CPF do motoqueiro que deseja cadastrar:");
			c++;
			fflush(stdin);
			gotoxy(19, c);
			gets(aux.cpf);

			flag = validarCPF(aux.cpf);
			verif = verificaMotoqueiroCadastrado(aux.cpf);
			while((flag != 1 || verif != -1)  && strlen(aux.cpf) > 0) {
				printf("CPF INVALIDO ou ja CADASTRADO, insira outro CPF:");
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
	int l = 30, c = 10;
		
	FILE *ptrarquivo = fopen("Clientes.dat", "rb");

	moldeCadastrar();
		
	if (ptrarquivo == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else{
		fread (&aux, sizeof(TpCliente), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				limparquadro();
				l = 30, c = 10;
				gotoxy(l, c);
				printf("TELEFONE: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("NOME: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("ENDERECO: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("CIDADE: %s", aux.cidade);
				c++;
				gotoxy(l, c);
				printf("CEP: %s", aux.cep);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);

				gotoxy(49, 22);
				printf("ENTER para proxima pagina");
				getch();
				
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
	int l = 30, c = 10;

	FILE *ptrarquivo = fopen("Motoqueiros.dat", "rb");
	
	moldeCadastrar();
	
	if (ptrarquivo == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura");
	}else {
		fread(&aux, sizeof(TpMotoqueiro), 1, ptrarquivo);
		while (!feof(ptrarquivo)){
			if(aux.status != 'I'){
				limparquadro();
				l = 30, c = 10;
				gotoxy(l, c);
				printf("CPF: %s", aux.cpf);
				c++;
				gotoxy(l, c);
				printf("NOME: %s", aux.nome);
				c++;
				gotoxy(l, c);
				printf("ENDERECO: %s", aux.endereco);
				c++;
				gotoxy(l, c);
				printf("TELEFONE: %s", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("DATA DE ADMISSAO: %d/%d/%d", aux.data.d, aux.data.m, aux.data.a);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);

				gotoxy(49, 22);
				printf("ENTER para proxima pagina");
				getch();

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
	int l = 30, c = 10;

	FILE *ptrarquivo = fopen("Pizzas.dat", "rb");
	
	moldeCadastrar();

	if (ptrarquivo == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura\n");
	}else{
		fread (&aux, sizeof(TpPizza), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				limparquadro();
				l = 30, c = 10;
				gotoxy(l, c);
				printf("CODIGO: %d", aux.codigo);
				c++;
				gotoxy(l, c);
				printf("DESCRICAO: %s", aux.descricao);
				c++;
				gotoxy(l, c);
				printf("VALOR: %.2f", aux.valor);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c", aux.status);

				gotoxy(49, 22);
				printf("ENTER para proxima pagina");
				getch();
			}
			fread(&aux, sizeof(TpPizza), 1, ptrarquivo);
		}
		
		fclose(ptrarquivo);
	}
	
	getch();
	clrscr();
}

void exibirPedidos(void){
	clrscr();
	TpPedido aux;
	int l = 30, c = 10;

	FILE *ptrarquivo = fopen("Pedidos.dat", "rb");
	
	moldeCadastrar();
	
	if (ptrarquivo == NULL){
		gotoxy(l, c);
		printf("ERRO de abertura\n");
	}else{
		fread (&aux, sizeof(TpPedido), 1, ptrarquivo);

		while (!feof(ptrarquivo)) {
			if(aux.status != 'I'){
				limparquadro();
				l = 30, c = 10;
				gotoxy(l, c);
				printf("NUMERO: %d\n", aux.numero);
				c++;
				gotoxy(l, c);
				printf("TELEFONE: %s\n", aux.telefone);
				c++;
				gotoxy(l, c);
				printf("CODIGO: %d\n", aux.codigo);
				c++;
				gotoxy(l, c);
				printf("CPF: %s\n", aux.cpf);
				c++;
				gotoxy(l, c);
				printf("SITUACAO: %s\n", aux.situacao);
				c++;
				gotoxy(l, c);
				printf("DATA DO PEDIDO: %d/%d/%d\n", aux.dataPedido.d, aux.dataPedido.m, aux.dataPedido.a);
				c++;
				gotoxy(l, c);
				printf("STATUS: %c\n\n", aux.status);

				gotoxy(49, 22);
				printf("ENTER para proxima pagina");
				getch();
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
	clrscr();
	moldeMenuInicial();

	gotoxy(14,12);
	printf("[1]Cadastrar");

	gotoxy(38,12);
	printf("[2]Exibir");

	gotoxy(60,12);
	printf("[3]Alterar");

	gotoxy(15,19);
	printf("[4]Excluir");

	gotoxy(36,19);
	printf("[5]Relatorios");

	gotoxy(58,19);
	printf("[6]Estatisticas");
	gotoxy(76,23);

	return getch();
}

char menuCad(void) {
	clrscr();
	moldeMenuCadastro();
	
	gotoxy(22,12);
	printf("[1]CLIENTES");

	gotoxy(51,12);
	printf("[2]MOTOQUEIROS");

	gotoxy(23,19);
	printf("[3]PIZZAS");
	
	gotoxy(53,19);
	printf("[4]PEDIDOS");
	gotoxy(76,23);

	return getch();
}

char menuExib(void) {
	clrscr();
	moldeMenuExibir();
	
	gotoxy(22,12);
	printf("[1]CLIENTES");

	gotoxy(51,12);
	printf("[2]MOTOQUEIROS");

	gotoxy(23,19);
	printf("[3]PIZZAS");
	
	gotoxy(53,19);
	printf("[4]PEDIDOS");
	gotoxy(76,23);

	return getch();
}

char menuAlt(void) {
	clrscr();
	moldeMenuAlterar();
	
	gotoxy(22,12);
	printf("[1]CLIENTES");

	gotoxy(51,12);
	printf("[2]MOTOQUEIROS");

	gotoxy(23,19);
	printf("[3]PIZZAS");
	
	gotoxy(53,19);
	printf("[4]PEDIDOS");
	gotoxy(76,23);

	return getch();
}

char menuExclLF(void) {
	clrscr();
	moldeMenuTipoExclusao();

	gotoxy(23,15);
	printf("[1] FISICA");
	
	gotoxy(54,15);
	printf("[2] LOGICA");
	gotoxy(76,23);

	return getch();
}

char menuExcl(void) {
	clrscr();
	moldeMenuExcluir();
	
	gotoxy(22,12);
	printf("[1]CLIENTES");

	gotoxy(51,12);
	printf("[2]MOTOQUEIROS");

	gotoxy(23,19);
	printf("[3]PIZZAS");
	
	gotoxy(53,19);
	printf("[4]PEDIDOS");
	gotoxy(76,23);

	return getche();
}

char menuRel(void) {
	clrscr();
	moldeMenuRelatorio();

	gotoxy(17,11); printf("Exibir");
	gotoxy(13,12); printf("[1] Estado");
	gotoxy(17,13); printf("Pizza");

	gotoxy(40,11); printf("Filtrar");
	gotoxy(35,12); printf("[2]  Cliente");
	gotoxy(39,13); printf("por inicial");

	gotoxy(62,11); printf("Relatorio");
	gotoxy(58,12); printf("[3]    de");
	gotoxy(62,13); printf("Clientes");
	
	gotoxy(17,18); printf("Motoqueiro");
	gotoxy(13,19); printf("[4] com maior");
	gotoxy(17,20); printf("entrega");

	gotoxy(41,18); printf("Rank");
	gotoxy(35,19); printf("[5]    de");
	gotoxy(40,20); printf("Pizzas");

	gotoxy(76,23);

	return getch();
}

char menuEst(void) {
	clrscr();
	moldeMenuEstatisticas();

	gotoxy(16,11); printf("Relatorio");
	gotoxy(13,12); printf("[1]  Pizza");
	gotoxy(16,13); printf("mais pedida");

	gotoxy(38,11); printf("Relatorio");
	gotoxy(35,12); printf("[2]  Pizza");
	gotoxy(38,13); printf("menos pedida");

	gotoxy(60,11); printf("Cliente que");
	gotoxy(58,12); printf("[3] mais pede");
	gotoxy(64,13); printf("Pizza");
	
	gotoxy(16,18); printf("Motoqueiro");
	gotoxy(13,19); printf("[4]  menos");
	gotoxy(16,20); printf("experiente");

	gotoxy(36,18); printf("Motoqueiro com");
	gotoxy(35,19); printf("[5]mais entregas");
	gotoxy(40,20); printf("no dia");

	gotoxy(59,18); printf("Maior consumo");
	gotoxy(58,19); printf("[6] de pizza");
	gotoxy(60,20); printf("determinada");

	gotoxy(76,23);
	
	return getch();
}