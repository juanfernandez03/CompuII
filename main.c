
#include "http_worker.h"

int main(int argc, char * const *argv){
	socklen_t addrlen;
	struct sockaddr_in cli_addr;
	int sd, sd_conn;
	//int opt = 1, optlen = sizeof(opt); 
	int opcion = 4;
	int protocolo = 0;
		while ((opcion = getopt (argc, argv, "46")) >= 0){
		switch (opcion){
	
			case '4': // protocolo ipv4
				if (protocolo != 0){
					protocolo = -1;
				}
				else {
					protocolo = 4;
				}
				break;

			case '6': // protocolo ipv6
				if (protocolo != 0){
					protocolo = -1;
				}
				else {
					protocolo = 6;
				}
				break;
			
		} // cierre switch
	}
	printf("ip: %d \n",protocolo);
		switch (protocolo){
		case 0:
			sd = ipv4();
			break;
		case 4:
			sd = ipv4();
			break;
		case 6:
			sd = ipv6();
			break;
	} 
	listen(sd,CONCUR); 		//"n" incoming connections 
	signal(SIGCHLD,SIG_IGN);
	//char *ejemplo = "Chauuu";
	//int error;		
	//pthread_t idHilo;						
	while( (sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
		switch (fork()) {
			case 0: // hijo
				http_worker(sd_conn, (struct sockaddr *) &cli_addr);
				return 0;
			case -1: // error
				break;
			default: // padre
			/*	error = pthread_create (&idHilo, NULL, logWrite,(void*) ejemplo);


				if (error != 0)
				{
					perror ("No puedo crear thread");
					exit (-1);
				}
*/
				break;
		}
		close(sd_conn);
	}
	close(sd);
	perror("acept ()");
	return 0;
}
