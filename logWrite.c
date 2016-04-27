#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include "http_worker.h"
#include "func.h"

void *logWrite (void *parametro)
{
	time_t curtime;

   	time(&curtime);

//	printf("Current time = %s", ctime(&curtime));
	key_t Clave1;
	int idCola;
	mensa Un_Mensaje;
	Clave1 = ftok ("/bin/ls", 30);
	if (Clave1 == (key_t)-1)
	{
		printf("Error al obtener clave para cola mensajes");
		exit(0);
	}	
	idCola = msgget (Clave1, 0600 | IPC_CREAT);
	if (idCola == -1)
	{
		printf("Error al obtener identificador para cola mensajes");
		exit(0);
	}
	while(msgrcv (idCola, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Mensaje),1, 0) > 0)
	{	
	char *log = (" es la nueva ip que se conecto a las ");
    char logCom[41] = {0}; //(char*)parametro;
    int input_fd;    /* Input and output file descriptors */
    input_fd = open (DIRLOG,  O_WRONLY | O_APPEND);
    if (input_fd == -1) {
		perror ("open");
		exit(0);
    }
    strncat(logCom,Un_Mensaje.Mensaje,strlen(Un_Mensaje.Mensaje));
    strncat(logCom,log,strlen(log));
    strncat(logCom,ctime(&curtime),strlen(ctime(&curtime)));
   strncat(logCom,"\n",strlen("\n"));
    //printf("Hola soy el hiloo, ip %s \n",logCom);
     if((write (input_fd,logCom, strlen(logCom))) < 0){
        perror("ultimo write");
     }
    close (input_fd);
	}
	   
	return 0;
}
