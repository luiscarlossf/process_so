#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#define MAX 102//Tamanho máximo da mensagem
#define TRUE 1
#define FALSE 0

void menu();

/*
	O programa criptografa uma mensagem usando o códido de Augustus.
	Além disso, tem uma ferramenta inspirada no log do banco de dados
	que armazena todas as mensagens que são criptografadas pelo programa.
*/

int main(int argc, const char* argv[], char * envp[])
{
	char input_message[MAX];
	char output_message[MAX];
	pid_t child_pid2, child_pid1;
	char  checkpoint[5]; //TRUE or FALSE--Controla o momento que os dados são armazenados no arquivo binário
	int child_status;
	int pipes_fd[2];
	int flag = TRUE;
	int save_pid; // Guarda o pid do child_process 1, que salva as mensagens no processo.

	while(TRUE){
    	printf("\n===============================\nProcesso ID %d\n", (int) getpid());

		printf("===============================\nDigite a mensagem que deseja criptografar: \
			  \n(Por favor, sem acentos e com no máximo 100 caracteres) exit()- para sair\n");
		fgets(input_message, MAX, stdin);
		strcpy(checkpoint, "TRUE");

		if(strcmp(input_message, "exit()\n")==0){
			kill(save_pid, SIGTERM);// Mata o processo que salva as mensagens no arquivo binário
			break;
		}
        


		printf("Criptografando...%s\n",input_message);

		if(pipe(pipes_fd)<0){
			perror("pipe");
			return -1;
		}


//===============================================================
		//ARMAZENAMENTO EM ARQUIVO BINÁRIO
		if (flag){
			//Lista de argumentos do child_process 2
			char * args2[] = {
				output_message,
				checkpoint,
				NULL
			};

			//Todas as mensagens criptografadas no programa são armzenadas 
			//em um arquivo binário.
			child_pid1 = fork();
			if (child_pid1 != 0){
				save_pid = child_pid1;
				printf("Criado processo filho (savemessage). Child Process ID %d\n", save_pid);
			}else{
				execve("./savemessage", args2, envp);
				fprintf(stderr, "ocorreu um erro em execve (savemessage)\n");
				abort();
			}
			flag = FALSE;
		}

 //==============================================================================
		 //CRIPTOGRAFIA
		char * args[] = { //Lista de argumentos
			input_message,
			NULL
		};

	    child_pid2 = fork();
		if (child_pid2 != 0){
			printf("Criado processo filho (encryption). Child Process ID %d\n", child_pid2);
			wait(&child_status); //Espera a mensagem ser criptografada
			if(WIFEXITED (child_status))
				printf("o processo filho (%d) terminou normalmente, com código de saída %d\n", child_pid2, WEXITSTATUS(child_status));
			else
				printf("o processo filho (%d) terminou inesperadamente\n", child_pid2);
			
			//A saída gerada pelo processo filho é lida e exibida
			close(pipes_fd[1]);
			int cont1 = read(pipes_fd[0], output_message, strlen(input_message));
			output_message[strlen(input_message)]= '\0';
			printf("Foram lidos %d elementos do pipe.\n", cont1);
			close(pipes_fd[0]);
			printf("+++++++++++++++++++++++++++++++++++++++++++\n");
		    printf("Saída: %s", output_message);
		    printf("+++++++++++++++++++++++++++++++++++++++++++\n");
		    strcpy(checkpoint, "TRUE");


		}else{
			//Novo processo que realiza a criptografia da mensagem
			close(pipes_fd[0]);
			dup2(pipes_fd[1], STDIN_FILENO);
			execve("./encryption", args, envp);
			fprintf(stderr, "ocorreu um erro em execve (encryption)\n");
			abort();
		}
		sleep(2);

	}
	return 0;

}