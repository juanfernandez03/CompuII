
#include "http_worker.h"

void hilo(char *ip){

	int error;		
	pthread_t idHilo;
	error = pthread_create (&idHilo, NULL, logWrite,(void*) ip);
	if (error != 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}						
}
