#include "utils.h"

void terminarExecucao();

int main(int argc, char** argv){
	char fifo[40];
	int fd_out, fd_in, num;
	cli j;
	
	signal(SIGUSR1, terminarExecucao);

	
	if (access(FIFO_SRV, F_OK) != 0){
		printf("ERRO - NAO FOI POSSIVEL ENCONTRAR O ARBITO");
		exit(1);
	}
	
	
	j.pid = getpid();
	sprintf(fifo, FIFO_CLI, j.pid);
	
	mkfifo(fifo,0600);
	printf("Cliente inicializado.\n");
	
	fd_out = open(FIFO_SRV, O_WRONLY);
	
	printf("Nome: "); fflush(stdout);
	scanf("%s", j.nome);
	j.aceite = -1;
	

	
	do{
		
		num = write(fd_out, &j, sizeof(cli));
		
		fd_in = open(fifo, O_RDONLY);
		num = read(fd_in, &j, sizeof(cli));
		close(fd_in);
		
		printf("Nome [%s] valido", j.nome); fflush(stdout);
		scanf("%s", j.res);
		
	}while(strcmp(j.res,"sair")!=0);		

	close(fd_out);
	unlink(fifo);
	
	exit(5);
	
	
	
	

}

void terminarExecucao(){
	printf("\nKickado do Servidor...\n");
	char temp[20];
	sprintf(temp, FIFO_CLI, getpid());
	unlink(temp);

	exit(0);
}
