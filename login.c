#include "http_worker.h"
#include "func.h"

char *InitLogin(char *userTmp,char *passTmp)
{
	char userPass[1024] = {0};
	/*
	 key_t Clave1;
	int Id_Cola_Mensajes;
	msj Un_Mensaje;
	int i = 0;
	printf("Antes de la cola de mensaje, : PID %d \n" , getpid ());
	int pid = getpid (); 
   	Clave1 = ftok ("/bin/ls", 33);
	if (Clave1 == (key_t)-1)
	{
		printf("Error al obtener clave para cola mensajes");
	}				
	Id_Cola_Mensajes = msgget (Clave1, 0600 | IPC_CREAT);
	if (Id_Cola_Mensajes == -1)
	{
		printf("Error al obtener identificar para la cola de mensajes");	
		exit(0);
	}			
							
	Un_Mensaje.Id_Mensaje = 1;  
	Un_Mensaje.Pid = pid;   
	strcpy (Un_Mensaje.Mensaje, userPass);    
	msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje),IPC_NOWAIT);
	msgrcv (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje),2, 0);
	while(pid != Un_Mensaje.Pid)	
	{
		i++;
		printf("Pd: %d \n",pid);                         
		Un_Mensaje.Id_Mensaje = 2;
		printf("En el while mensaje: %d \n",Un_Mensaje.Pid);              
		msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT);		  
		if(i>10)
		return "false";      
	}

	printf("paso el while mensaje: %s, pid %d  \n",Un_Mensaje.Mensaje,Un_Mensaje.Pid);   
	*/
	int n;
	mqd_t msjcola = mq_open (COLAMSJ2, O_CREAT | O_RDWR, 0666, NULL);
	mqd_t  msjvuelta = mq_open (COLAMSJ3, O_RDWR, 0666, NULL);
	int prioridad = 1;
	unsigned int pri = 1;
	char buffer[200];
	char volvio[200];
	strcat(userPass,userTmp);
	strcat(userPass,"|");
	strcat(userPass,passTmp);
	strncpy(buffer,userPass,strlen(userPass));
	n = mq_send (msjcola, buffer, strlen(buffer), prioridad);

	if(n<0)
	{
		perror("mq_send");
		return -1;					
	}
	else
		printf("se envio %s \n",buffer); 
	while ((mq_receive (msjvuelta, volvio, atributos.mq_msgsize, &pri)) > 0)
	{
		printf("VOLVIO DEL LOGIN: %s  \n",volvio);              
	}          

return buffer;
}
