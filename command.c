#include "func.h"
#include "http_worker.h"

char *command(char * pedido)
{
	//printf("pedido en command %s\n",pedido);

	int fd = 0;
	if(strncmp("www/ram",pedido,strlen(pedido)) == 0)
	{
		printf("ram \n");
		fd = open(DIRRAM, O_RDONLY);	
	}
	else
	{
		printf("memory \n");
		fd = open(DIRMEMORY, O_RDONLY);	
	}	
	
	ssize_t ret_in;
	char buff[1024];
	char buff2[1024];
	if(fd < 0)
	{
	 	printf("error fd \n" );
	 	perror ("open");
      return "error";
      }
	while((ret_in = read (fd, buff,sizeof(buff))) > 0)
	{
		//printf("buff : %s \n",buff);
		strncat(buff2,buff,strlen(buff));

	}
			printf("buff2 : %s \n",buff2);

 return buff2;
}


