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

int main(int argc, char** argv) {

	printf("asdasdad1");
	char game_dir[50];
	int max_player, duracao_camp,tempo_espera,fs_in,fs_out,r;

	
	printf("asdasdad2");
	//verificar se ja existe algum server a correr
	if (access(PIPE_SERVER, F_OK) != 0)
		mkfifo(PIPE_SERVER, 0600);
	else {
		fprintf(stderr, "ERRO Ja existe um servidor a funcionar!\n");
		exit(1);
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
	
	/*########################################## USER COMANDOS ##########################################*/
	
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
					}
						
					interpretaCmdUser(c.res);
						
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
