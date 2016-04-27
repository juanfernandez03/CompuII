
#include "http_worker.h"

int main(int argc, char * const *argv){
	socklen_t addrlen;
	struct sockaddr_in cli_addr;
	int sd, sd_conn;
	int opcion = 4;
	int protocolo = 0;
	char ipAddress[INET_ADDRSTRLEN];
	key_t Clave1;
	int idCola;
	mensa Un_Mensaje;
	initMemory();
	initRam();
	Req buf;
	int n;
	mqd_t msjcola = mq_open ("/home", O_CREAT | O_RDWR, 0666, NULL);
	int prioridad = 1;
	char buffer[200];
	strncat(buffer,"holaaa",strlen("holaaa"));
	//mqd_t handle = mq_open ("/home/jpfernandez/Escritorio/Compu/www/", O_CREAT | O_RDONLY, 0, &buf);
	n = mq_send (msjcola, buffer, strlen(buffer), prioridad);

	if(n<0)
	{
	         perror("mq_send");

	printf("mensaje error");
	}
	else
	printf("se envio %s \n",buffer);

	
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
	listen(sd,CONCUR); 		//"n" incoming connections 
	signal(SIGCHLD,SIG_IGN);
	hilo(ipAddress);			
	Clave1 = ftok ("/bin/ls", 30);
	if (Clave1 == (key_t)-1)
	{
		printf("Error al obtener clave para cola mensajes");	
		return -1;			
	}		
	idCola = msgget (Clave1, 0600 | IPC_CREAT);

	if (idCola == -1)
	{
		printf("Error al obtener identificar para la cola de mensajes");		
		return -1;					
	}
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
			Un_Mensaje.Id_Mensaje = 1;             
			strcpy (Un_Mensaje.Mensaje, ipAddress);             
			msgsnd (idCola, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Mensaje),IPC_NOWAIT);

				break;
		}
		close(sd_conn);
	}
	close(sd);
	perror("acept ()");
	return 0;
}


