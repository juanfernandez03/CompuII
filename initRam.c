#include "http_worker.h"
#include "func.h"

void initRam()
{

	char *argv[3] = {"Command-line", ".", NULL};//-v en el segundo -k para lspci  
    int fd = open(DIRRAM, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0) {
        perror("open()");
        exit(EXIT_FAILURE);
    }   


	pid_t pid = fork();
	if(pid==0)
	{	 close(STDOUT_FILENO);
	    dup2(fd, STDOUT_FILENO);

		if(execvp( "free", argv ) == -1)//lsusb lspci df(estado del disco) free (ram)
		_exit(EXIT_FAILURE);   // exec never returns

	}	
	 else
	{
	int status;
    waitpid(pid, &status, 0);
	close(fd);
	}
	
}
