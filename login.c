#include "http_worker.h"
#include "func.h"

char *InitLogin(char *userTmp,char *passTmp)
{
	char userPass[1024] = {0};
	int pid = getpid (); 
	int n;
	mqd_t msjcola = mq_open (COLAMSJ2, O_CREAT | O_RDWR, 0666, NULL);
	mqd_t  msjvuelta = mq_open (COLAMSJ3, O_RDWR, 0666, NULL);
	int prioridad = 1;
	unsigned int pri = 1;
	Req buf;
	Req buf2;
	strcat(userPass,userTmp);
	strcat(userPass,"|");
	strcat(userPass,passTmp);
	strncpy(buf2.data,userPass,strlen(userPass));
	buf2.pid = pid;
	n = mq_send (msjcola, (const char *) &buf2, sizeof(buf2), prioridad);
	if(n<0)
	{
		perror("mq_send");
      return "error";
	}
	int i = 0;
	/*if((mq_receive (msjvuelta, (char *) &buf, atributos.mq_msgsize, &pri))<0)
	{
		perror("mq_receive");
		return -1;					
	}*/
	if ((mq_receive (msjvuelta, (char *) &buf, atributos.mq_msgsize, &pri)) > 0)
	{
		while(pid != buf.pid)
		{
			printf("VOLVIO DEL LOGIN: %s  \n",buf.data);   
			printf("VOLVIO DEL LOGIN pid: %d  \n",buf.pid);     
			i++;
			printf("Pd: %d \n",pid);                         
			mq_send (msjvuelta, (const char *) &buf, sizeof(buf), prioridad);
	if(n<0)
			if(i>10)
			return "false";  
		}                        
	}       

return buf.data;
}
