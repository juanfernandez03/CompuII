#include "http_worker.h"
#include "func.h"

char *InitLogin(char *userTmp,char *passTmp)
{
	char userPass[1024] = {0};
	key_t Clave1;
	int Id_Cola_Mensajes;
	msj Un_Mensaje;
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
		return -1;			
	}			
	strcat(userPass,userTmp);
	strcat(userPass,"|");
	strcat(userPass,passTmp);						
	Un_Mensaje.Id_Mensaje = 1;  
	Un_Mensaje.Pid = pid;   
	strcpy (Un_Mensaje.Mensaje, userPass);    

	msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje),IPC_NOWAIT);
	msgrcv (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje),2, 0);
	
	if(pid != Un_Mensaje.Pid)	
	{
				printf("Pd: %d \n",pid);                         
		//Un_Mensaje.Id_Mensaje = 2;
		printf("En el while mensaje: %d \n",Un_Mensaje.Pid);              
		//msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Pid)+sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT);		        
	}

	printf("paso el while mensaje: %s \n",Un_Mensaje.Mensaje);              

return Un_Mensaje.Mensaje;
}
