#include "http_worker.h"

void hilo(char *ip){
	//char *ejemplo = "Chauuu";
	printf("la ip en el hilo %s \n",ip);
	int error;		
	pthread_t idHilo;
	error = pthread_create (&idHilo, NULL, logWrite,(void*) ip);
	if (error != 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}						
}
