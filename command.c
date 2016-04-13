
#include "http_worker.h"

char *command(char * pedido)
{
	//printf("pedido en command %s\n",pedido);
	char *p = NULL;
	if(strncmp("www/cpuInfo",pedido,strlen(pedido)) == 0)
		p = "cat /proc/cpuinfo";
	else
		p = "lspci";
		/*
	switch (pedido) 
			{		   
			   	case 'www/cpuInfo': 
						p = "cat /proc/cpuinfo";
						break;
				case 'www/pciInfo': 
						p = "lspci";
				default: 
				break;
			}
			*/
 	//int fd;
	FILE *in;
	//extern FILE *open();//usar open
	char buff[1024];
	char buff2[1024];

    //ssize_t ret_in, ret_out;

	//fd = open("lspci", O_RDONLY); //lscpu
	//fd = open("/usr/bin/lspci", O_RDONLY);
	//fd2 = open("/home/jpfernandez/Escritorio/Compu/www/log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0700);

	//if(fd < 0)
	//
	 	//printf("error fd \n" );
	 	//perror ("open");
      //return 2;
	//}

	//while((ret_in = read (fd, &buff,sizeof(buff))) > 0){
	//ret_out = write (fd2, &buff, ret_in);
            //if(ret_out != ret_in){
                /* Write error */
               // perror("write");
                //return 4;
            //}
	//printf("buff command %s", &buff);
	//strcat(buff2,buff);
	//strcat(buff2,"<li>");//utilizar <li>  usar write lo 
	//}
	

	if(!(in = popen(p, "r"))){
 	printf("Fallo popen \n" );
	}

	while(fgets(buff, sizeof(buff), in)!=NULL){

		//printf("buff command %s", buff);
		strcat(buff2,buff);
		strcat(buff2,"<li>");//utilizar <li>
	}
	pclose(in);

 return buff2;
}


