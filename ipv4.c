#include "http_worker.h"
#include "func.h"
int ipv4(){

		int sd;
		int opt = 1, optlen = sizeof(opt);
		struct sockaddr_in srv_addr;
		strncpy(d_con.ROOT,"www/",4);			
		printf("Mi directorio ROOT es y el protocolo ipv4: %s\n",d_con.ROOT);
		d_con.PORT=PUERTOI;	
	
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
	return sd;
}
