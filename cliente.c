#include "utils.h"

int main(int argc, char** argv){

	cli jogador;
	printf("Introduza o seu nome:");
	scanf("%49[^\n]", jogador.nome);
	printf("Bem Vindo %s", jogador.nome);

}