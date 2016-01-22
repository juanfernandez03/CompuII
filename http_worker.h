#ifndef _HTTP_WORKER_H
	#define _HTTP_WORKER_H_

	#define CONCUR 10
	#define BUF_SIZE 1024

	typedef struct DATOS{
		int PORT ;
		char ROOT[256];
	} datos; 
	
	void http_worker(int sd_conn,void *addr);
	int largo(char * arch_pedido);
	datos d_con;

#endif
