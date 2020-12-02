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
	
	printf("asdasdad3");

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
	
	

	printf("asdasdad4");

	cli m;
	char nome[50];
	printf("asdasdad5");
		fs_in = open(PIPE_SERVER, O_RDONLY);
		r=read(fs_in,nome,sizeof(char)*50);
			printf("O jogador %s acabou de se juntar",nome);	
	close(fs_in);
	//printf("diretorio dos jogos: %s\nnumero maxino de jogadores: %d\nduracao do campeonato: %d\ntempo de espera: %d\n", game_dir, max_player,duracao_camp,tempo_espera);
	
	unlink(PIPE_SERVER);
	
}
