#include "http_worker.h"

int ipv6 (){

		int sd;
		int opt = 1, optlen = sizeof(opt);
		struct sockaddr_in6 srv_addr;
		strncpy(d_con.ROOT,"www/",4);			
		printf("Mi directorio ROOOT es y el protocolo ipv6: %s\n",d_con.ROOT);
		d_con.PORT=8081;	
	
		sd = socket(AF_INET6, SOCK_STREAM,0);

		setsockopt(sd, IPPROTO_IPV6, IPV6_V6ONLY,&opt,optlen); 
	
		memset (&srv_addr,0,sizeof (struct sockaddr_in));//vacio la  struct
		srv_addr.sin6_family = AF_INET6;		
		srv_addr.sin6_port = htons(d_con.PORT);
		srv_addr.sin6_addr = in6addr_any;
		//inet_pton(AF_INET,"127.0.0.1" , &srv_addr.sin_addr.s_addr);	

		//bindeo el socket a una direccion
		if(bind (sd,(struct sockaddr *)&srv_addr, sizeof srv_addr)==-1){
			perror("bind ()");
			exit (EXIT_FAILURE);
		}
	return sd;
} // fin funcion
