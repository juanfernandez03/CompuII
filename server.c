#include "header.h"


int main(){

const int PORT = 7200;
//char * advide[] = {"Open socket"};
//---variables para leer envio
int leido;
char buffer[8000];
bzero(buffer,8000);
char tipo[256];
char archivo[256];
char *parse = malloc(256*sizeof(char));
//-----------Fork
char *nombre = malloc(256*sizeof(char));
pid_t getpid ( void );
pid_t getppid ( void );
//---------
int listener = openSocket();

if(listener == -1){
printf ("Error en listener \n");
return -1;
}
bindToPort(listener,PORT);
if(listen(listener,10) == -1){ // el 10 es el maximo numero de cliente despues cambiar
printf ("Ocupado \n");
return -1;
}
printf ("Conectado al puerto %d \n",PORT);
while(1){
	struct sockaddr_storage client;
	unsigned int addres_size = sizeof(client);
	printf ("Esperando al cliente \n");
	int connect = accept(listener,(struct sockaddr*)&client,&addres_size);
	if(connect == -1)
			{
				printf("No se puede conectar socket \n");
			}
		
				
				printf("Atendiendo al cliente \n");
			char* msg = "Hola \n";
int tam = strlen(msg);
switch(fork()){
				
			case -1:	// error fork
				perror("Error en la creacion de fork\n");
				return -1;			
				break;
			case 0:
				printf (" Va a ser atendido por el proceso hijo: PID %d\ n" , getpid () );
				nombre = hijo(connect);
				printf("Volvio del hijo %s \n",nombre);
				break;	
		}

	send(connect,msg,tam,0);					
	close(connect);
	}
return 0;
}

//void hijo(int con,char* m,int cant){
//			send(con,m,cant,0);
//}
 
int openSocket(){
	int s = socket(PF_INET,SOCK_STREAM,0);
	if(s == -1)
	printf("Error al abrir el socket \n");
	return s;
}

char *hijo(int connct){

	//---variables para leer envio
	int leido;
	char buffer[8000];
	bzero(buffer,8000);
	char tipo[256];
	char archivo[256];
	char *parse = malloc(256*sizeof(char));

		if ((leido = read(connct, buffer, sizeof(buffer))) > 0){
				printf("Entro al if \n");
			memset(tipo, 0, sizeof tipo);
			memset(archivo, 0, sizeof archivo);
		}
	execl("/bin/ls", "ls", "-l", (char *)0);
	parse = strtok( buffer, "/" ); 
	parse = strtok( NULL, " " ); 
	//buf = strtok( NULL, " " ); 
	printf("Buffer %s \n",parse);
return parse;
}


void bindToPort(int socket,int port){
struct sockaddr_in name;

name.sin_family = PF_INET;
name.sin_port = (in_port_t)htons(port);
name.sin_addr.s_addr = htonl(INADDR_ANY);
int reuse = 1;
printf("IP address is: %s\n", inet_ntoa(name.sin_addr));

if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) == -1){
	perror("No es posible reusar el socket");
}
int c = bind(socket,(struct sockaddr*)&name,sizeof(name));
	if (c == -1)
		{
		perror("No se puede enlazar al puerto : dirrecion ya esta en uso \n");
		}
}
