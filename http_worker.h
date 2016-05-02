#ifndef _HTTP_WORKER_H
	#define _HTTP_WORKER_H_

	#define CONCUR 10
	#define BUF_SIZE 1024
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
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
#include <time.h>
#include <mqueue.h>
#include <sys/mman.h>


	struct mq_attr atributos;
	typedef struct DATOS{
		int PORT ;
		char ROOT[256];
	} datos; 

	typedef struct Req
	{
	  int pid;
	  char data[4096];
	} Req;

	
	void http_worker(int sd_conn,void *addr);
	char *command(char *com);
	void *logWrite(void *ip);
	int ipv4();
	int ipv6();
	void hilo(char *ip);
	int largo(char * arch_pedido);
	char *InitLogin(char *user,char *pass);
	void initRam();
	void initMemory();
	int ipvDefault();
	void response(int sd_conn,int tarea);
	datos d_con;
	
#endif
