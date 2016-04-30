#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include "func.h"
int vericador(char *up);
	struct mq_attr atributos; 

	typedef struct Req
	{
	  int pid;
	  char data[4096];
	} Req;
	int result = 0;
	char *r = NULL;
	char *buffer = NULL;

	mqd_t  msjcola = mq_open (COLAMSJ2, O_RDWR, 0666, NULL);
	mqd_t msjEnvio = mq_open (COLAMSJ3, O_CREAT | O_RDWR, 0666, NULL);
	mq_getattr (msjcola, &atributos);
	buffer = malloc (atributos.mq_msgsize * sizeof (char));
	unsigned int prioridad= 1;
	int pri = 1;
	int n;
	Req buf;
	Req buf2;
	//buf2 = malloc (atributos.mq_msgsize * sizeof (char));
	if((mq_receive (msjcola, (char *) &buf2, atributos.mq_msgsize, &prioridad)<0))      
	{
		perror("mq_receive");
	}
			printf("NUEVA COLA  \n");              
	while ((mq_receive (msjcola, (char *) &buf2, atributos.mq_msgsize, &prioridad)) > 0)
	{
		printf("NUEVA COLA En el while autenticador: %s  \n",buffer);              
		result = verificador(buffer);
		if(result == 1)
			r = "true";
		else
			r = "false";
			strncpy(buf.data,r,strlen(r));
			buf.pid = buf2.pid;
			n = mq_send (msjEnvio, (const char *) &buf, sizeof(buf), pri);
			
			if(n<0)
			{
				perror("mq_send");
				return -1;					
			}
			else
				printf("se envio resultado %s %d \n",buf.data,buf.pid);    
	}
}

int verificador(char * up)
{
int fd;
int re = 0;
ssize_t ret_in;
char buff[1024];
   char *token;

	fd = open(DIRUSER, O_RDONLY);
	if(fd < 0)
	{
	 	printf("error fd \n" );
	 	perror ("open");
      return;
      }
while((ret_in = read (fd, buff,sizeof(buff))) > 0)
	{
		int i = 0;

		i++;
    	printf("user y pass que llego %s  \n",up);
    	token =strtok(buff,"-");
    	 while( token != NULL ) 
   		{

			switch (strncmp(token,up,strlen(up))) 
			{		   
			   	case 0: 
						re = 1;
						break;
				case -1: 
						re = 0;
				default: 
				break;
			}
      	token = strtok(NULL, "-");
   		}	    	
		
    }
return re;
}

