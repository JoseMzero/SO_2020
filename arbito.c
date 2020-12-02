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

	char game_dir[50];
	int max_player, duracao_camp,tempo_espera;

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
	printf("diretorio dos jogos: %s\nnumero maxino de jogadores: %d\nduracao do campeonato: %d\ntempo de espera: %d\n", game_dir, max_player,duracao_camp,tempo_espera);
	
}