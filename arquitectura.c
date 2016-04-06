#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[] )
{

 FILE *fp;
 int estado;
 char ruta[1035];

 /* Abrir el comando de lectura. */
 fp = popen("lspci", "r");
 if (fp == NULL) {
 printf("Error al ejecutar el comando\n" );

}

 /* Leer la salida en una línea a la hora de salida. */
 while (fgets(ruta, sizeof("/home/jpfernandez/Escritorio/Compu")-1, fp) != NULL) {
 printf("%s", ruta);
}

 /* cerrar */
pclose(fp);

 return 0;
}
