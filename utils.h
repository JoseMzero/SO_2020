#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <stdbool.h>

#define GAME_DIR "jogos"
#define MAX_PLAYER 30
#define FIFO_CLI "fifo_%d"
#define FIFO_SRV "fifo_server"

typedef struct {
	char nome[50];
	char res[50];
	char nomeJogo[50];
	int pontos;
	int pid;
	int aceite;
}cli, pCli;

typedef struct{
		char resposta[100];
	
}msg,pMsg;

#endif
