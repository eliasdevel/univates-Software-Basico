#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define clear() printf("\033[H\033[J")

int is_valid_option(char option, int type_validation){
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

	int i =0;

	while(i<strlen(possible_inputs)){
		if(option == possible_inputs[i]){
			return 1;
		}

		i++;
	}
	possible_inputs = NULL;

	return 0;
}




void print_invalid_option(char option){
	printf(ANSI_COLOR_RED "%c é uma opção inválida!!! " ANSI_COLOR_RESET "\n",option);
}
int print_invalid_int(){
	printf(ANSI_COLOR_RED " Deve ser um numero inteiro!!! " ANSI_COLOR_RESET "\n");
}
int print_invalid_float(){
	printf(ANSI_COLOR_RED " Deve ser um numero valido!!! " ANSI_COLOR_RESET "\n");
}
int print_invalid_yes_no(){
	printf(ANSI_COLOR_RED " A opção deve ser s ou n!!! " ANSI_COLOR_RESET "\n");
}
int print_sucess(int id){
	printf(ANSI_COLOR_GREEN " Registro (ID = %d) cadastrado com sucesso! " ANSI_COLOR_RESET "\n",id);
}
int print_exit(){
	printf( ANSI_COLOR_GREEN "Bye\n" ANSI_COLOR_RESET  );
}

void print_menu(){

	printf("Sistema de controle imobiliário:\n  [1] Listar imóveis\n  [2] Cadastrar imóvel\n  [3] Editar imóvel\n  [4] Buscar imóvel\n  [x] Sair do programa\nDigite uma das opções:\n" );
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

void print_tipo_cadastro(){
	printf("Tipo (1 - casa; 2 - apartamento):");
}


void cadastro(){
	struct imovel im;
	im.id = id;
	printf("Cadastrar imóveis:\n");

	print_tipo_cadastro();
	fgets(im.tipo,255,stdin);

	while(!is_valid_option(im.tipo[0],2)){
		print_invalid_option(im.tipo[0]);
		print_tipo_cadastro();
		fgets(im.tipo,255,stdin);
		getchar();
	}

	printf("Descricao:" );
	fgets(im.descricao,255,stdin);


	printf("Quartos:" );
	while(!scanf("%d", &im.quartos)){
		print_invalid_int();
		printf("Quartos:" );
		getchar();
	}

	printf("Área (m²):" );
	while(!scanf("%f", &im.area)){
		print_invalid_float();
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
		print_invalid_int();
		printf("Número:" );
		getchar();
	}

	printf("Deseja cadastrar o registro? [s/n]:");
	char option[2];
	getchar();
	fgets(option,2,stdin);

	//verify if the input is right
	while(!is_valid_option(option[0],3)){
		getchar();
		print_invalid_yes_no();
		fgets(option,2,stdin);
	}

	if(option[0]=='s'){
		clear();
		imoveis[im.id] = im;
		print_sucess(im.id);
		id++;
	}
	getchar();
	main();
}
void list() {
	int i = 1;
	while (i<1000) {
		if(imoveis[i].id){
			printf("----\n");
			printf("ID: %d\n",imoveis[i].id);
			printf("Tipo: %s\n", imoveis[i].tipo[0] == '1' ? "Casa":"Apartamento");
			printf("Descricao: %s\n",imoveis[i].descricao);
			printf("Quartos: %d\n",imoveis[i].quartos);
			printf("Área: %fm²\n",imoveis[i].area);
			printf("Cidade: %s\n",imoveis[i].cidade);
			printf("Rua: %s\n",imoveis[i].rua);
			printf("Numero: %d\n",imoveis[i].numero);
			printf("----\n");
		}

		i++;
	}
	getchar();
	main();
}

int main(){

	print_menu();
	char option[2];
	fgets(option,2,stdin);

	//verify if the input is right
	while(!is_valid_option(option[0],1)){
		getchar();
		print_invalid_option(option[0]);
		print_menu();
		fgets(option,2,stdin);

	}
	switch(option[0]){
		case '1':
			list();
			break;
		case '2':
			getchar();
			cadastro();
			break;
		case 'x':
			print_exit();
			break;
		case 'X':
			print_exit();
			break;
	}

	return 0;
}
