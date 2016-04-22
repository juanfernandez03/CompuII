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
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <netdb.h>


	typedef struct DATOS{
		int PORT ;
		char ROOT[256];
	} datos; 

	typedef struct Mi_Tipo_Mensaje
	{
		long Id_Mensaje;
				int Pid;
		char Mensaje[100];
	} msj;
	typedef struct Mensaje
	{
		long Id_Mensaje;
		char Mensaje[100];
	} mensa;
	
	void http_worker(int sd_conn,void *addr);
	char *command(char *com);
	void *logWrite(void *ip);
	int ipv4();
	int ipv6();
	void hilo(char *ip);
	int largo(char * arch_pedido);
	char *InitLogin(char *user,char *pass);
	int initMemory();
	datos d_con;
	
#endif
