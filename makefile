all: 
	gcc -c arbito.c
	gcc utils.h arbito.c -o arbito
	gcc -c cliente.c
	gcc utils.h cliente.c -o cliente
	gcc -c jogos/G_001.c
	gcc jogos/G_001.c -o jogos/G_001

arbito : 
	gcc -c arbito.c
	gcc utils.h arbito.c -o arbito

cliente : 
	gcc -c cliente.c
	gcc utils.h cliente.c -o cliente

jogo1 : 
	gcc -c $GAMEDIR/G_001.c
	gcc jogos/G_001.c -o jogos/G_001
	
clean:
	$(RM) arbito arbito.o
	$(RM) cliente cliente.o
	$(RM) jogos/G_001 jogos/G_001.o
