#ifndef _HTTP_WORKER_H
	#define _HTTP_WORKER_H_

	#define CONCUR 10
	#define BUF_SIZE 1024
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
	typedef struct DATOS{
		int PORT ;
		char ROOT[256];
	} datos; 

	typedef struct Mi_Tipo_Mensaje
	{
		long Id_Mensaje;
		char Mensaje[100];
	} msj;

	
	void http_worker(int sd_conn,void *addr);
	char *command(char *com);
	void *logWrite(void *ip);
	int ipv4();
	int ipv6();
	int largo(char * arch_pedido);
	datos d_con;
	
#endif
