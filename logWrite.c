#include "http_worker.h"

void *logWrite (void *parametro)
{
  	
    char *log = " es la nueva ip que se conecto \n";
    char logCom[41] = {0}; //(char*)parametro;
	printf("Hola soy el hiloo, ip %s \n",logCom);
    int input_fd;    /* Input and output file descriptors */

    input_fd = open ("/home/jpfernandez/Escritorio/Compu/www/log.txt",  O_WRONLY | O_APPEND);
    if (input_fd == -1) {
      perror ("open");
    }

    strcat(logCom,(char*)parametro);
    strcat(logCom,log);
     if((write (input_fd,logCom, strlen(logCom))) < 0){
        perror("ultimo write");
     }

    close (input_fd);

	return 0;
}
