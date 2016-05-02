#include "http_worker.h"
#include "func.h"
int ipvDefault(){
  struct addrinfo hints, *servinfo, *p;
  int sockfd;  
  int rv;
  memset (&hints, 0, sizeof (hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP address
  //hints.ai_flags |= AI_CANONNAME;
  
	  if ((rv = getaddrinfo(NULL,PUERTO, &hints, &servinfo)) != 0) {
		perror("getaddrinfo");
		return -1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
		        p->ai_protocol)) == -1) {
		    perror("socket");
		    continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
		    close(sockfd);
		    perror("bind");
		    continue;
		}

		break; // if we get here, we must have connected successfully
	}

	if (p == NULL) {
		// looped off the end of the list with no successful bind
		printf( "failed to bind socket\n");
		return -1;
	}
printf("socket default %d \n",sockfd);
freeaddrinfo(servinfo);
  /*
  
  printf("Ruta %s \n",d_con.ROOT);
  errcode = getaddrinfo (NULL, "3490", &hints, &res);
  if (errcode != 0)
    {
    printf("Error en el  getaddrinfo");
      perror ("getaddrinfo");
      return -1;
    }


  while (res)
    {
      inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100);

      switch (res->ai_family)
        {
        case AF_INET:
          ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
          sd = ipv4();
          break;
        case AF_INET6:
          ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
          sd = ipv6();
          break;
        }
      inet_ntop (res->ai_family, ptr, addrstr, 100);
      printf ("IPv%d direccion: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
              addrstr, res->ai_canonname);
      res = res->ai_next;
      freeaddrinfo(res);

    }
*/
  return sockfd;
		

}
