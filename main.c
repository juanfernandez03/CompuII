#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "http_worker.h"

int main(int argc, char * const *argv){
	int sd, sd_conn,opc=0;
	int opt = 1, optlen = sizeof(opt); 
	socklen_t addrlen;
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	//printf("argc %c \n",argc);
	//printf("argv %c \n",argv[2]);
    /* TODO: agregar creación y configuración del socket */
	if((opc=getopt(argc,argv,"d:"))!=0 && argc==3){
		strncpy(d_con.ROOT,argv[2],strlen(argv[2]));			
	}else{	
		strncpy(d_con.ROOT,"www/",4);			
	}
	printf("Mi directorio ROOOT es: %s\n",d_con.ROOT);
	d_con.PORT=8081;	
	
	sd = socket(PF_INET, SOCK_STREAM,0);		 //creo el socket
	setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&opt,optlen); //to avoid "Address already in use"(EADDRINUSE)
	
	memset (&srv_addr,0,sizeof (struct sockaddr_in));//vacio la  struct
	srv_addr.sin_family=AF_INET;		
	srv_addr.sin_port=htons(d_con.PORT);		
	inet_pton(AF_INET,"127.0.0.1" , &srv_addr.sin_addr.s_addr);

	//bindeo el socket a una direccion
	if(bind (sd,(struct sockaddr *)&srv_addr, sizeof srv_addr)==-1){
		perror("bind ()");
		exit (EXIT_FAILURE);
	}
	listen(sd,CONCUR); 		//"n" incoming connections (backlog)
	signal(SIGCHLD,SIG_IGN);

	while( (sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
		switch (fork()) {
			case 0: // hijo
				http_worker(sd_conn, (struct sockaddr *) &cli_addr);
				return 0;
			case -1: // error
				break;
			default: // padre
				break;
		}
		close(sd_conn);
	}
	close(sd);
	perror("acept ()");
	return 0;
}
