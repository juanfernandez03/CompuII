#include "http_worker.h"

int ipvDefault(){
/*
		int sd;
		int opt = 1, optlen = sizeof(opt);
		struct sockaddr_in srv_addr;
		strncpy(d_con.ROOT,"www/",4);			
		printf("Mi directorio ROOOT es y el protocolo ipv4: %s\n",d_con.ROOT);
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
		*/
		   struct addrinfo hints;
           struct addrinfo *result, *rp;
           int sfd, s;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[500];

        

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           //hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */
           hints.ai_canonname = NULL;
           hints.ai_addr = NULL;
           hints.ai_next = NULL;

           s = getaddrinfo(NULL,d_con.ROOT, &hints, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */

               close(sfd);
           }
		
	return sfd;
}
