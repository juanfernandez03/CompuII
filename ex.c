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

int main()
{
	char *argv[3] = {"Command-line", ".", NULL};//-v en el segundo -k para lspci
	//char *prog[] = { "ls", NULL };
	int respuesta;
	int fd = open("/home/jpfernandez/Escritorio/Compu/www/t.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0) {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    close(STDOUT_FILENO);

    dup2(fd, STDOUT_FILENO);
	pid_t pid = fork();
	if(pid==0)
	{
		//execv("/home/jpfernandez/Escritorio/Compu",argv);
		respuesta=execvp( "free", argv );//lsusb lspci df(estado del disco) free (ram)
		//execvp("sh", "-c", "cd /tmp; pwd");
		printf("re :%d",respuesta);

	}
}
