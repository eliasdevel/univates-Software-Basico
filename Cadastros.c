#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define clear() printf("\033[H\033[J")

#ifndef MAIN_H
#define MAIN_H

int main();

#endif
/*
Git Hub :https://github.com/eliasdevel/univates-Software-Basico
*/
int compareStrings(char str1[],char str2[]){
	int ret =1;
	if(strlen(str1) != strlen(str2)){

		ret = 0;
	}
	int i;
	int len = strlen(str1);
	for ( i = 0; i < len; i++) {
		if(str1[i] != str2[i]){
			ret = 0;
		}
	}

	return ret;
}
void removeEnter(char teste[]) {
	int leng = strlen(teste);
	int i;
	for ( i = 0; i < leng; i++) {
		if(teste[i] == '\n' || teste[i] == '\r'){
			teste[i] = '\0';
		}
	}
}

int isValidOption(char option, int type_validation){
	char* possible_inputs;
	// for validation of main menu function
	if(type_validation == 1){
		possible_inputs = "1234xX";
	}
	// for validation of cadastro function
	if(type_validation == 2){
		possible_inputs = "12";
	}
	// for validation of cadastro function
	if(type_validation == 3){
		possible_inputs = "snSN";
	}
	// for validation of cadastro function
	if(type_validation == 4){
		possible_inputs = "123";
	}

	int ret =0;
	int i =0;
	int len = strlen(possible_inputs);
	while(i < len){
		if(option == possible_inputs[i]){
			ret = 1;
		}
		i++;
	}
	possible_inputs = NULL;
	return ret;
}
void printInvalidOption(char option){
	printf(ANSI_COLOR_RED "%c é uma opção inválida!!! " ANSI_COLOR_RESET "\n",option);
}
void printInvalidInt(){
	printf(ANSI_COLOR_RED " Deve ser um numero inteiro!!! " ANSI_COLOR_RESET "\n");
}
void printInvalidFloat(){
	printf(ANSI_COLOR_RED " Deve ser um numero valido!!! " ANSI_COLOR_RESET "\n");
}
void printInvalidYesNo(){
	printf(ANSI_COLOR_RED " A opção deve ser s ou n!!! " ANSI_COLOR_RESET "\n");
}
void printSucess(int id){
	printf(ANSI_COLOR_GREEN " Registro (ID = %d) cadastrado com sucesso! " ANSI_COLOR_RESET "\n",id);
}
void printExit(){
	printf( ANSI_COLOR_GREEN "Bye\n" ANSI_COLOR_RESET  );
}
void printMenu(){
	printf("Sistema de controle imobiliário:\n  [1] Listar imóveis\n  [2] Cadastrar imóvel\n  [3] Editar imóvel\n  [4] Buscar imóvel\n  [x] Sair do programa\nDigite uma das opções:\n" );
}
void printMenuBuscar(){
	printf("	[1] Buscar por tipo\n	[2] Buscar por cidade\n	[3] Buscar por número de quartos\n	Digite uma das opções:");
}

struct imovel {
    int   id;
    char  tipo[2];
    char  descricao[255];
    int   quartos;
    float area;
    char  cidade[255];
    char  rua[255];
    int   numero;
};

struct imovel imoveis[1000];
int id = 1;

void printTipoCadastro(){
	printf("Tipo (1 - casa; 2 - apartamento):");
}



void cadastro(int editId){
	struct imovel im;
	im.id = id;
	if (editId){
		im.id = editId;
	}
	printf("Cadastrar imóveis:\n");

	printTipoCadastro();
	fgets(im.tipo,255,stdin);

	while(!isValidOption(im.tipo[0],2)){
		printInvalidOption(im.tipo[0]);
		printTipoCadastro();
		fgets(im.tipo,255,stdin);
		getchar();
	}

	printf("Descricao:" );
	fgets(im.descricao,255,stdin);


	printf("Quartos:" );
	while(!scanf("%d", &im.quartos)){
		printInvalidInt();
		printf("Quartos:" );
		getchar();
	}

	printf("Área (m²):" );
	while(!scanf("%f", &im.area)){
		printInvalidFloat();
		printf("Área (m²):" );
		getchar();
	}
	getchar();
	printf("Cidade:" );
	fgets(im.cidade,255,stdin);

	printf("Rua:" );
	fgets(im.rua,255,stdin);

	printf("Número:" );
	while(!scanf("%d", &im.numero)){
		printInvalidInt();
		printf("Número:" );
		getchar();
	}

	printf("Deseja cadastrar o registro? [s/n]:");
	char option[2];
	getchar();
	fgets(option,2,stdin);

	//verify if the input is right
	while(!isValidOption(option[0],3)){
		getchar();
		printInvalidYesNo();
		fgets(option,2,stdin);
	}

	if(option[0]=='s'){
		clear();
		imoveis[im.id] = im;
		printSucess(im.id);
		id++;
	}
	getchar();
	main();
}

