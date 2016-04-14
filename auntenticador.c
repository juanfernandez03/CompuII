
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
int vericador(char *up);

typedef struct Mi_Tipo_Mensaje
	{
		long Id_Mensaje;
		char Mensaje[100];
	} msj;
main()
{
	key_t Clave1;
	int Id_Cola_Mensajes;
	msj Un_Mensaje;
	
	int result = 0;
	char *r = NULL;

	printf("hola estoy en el autenticador \n");

	Clave1 = ftok ("/bin/ls", 33);
	if (Clave1 == (key_t)-1)
	{
		printf("Error al obtener clave para cola mensajes");
	}
	
	Id_Cola_Mensajes = msgget (Clave1, 0600 | IPC_CREAT);
	if (Id_Cola_Mensajes == -1)
	{
		printf("Error al obtener identificador para cola mensajes");		
	}
	
	while(msgrcv (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Mensaje),1, 0) > 0)
	{	
		result = verificador(Un_Mensaje.Mensaje);
		if(result == 1)
			r = "true";
		else
			r = "false";
		Un_Mensaje.Id_Mensaje = 2;	
		strcpy (Un_Mensaje.Mensaje,r);
		msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT);
	}

	msgctl (Id_Cola_Mensajes, IPC_RMID, (struct msqid_ds *)NULL);

}

int verificador(char * up)
{
int fd;
int re = 0;
ssize_t ret_in;
char buff[1024];
   char *token;

	fd = open("/home/jpfernandez/Escritorio/Compu/www/user.txt", O_RDONLY);
	if(fd < 0)
	{
	 	printf("error fd \n" );
	 	perror ("open");
      //return 2;
      }
while((ret_in = read (fd, buff,sizeof(buff))) > 0)
	{
		int i = 0;
		printf("i %d \n",i);
		i++;
    	printf("up %s y buff %s \n",up,buff);
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
