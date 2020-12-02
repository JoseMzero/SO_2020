#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

#define GAME_DIR "jogos"
#define MAX_PLAYER 30

typedef struct {
	char nome[50];
	int pontos;
	int pid;
}cli, pCli;

#endif // !ARBITO_H