void edit(){
	int editId;
	printf("Editar imóvel:" );
	while(!scanf("%d", &editId)){
		printInvalidInt();
		printf("Editar imóvel:" );
		getchar();
	}
	getchar();
	cadastro(editId);
}



void list(char query[],int type) {

	int i = 1;
	int wilList = 1;
	removeEnter(query);
	while (i<1000) {

		removeEnter(imoveis[i].cidade);
		removeEnter(imoveis[i].rua);
		removeEnter(imoveis[i].descricao);

		if(type == 1 && imoveis[i].tipo[0] != query[0] ){
			wilList = 0;
		}
		if(type == 2 && !compareStrings( imoveis[i].cidade , query) ){

			wilList = 0;
		}

		if(type == 3 && imoveis[i].quartos != atoi(query) ){
			wilList = 0;
		}

		if(imoveis[i].id && wilList  ){

			printf("----\n");
			printf("ID: %d\n",imoveis[i].id);
			printf("Tipo: %s\n", imoveis[i].tipo[0] == '1' ? "Casa":"Apartamento");
			printf("Descricao: %s\n",imoveis[i].descricao);
			printf("Quartos: %d\n",imoveis[i].quartos);
			printf("Área: %.2fm²\n",imoveis[i].area);
			printf("Cidade: %s\n",imoveis[i].cidade);
			printf("Rua: %s\n",imoveis[i].rua);
			printf("Numero: %d\n",imoveis[i].numero);
			printf("----\n");

		}
		wilList = 1;
		i++;

	}

	getchar();

	query = NULL;
	main();
}

void buscar(){
	printMenuBuscar();
	getchar();
	char option[2];
	fgets(option,2,stdin);

	while(!isValidOption(option[0],4)){
		getchar();
		printInvalidOption(option[0]);
		printMenuBuscar();
		fgets(option,2,stdin);
	}
	char query[255];
	char option_2[2];


	switch(option[0]){
		case '1':
		printf("Busca por casa (1) ou apartamento (2):\n");
		getchar();
		fgets(option_2,2,stdin);
		while(!isValidOption(option_2[0],2)){
			printInvalidOption(option_2[0]);
			printf("Busca por casa (1) ou apartamento (2):\n");
			fgets(option_2,2,stdin);
			getchar();
		}

			list(option_2,1);
		case '2':
			printf("	Buscar por Cidade:\n");
			getchar();
			fgets(query,255,stdin);

			while(getchar() != '\n' ){}

			list(query,2);
			break;
		case '3':
			printf("Busca por numero de quartos:\n");

			getchar();
			fgets(query,11,stdin);

			while(getchar() != '\n'){}
			list(query,3);
			break;
	}

}



int main(){

	printMenu();
	char option[2];
	fgets(option,2,stdin);

	//verify if the input is right
	while(!isValidOption(option[0],1)){
		getchar();
		printInvalidOption(option[0]);
		printMenu();
		fgets(option,2,stdin);

	}
	switch(option[0]){
		case '1':
			list("",0);

			break;
		case '2':
			getchar();
			cadastro(0);
			break;
		case '3':
			edit();
			getchar();
			break;
		case '4':
			buscar();
			getchar();
			break;
		case 'x':
			getchar();
			printExit();
		
			break;
		case 'X':
		    getchar();
			printExit();
		
			break;
	}

	return 0;
}
