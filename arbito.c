#include "utils.h"

void verifica_var_amb(char *dir,int *max) {
	//defenir diretorios dos jogos
	if (getenv("GAMEDIR"))
		strcpy(dir, getenv("GAMEDIR"));
	else
		strcpy(dir, GAME_DIR);

	//defenir numero maximo de jogadores
	if (getenv("MAXPLAYER")) {
		*max = atoi(getenv("MAXPLAYER"));
		if (*max > 30)
			*max = 30;
	}
	else
		*max = MAX_PLAYER;
}

void addUser(cli *c, cli *Users, int *n, int max){
	int i;	

	for(i=0;i<max;i++)
  		if((Users+i)->aceite==-1)
  			break;
  		
  	 if(i==max)
  	 { 
  	 	printf("\nNao existem vagas\n"); fflush(stdout);
  	 	strcpy(c->res, "Nao existem vagas");
  	 	return;
  	 }
  	
  	 
  	 char nome[15], nomeaux[40];
  	 int j,st,x;
  	 strcpy(nome,c->nome);
  	 for(j=0,st=1,x=0;j<max;j++)
  	 {
    		if((Users+j)->aceite==1)
			if(strcmp((Users+j)->nome,nome)==0)
      			{
				if(x) nome[strlen(nome)-1]='\0';
				
        			sprintf(nomeaux,"%s%d",nome,st++);
      				strcpy(nome,nomeaux);
				x=1;
        			j=-1;
      			}
  	}
	
	*n = *n + 1;			//estas 3 linhas provavelmente vao de cona com mutex ñ sei
	strcpy(c->nome,nome);
	c->aceite = 1;
	
	strcpy((Users+i)->nome,nome);
  	(Users+i)->pid=c->pid;
  	(Users+i)->aceite=1;

  	return;	
	}
	
	
	void mostraJogadores(cli *clientes, int max){
			
			for(int i=0;i<max;i++)
  				if((clientes+i)->aceite==1)
  					printf("\nNome: %s\nJogo: %s\n", (clientes+i)->nome, (clientes+i)->nomeJogo);
	}
	
	int kickPlayer(cli *Users,char cmd[],int max){
		int i;	

		for(i=0;i<max;i++)
  			if((Users+i)->aceite==1)
  				if(strcmp(cmd, (Users+i)->nome)==0){
  					(Users+i)->aceite = -1;

  					kill((Users+i)->pid, SIGUSR1);
  					return 0;
  				}
  		return -1; //erro
	}
	
		int interpretaCmdUser(char cmd[]){
		if(cmd[0]=='#'){
			if(strcmp(cmd, "#mygame")==0){

			}
			else if(strcmp(cmd, "#quit")==0){

			}
		}
		return 0;
	}
	
	
	

int main(int argc, char** argv) {

	char game_dir[50], fifo[40], cmd[40];
	int max_player, duracao_camp,tempo_espera, fd, fdr, num, res, nPlayers=0;
	cli c;
	bool termina = false;
	
	
	struct timeval tempo;
	fd_set fds;
	
	
				/*------------------Argumentos & outras cenas------------------*/
			
	if (argc < 3) {
			printf("ERRO - FALTAMARGUMENTOS NA LINHA DE COMANDOS\n");
			exit(-1);
	}
	else {
		if (atoi(argv[1]) && atoi(argv[2])) {
			duracao_camp = atoi(argv[1]);
			tempo_espera = atoi(argv[2]);
		}
		else {
			printf("ERRO - PARAMETROS DA LINHA DE ARGUMENTO FORAM MAL INTRODUZIDOS\n");
			exit(-1);
		}
	}
	
	verifica_var_amb(game_dir, &max_player);
	cli clientes[max_player];
	
	  	for(int i=0;i<max_player;i++)
  	{
  		clientes[i].aceite=-1;
  		clientes[i].pid=-1;
  	}

			/*------------------Servidor------------------*/


	//verificar se ja existe algum server a correr
	if (access(FIFO_SRV, F_OK) != 0){
		mkfifo(FIFO_SRV, 0600);
		printf("Servidor iniciado...\n");
		}
	else {
		fprintf(stderr, "ERRO Ja existe um servidor a funcionar!\n");
		exit(1);
	}
	
	
		fd = open(FIFO_SRV, O_RDWR);
	do{
		
		
		printf("\nCOMANDO: ");	fflush(stdout);
		
		FD_ZERO(&fds);
		FD_SET(0, &fds);	//TECLADO
		FD_SET(fd, &fds);	//FIFO  	
		//tempo.tv_sec = 5; tempo.tv_usec = 0;
		res = select(fd+1, &fds, NULL, NULL, NULL);
		
		if(res == 0){
			//PODEMOS USAR ISTO PRA TERMINAR OS JOGOS AO FIM D X TEMPO TALVEZ
		}
		else if(res > 0 && FD_ISSET(0, &fds)){
			scanf("%s",cmd);
			printf("processar o cmd -> %s", cmd);
			
				if(strcmp(cmd, "exit")==0){
					termina = true;
				}
				else if(strcmp(cmd, "players")==0){
					mostraJogadores(clientes, max_player);

				}
				else if(strcmp(cmd, "games")==0){
					//lista jogos
				}
				else if(cmd[0]=='k'){
					memmove(cmd, cmd+1, strlen(cmd));
					kickPlayer(clientes, cmd, max_player);
				}

		}
		else if(res>0 && FD_ISSET(fd, &fds)){
			
			//comunicaçoes
				
				num = read(fd, &c, sizeof(cli));
		
				if(num == sizeof(cli)){
					if(c.aceite == -1){
						addUser(&c, clientes, &nPlayers, max_player);
					}else{
						interpretaCmdUser(c.res);
					}
						
						
					sprintf(fifo, FIFO_CLI, c.pid); //poder saber a quem responder
					fdr = open(fifo, O_WRONLY);
			
					num = write(fdr, &c, sizeof(cli));
					close(fdr);
				}
		}		
		
	}while(termina != true);
	
	close(fd);
	unlink(FIFO_SRV);
	
	exit(5);
	
	

	
}
