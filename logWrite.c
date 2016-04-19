#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include "http_worker.h"

void *logWrite (void *parametro)
{
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
	char *log = " es la nueva ip que se conecto \n";
    char logCom[41] = {0}; //(char*)parametro;
    int input_fd;    /* Input and output file descriptors */
    input_fd = open ("/home/jpfernandez/Escritorio/Compu/www/log.txt",  O_WRONLY | O_APPEND);
    if (input_fd == -1) {
		perror ("open");
		exit(0);
    }
    strcat(logCom,Un_Mensaje.Mensaje);
    strcat(logCom,log);
    printf("Hola soy el hiloo, ip %s \n",logCom);
     if((write (input_fd,logCom, strlen(logCom))) < 0){
        perror("ultimo write");
     }
    close (input_fd);
	}
	   
	return 0;
}
