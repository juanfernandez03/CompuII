#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <netdb.h>
//#include "func.h"

int main()
{
/*
	char *argv[3] = {"Command-line", ".", NULL};//-v en el segundo -k para lspci
	int fd = open("/home/jpfernandez/Escritorio/Compu/www/ram.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0) {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    close(STDOUT_FILENO);   
    dup2(fd, STDOUT_FILENO);
	pid_t pid = fork();
	if(pid==0)
	{
		execvp( "free", argv );//lsusb lspci df(estado del disco) free (ram)
	}			
	*/
	char *argv[3] = {"Command-line", ".", NULL};//-v en el segundo -k para lspci  
    int fd2 = open("/home/jpfernandez/Escritorio/Compu/www/memory.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd2 < 0) {
        perror("open()");
        exit(EXIT_FAILURE);
    }   
    close(STDOUT_FILENO);
    dup2(fd2, STDOUT_FILENO);
	pid_t pid2 = fork();
	if(pid2==0)
	{
		execvp( "df", argv );//lsusb lspci df(estado del disco) free (ram)
	}
	
}
