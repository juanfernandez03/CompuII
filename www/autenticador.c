#include "http_worker.h"
#include <iostream.h>
#include <sys/msg.h>
#include <errno.h>


//
// Estructura para los mensajes que se quieren enviar y/o recibir. Deben llevar
// obligatoriamente como primer campo un long para indicar un identificador
// del mensaje. 
// Los siguientes campos son la información que se quiera transmitir en el  
// mensaje. Cuando más adelante, en el código, hagamos un cast a 
// (struct msgbuf *), todos los campos de datos los verá el sistema como
// un único (char *)
//

void auntenticador()
{
	key_t Clave1;

	Mi_Tipo_Mensaje Un_Mensaje;

	//
	// Igual que en cualquier recurso compartido (memoria compartida, semaforos 
	//  o colas) se obtien una clave a partir de un fichero existente cualquiera 
	//  y de un entero cualquiera. Todos los procesos que quieran compartir este
	//  semaforo, deben usar el mismo fichero y el mismo entero.
	//
	Clave1 = ftok ("/bin/ls", 33);
	if (Clave1 == (key_t)-1)
	{
		cout << "Error al obtener clave para cola mensajes" << endl;
		exit(-1);
	}

	//
	//	Se crea la cola de mensajes y se obtiene un identificador para ella.
	// El IPC_CREAT indica que cree la cola de mensajes si no lo está ya.
	// el 0600 son permisos de lectura y escritura para el usuario que lance
	// los procesos. Es importante el 0 delante para que se interprete en
	// octal.
	//
	Id_Cola_Mensajes = msgget (Clave1, 0600 | IPC_CREAT);
	if (Id_Cola_Mensajes == -1)
	{
		cout << "Error al obtener identificador para cola mensajes" << endl;
		exit (-1);
	}

	//
	//	Se recibe un mensaje del otro proceso. Los parámetros son:
	//	- Id de la cola de mensajes.
	//	- Dirección del sitio en el que queremos recibir el mensaje,
	//	convirtiéndolo en puntero a (struct msgbuf *).
	//	- Tamaño máximo de nuestros campos de datos. 
	//	- Identificador del tipo de mensaje que queremos recibir. En este caso
	//	se quiere un mensaje de tipo 1, que es el que envia el proceso cola1.cc
	//	- flags. En este caso se quiere que el programa quede bloqueado hasta
	//	que llegue un mensaje de tipo 1. Si se pone IPC_NOWAIT, se devolvería
	//	un error en caso de que no haya mensaje de tipo 1 y el programa
	//	continuaría ejecutándose.
	//
	msgrcv (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Mensaje),1, 0);

	cout << "Recibido mensaje tipo 1" << endl;

	cout << "Mensaje = " << Un_Mensaje.Mensaje << endl;

	//
	//	Se rellenan los campos del mensaje que se quiere enviar.
	//	El Id_Mensaje es un identificador del tipo de mensaje. Luego se podrá
	//	recoger aquellos mensajes de tipo 1, de tipo 2, etc.
	//	Dato_Numerico es un dato que se quiera pasar al otro proceso. Se pone, 
	//	por ejemplo 13.
	//	Mensaje es un texto que se quiera pasar al otro proceso.
	//
	Un_Mensaje.Id_Mensaje = 2;

	strcpy (Un_Mensaje.Mensaje, "Adios");

	//
	//	Se envia el mensaje. Los parámetros son:
	//	- Id de la cola de mensajes.
	//	- Dirección al mensaje, convirtiéndola en puntero a (struct msgbuf *)
	//	- Tamaño total de los campos de datos de nuestro mensaje, es decir
	//	de Dato_Numerico y de Mensaje
	//	- Unos flags. IPC_NOWAIT indica que si el mensaje no se puede enviar
	//	(habitualmente porque la cola de mensajes esta llena), que no espere
	//	y de un error. Si no se pone este flag, el programa queda bloqueado
	//	hasta que se pueda enviar el mensaje.
	//
	msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT);
}
