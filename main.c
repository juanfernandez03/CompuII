
#include "http_worker.h"

int main(int argc, char * const *argv){
	socklen_t addrlen;
	struct sockaddr_in cli_addr;
	int sd, sd_conn;
	//int opt = 1, optlen = sizeof(opt); 
	int opcion = 4;
	int protocolo = 0;
	char ipAddress[INET_ADDRSTRLEN];
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
	

	while( (sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
		switch (fork()) {
			case 0: // hijo
				http_worker(sd_conn, (struct sockaddr *) &cli_addr);
				return 0;
			case -1: // error
				break;
			default: // padre	
			//jode el favicon pasa 2 veces
			switch(protocolo) {
				case 4: {
					inet_ntop(AF_INET, &(cli_addr.sin_addr), ipAddress, INET_ADDRSTRLEN);
					break;
				}
				case 6: {
					inet_ntop(AF_INET6, &(cli_addr.sin_addr), ipAddress, INET_ADDRSTRLEN);
					break;
				}
				default:
					inet_ntop(AF_INET, &(cli_addr.sin_addr), ipAddress, INET_ADDRSTRLEN);
					break;
			}
			
			//inet_ntop(AF_INET, &(cli_addr.sin_addr), ipAddress, INET_ADDRSTRLEN);
			//char *ip = inet_ntoa((struct in_addr) cli_addr.sin_addr);
			hilo(ipAddress);			
				break;
		}
		close(sd_conn);
	}
	close(sd);
	perror("acept ()");
	return 0;
}


