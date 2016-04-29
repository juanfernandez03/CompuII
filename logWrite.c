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
	char *buffer = NULL;
	mqd_t  msjcola = mq_open (COLAMSJ, O_RDWR, 0666, NULL);
	mq_getattr (msjcola, &atributos);
	buffer = malloc (atributos.mq_msgsize * sizeof (char));
	unsigned int prioridad= 1;
	
	time_t curtime;

   	time(&curtime);


	while ((mq_receive (msjcola, buffer, atributos.mq_msgsize, &prioridad)) > 0)
	{
		printf("se recibio %s \n",buffer);
		char *log = (" es la nueva ip COLA DE MENSAJE NUEVA que se conecto a las ");
		char logCom[41] = {0}; //(char*)parametro;
		int input_fd;    /* Input and output file descriptors */
		input_fd = open (DIRLOG,  O_WRONLY | O_APPEND);
		if (input_fd == -1) {
			perror ("open");
			exit(0);
		}
		strncat(logCom,buffer,strlen(buffer));
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
