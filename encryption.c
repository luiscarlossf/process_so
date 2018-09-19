#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX 102//Tamanho máximo da mensagem
#define TRUE 1
#define FALSE 0

/*
  Recebe como parâmetro a message que deseja aplicar o códido de 
  Augustus. Retorna a message criptografada.
*/
void encryption(char *message, char *encrypted_message)
{

	for(int i = 0; i< strlen(message); i++, encrypted_message[i] = '\0'){
		switch(message[i])
		{
			case ' ': encrypted_message[i] = ' '; break;
			case 'a': encrypted_message[i] = 'b'; break;
			case 'A': encrypted_message[i] = 'B'; break;
			case 'b': encrypted_message[i] = 'c'; break;
			case 'B': encrypted_message[i] = 'C'; break;
			case 'c': encrypted_message[i] = 'd'; break;
			case 'C': encrypted_message[i] = 'D'; break;
			case 'd': encrypted_message[i] = 'e'; break;
			case 'D': encrypted_message[i] = 'E'; break;
			case 'e': encrypted_message[i] = 'f'; break;
			case 'E': encrypted_message[i] = 'F'; break;
			case 'f': encrypted_message[i] = 'g'; break;
			case 'F': encrypted_message[i] = 'G'; break;
			case 'g': encrypted_message[i] = 'h'; break;
			case 'G': encrypted_message[i] = 'H'; break;
			case 'h': encrypted_message[i] = 'i'; break;
			case 'H': encrypted_message[i] = 'I'; break;
			case 'i': encrypted_message[i] = 'j'; break;
			case 'I': encrypted_message[i] = 'J'; break;
			case 'j': encrypted_message[i] = 'k'; break;
			case 'J': encrypted_message[i] = 'K'; break;
			case 'k': encrypted_message[i] = 'l'; break;
			case 'K': encrypted_message[i] = 'L'; break;
			case 'l': encrypted_message[i] = 'm'; break;
			case 'L': encrypted_message[i] = 'M'; break;
			case 'm': encrypted_message[i] = 'n'; break;
			case 'M': encrypted_message[i] = 'N'; break;
			case 'n': encrypted_message[i] = 'o'; break;
			case 'N': encrypted_message[i] = 'O'; break;
			case 'o': encrypted_message[i] = 'p'; break;
			case 'O': encrypted_message[i] = 'P'; break;
			case 'p': encrypted_message[i] = 'q'; break;
			case 'P': encrypted_message[i] = 'Q'; break;
			case 'q': encrypted_message[i] = 'r'; break;
			case 'Q': encrypted_message[i] = 'R'; break;
			case 'r': encrypted_message[i] = 's'; break;
			case 'R': encrypted_message[i] = 'S'; break;
			case 's': encrypted_message[i] = 't'; break;
			case 'S': encrypted_message[i] = 'T'; break; 
			case 't': encrypted_message[i] = 'u'; break;
			case 'T': encrypted_message[i] = 'U'; break;
			case 'u': encrypted_message[i] = 'v'; break;
			case 'U': encrypted_message[i] = 'V'; break;
			case 'v': encrypted_message[i] = 'w'; break;
			case 'V': encrypted_message[i] = 'W'; break;
			case 'w': encrypted_message[i] = 'x'; break;
			case 'W': encrypted_message[i] = 'X'; break;
			case 'x': encrypted_message[i] = 'y'; break;
			case 'X': encrypted_message[i] = 'Y'; break;
			case 'y': encrypted_message[i] = 'z'; break;
			case 'Y': encrypted_message[i] = 'Z'; break;
			case 'z': encrypted_message[i] = 'a'; break;
			case 'Z': encrypted_message[i] = 'A'; break;
			default:  encrypted_message[i] = message[i]; break;
		}
	}
}

int main(int argc, char* argv[], char * envp[])
{
	char out_message[MAX];
	encryption(argv[0], out_message);
	int cont = write(STDIN_FILENO, out_message, strlen(out_message));
	printf("Foram escritos %d elementos no pipe.\n", cont);
	close(STDIN_FILENO);
	exit(0);
}