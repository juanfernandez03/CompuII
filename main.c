
#include "http_worker.h"
#include "func.h"
int main(int argc, char * const *argv){
	struct sockaddr_in cli_addr;
	socklen_t addrlen = sizeof cli_addr;
	int sd, sd_conn;
	int opcion = 4;
	int protocolo = 0;
	char ipAddress[INET_ADDRSTRLEN];

	

	int n;
	mqd_t msjcola = mq_open (COLAMSJ, O_CREAT | O_RDWR, 0666, NULL);
	int prioridad = 1;
	char buffer[200];
	

	
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
			sd = ipvDefault();
			break;
		case 4:
			sd = ipv4();
			break;
		case 6:
			sd = ipv6();
			break;
	} 
	printf("sd %d \n",sd);
	if (listen(sd,CONCUR) < 0){
	perror("Error en listen (getaddrinfo)");
	return -1;
	}
	signal(SIGCHLD,SIG_IGN);
	hilo(ipAddress);			
	
	while( (sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
		switch (fork()) {
			case 0: // hijo
				initMemory();
				initRam();
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
			
			strncpy(buffer,ipAddress,strlen(ipAddress));
			n = mq_send (msjcola, buffer, strlen(buffer), prioridad);

			if(n<0)
			{
				perror("mq_send");
				return -1;					
			}
			else
				printf("se envio %s \n",buffer);
				break;
		}
		close(sd_conn);
	}
	close(sd);
	perror("accept");
	return 0;
}


