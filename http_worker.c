
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "http_worker.h"
#include "func.h"



void http_worker(int sd_conn, void *addr){
	char buf[4096]={0}, buf_arch[4096]={0}, buf_arch2[4096]={0}, arch_pedido[256]={0},value[256]={0};
	char out_msj[1024]={0},login[256]={0},index[256]={0},pedido[256]={0}, metodo[256]={0},userTmp[256]={0},passTmp[256]={0},url[256]={0};		
	int n,n2,fd_arch,fd_arch2,chk=0;
	int sd_conn2 = sd_conn;
	char *resp = NULL;
	int flag = 0;
	char *prueba = NULL;

	read (sd_conn, buf,sizeof buf);
	arch_pedido[255]=0;
	sscanf(buf, "%s /%s" ,metodo,arch_pedido);	//lee de buf con el formato indicado
	//printf("buf: %s\n",buf);
	strncpy(pedido,d_con.ROOT,strlen(d_con.ROOT));	
	strcat(pedido, arch_pedido);			//completo la ruta del archivo pedido
	printf("sd_conn: %d \t pedido:%s \n",sd_conn,pedido);
	printf("Metodo: %s\n",metodo);
	if((strncmp("GET",metodo,3)==0)){

		

		FILE *fpr;
		fpr = fopen("/home/jpfernandez/Escritorio/Compu/www/log.txt", "r");
	   	fscanf(fpr, "%s", value);
		v = "true";
		if((strncmp(value,"true",strlen("true"))!=0))
		{
				fclose(fpr);
		printf("login\n");
		strncpy(login,d_con.ROOT,strlen(d_con.ROOT));
		char init[256] = "login.html";	
		strcat(login,init);	
			if((fd_arch=open(login,O_RDONLY,0666))!=-1)
			{
				strcpy(out_msj,OK_HTML);
				write(sd_conn,out_msj, strlen(out_msj));
				while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0)
				{
				write(sd_conn,buf_arch,n);
				}
			}

		
		sscanf(pedido, "%*[^=]%*c%[^&]%*[^=]%*c%[^&]",userTmp,passTmp);

		//printf("u %s\n",userTmp);
		//printf("define user %s\n",USER);
		//printf("u2 %s\n",passTmp);
		//printf("define pass %s\n",PASS);
		//printf("Pedido %s\n",pedido);
		}

	
		if((strncmp(userTmp,USER,strlen(USER))==0) && (strncmp(passTmp,PASS,strlen(PASS))==0))
		{	
		FILE *fpw;
		fpw = fopen("/home/jpfernandez/Escritorio/Compu/www/log.txt", "w+");
		fprintf(fpw, "true\n");

   		fclose(fpw);
			printf("LOGEO BIEN\n");
			flag = 1;

					printf("flag %d\n",flag);
			strncpy(index,d_con.ROOT,strlen(d_con.ROOT));
			char loginTrue[256] = "index.html";	
			strcat(index,loginTrue);	
			if((fd_arch2=open(index,O_RDONLY,0666))!=-1)
			{

			//strcpy(out_msj,OK_HTML);
			//write(sd_conn2,out_msj, strlen(out_msj));
				while((n2=read(fd_arch2,buf_arch2, sizeof buf_arch2))>0)
				{
				write(sd_conn2,buf_arch2,n2);
				}
			}
			resp = command(pedido);
			///printf("respuesta %s\n",resp);
			strcpy(out_msj,MESS_404);
			write(sd_conn,out_msj, strlen(out_msj));
		}
		
		
		
		else
		{
		
			printf("LOGEO MAL\n");
		}

		if((strncmp(value,"true",strlen("true"))==0))
		{
				sscanf(pedido, "%*[^/]%*c%[^&]",url);
				printf("pedido abajo %s\n",url);
				if(pedido == "www/test.html")
				{
					prueba ="<html><body><h1>FILE NOT FOUND</h1></body></html>";
					printf("entroo");
				}
		}	

			
		

	if((fd_arch=open(pedido,O_RDONLY,0666))==-1)
	{

			//if(pedido == ""){
			//strcpy(out_msj,NOTOK_404);
			//write(sd_conn,out_msj, strlen(out_msj));
			//strcpy(out_msj,MESS_404);
			//write(sd_conn,out_msj, strlen(out_msj));

	}
		else{

			if ((strstr(arch_pedido,".jpeg"))!=NULL){
				strcpy(out_msj,OK_JPEG);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".html"))!=NULL){
				strcpy(out_msj,OK_HTML);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".txt"))!=NULL){
				strcpy(out_msj,OK_TXT);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".pdf"))!=NULL){
				strcpy(out_msj,OK_PDF);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if(chk==1){
				while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0){
					write(sd_conn,buf_arch,n);
				}
			}else{
				strcpy(out_msj,NOTOK_500);
				write(sd_conn,out_msj, strlen(out_msj));
				strcpy(out_msj,MESS_500);
				write(sd_conn,out_msj, strlen(out_msj));
			}
		close (fd_arch);
		}
	}else{


	strncpy(index,d_con.ROOT,strlen(d_con.ROOT));	
	strcat(pedido,"index.html");
	if((fd_arch=open(index,O_RDONLY,0666))==-1){
	strcpy(out_msj,OK_HTML);
	write(sd_conn,out_msj, strlen(out_msj));

	while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0){
					write(sd_conn,buf_arch,n);
					}
	}
			close (fd_arch);
		//strcpy(out_msj,NOTOK_501);
		//write(sd_conn,out_msj, strlen(out_msj));
		//strcpy(out_msj,MESS_501);
		//write(sd_conn,out_msj, strlen(out_msj));
		
	}

	close (sd_conn);
}
