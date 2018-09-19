#include <stdio.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MAX 102

/*
	Armazena no arquivo binário a message passada por parâmetro.
*/
void savemessage(char* message, char *file_name)
{
	FILE * arquivo = fopen(file_name, "wb");

	if (arquivo == NULL){
		fprintf(stderr, "Error! Impossível criar arquivo\n");
	}else{
		if(fwrite(message, sizeof(char), MAX, arquivo) != MAX)
			fprintf(stderr, "Não foi possivel gravar todos os dados \n");
	}

}

/*
	O programa fica constantemente procurando mensagens para armazenar no arquivo binário
*/
int main(int argc, char* argv[], char * envp[])
{
	while(TRUE){
		if (strcmp(argv[1],"TRUE") == 0){
			savemessage(argv[0], "encryption.dat");
			strcpy(argv[1], "FALSE");
		}
	}
}