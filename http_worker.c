#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/msg.h>
#include <errno.h>
#include "http_worker.h"
#include "func.h"



void http_worker(int sd_conn, void *addr){
    
    char buf[4096]={0}, buf_arch[4096]={0}, buf_arch2[4096]={0}, arch_pedido[256]={0};
    
    char out_msj[1024]={0},out_msj2[1024]={0},login[256]={0},index[256]={0},pedido[256]={0}, metodo[256]={0},userTmp[256]={0},cookie[256]={0},passTmp[256]={0},url[256]={0};
    
    int n,n2,fd_arch,fd_arch2;
    
    int sd_conn2 = sd_conn;
    
    char *resp = NULL;
    
    char prueba[512] = {0};
    char userPass[1024] = {0};
	int i = 0;

	key_t Clave1;
	int Id_Cola_Mensajes;
	msj Un_Mensaje;
    
    char *lg = NULL;
    
    
    read (sd_conn, buf,sizeof buf);
    
    arch_pedido[255]=0;
    //printf("buf \n %s \n",buf);
    sscanf(buf, "%s /%s" ,metodo,arch_pedido);
    //lee de buf con el formato indicado
    //printf("buf: %sn",buf);
    
    strncpy(pedido,d_con.ROOT,strlen(d_con.ROOT));
    
    strcat(pedido, arch_pedido);
    //completo la ruta del archivo pedido
    printf("sd_conn: %d \t pedido:%s \n",sd_conn,pedido);
    
    
    if((strncmp("GET",metodo,3)==0)){

         //sscanf(buf, "%*[^Cookie:]%*c",cookie);
        sscanf(buf, "%*[^@]%s",cookie);
        printf("cookie %s \n",cookie);
		int a = strlen(cookie);
		printf("strlen %d \n",a);
        if((strncmp(pedido,"www/favicon.ico",strlen("www/favicon.ico"))!=0) )
        {

            
          
            
            
            if(strlen(cookie) == 0)
            {

                
                printf("login \n");
                
                strncpy(login,d_con.ROOT,strlen(d_con.ROOT));
                
                char init[256] = "login.html";
                
                strcat(login,init);
                
                if((fd_arch=open(login,O_RDONLY,0666))!=-1)
                {
                    strcpy(out_msj,OK_HTML);
                    
                    write(sd_conn,out_msj, strlen(out_msj));
                    
                    while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0)
                    {
                    	printf("escribo el login \n");
                        write(sd_conn,buf_arch,n);
                        i++;
                        
                    }
                }          
                
            }
            sscanf(pedido, "%*[^=]%*c%[^&]%*[^=]%*c%[^&]",userTmp,passTmp);
            printf("user %s y pass %s \n",userTmp,passTmp);
            if((strncmp(cookie,"@00",strlen("@00"))==0) && (strlen(userTmp) > 0) && (strlen(passTmp) > 0))
            {
            	printf("Antes de la cola de mensaje");
               	Clave1 = ftok ("/bin/ls", 33);
				if (Clave1 == (key_t)-1)
				{
					printf("Error al obtener clave para cola mensajes");
					
				}
				
				Id_Cola_Mensajes = msgget (Clave1, 0600 | IPC_CREAT);
				if (Id_Cola_Mensajes == -1)
				{
					printf("Error al obtener identificar para la cola de mensajes");
					
				}
				
				strcat(userPass,userTmp);
				strcat(userPass,"|");
				strcat(userPass,passTmp);
						
                Un_Mensaje.Id_Mensaje = 1;
                
				strcpy (Un_Mensaje.Mensaje, userPass);
                
				msgsnd (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Mensaje),IPC_NOWAIT);

				msgrcv (Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje,sizeof(Un_Mensaje.Mensaje),2, 0);
			
				printf("Mensaje: %s \n",Un_Mensaje.Mensaje);
                
                printf("LOGEO BIEN \n");
				if(strncmp("true",Un_Mensaje.Mensaje,strlen(Un_Mensaje.Mensaje)) == 0)
				{
		            strncpy(index,d_con.ROOT,strlen(d_con.ROOT));
		            
		            lg = "index.html";
		            
		            strcat(index,lg);
		            
		            if((fd_arch2=open(index,O_RDONLY,0666))!=-1)
		            {
		                
		                strcpy(out_msj2,OK_HTML_LTRUE);
		                
						write(sd_conn,out_msj2, strlen(out_msj2));
		                i++;
		                while((n2=read(fd_arch2,buf_arch2, sizeof buf_arch2))>0)
		                {
		                    write(sd_conn2,buf_arch2,n2);

		                    
		                }
		            }
                }
                else
                {
                strncpy(index,d_con.ROOT,strlen(d_con.ROOT));
		            
		             lg = "loginMensaje.html";
		            
		            strcat(index,lg);
		            
		            if((fd_arch2=open(index,O_RDONLY,0666))!=-1)
		            {
		                
		                strcpy(out_msj2,OK_HTML);
		                
						write(sd_conn,out_msj2, strlen(out_msj2));
		                i++;
		                while((n2=read(fd_arch2,buf_arch2, sizeof buf_arch2))>0)
		                {
		                    write(sd_conn2,buf_arch2,n2);

		                    
		                }
		            }
                }
                
            }
                       printf("i %d \n",i);
            if((strncmp(cookie,"@11",strlen("@11"))==0))
            {
                sscanf(pedido, "%*[^/]%*c%[^&]",url);
                
                printf("url  %s \n",url);
                
                printf("FUNC1 %s \n",FUNC1);
                
                
               // if((strncmp(url,FUNC1,strlen(FUNC1))==0))
               // {
                    printf("entro estoy en la funcion \n");

                    printf("pedidoo %s \n",pedido);
                   	resp = command(pedido);
                    //printf("respuestaaaaa %s \n",resp);
                    strcat(prueba,INIT);
                    
                    strcat(prueba,resp);
                    
                    strcat(prueba,CLOSE);
                    
                    printf("PRUEBA %s \n",prueba);
                    
                    strcpy(out_msj2,OK_HTML_LTRUE);
                    
					write(sd_conn,out_msj2, strlen(out_msj2));
                    
                    write(sd_conn,prueba, strlen(prueba));
                    i++;
                    
                    //printf("entro \n");
                    
                //}
            }
            
            
            printf("i %d \n",i);
            if(i == 0)
            {

                
                printf("login \n");
                
                strncpy(login,d_con.ROOT,strlen(d_con.ROOT));
                
                char init[256] = "login.html";
                
                strcat(login,init);
                
                if((fd_arch=open(login,O_RDONLY,0666))!=-1)
                {
                    strcpy(out_msj,OK_HTML);
                    
                    write(sd_conn,out_msj, strlen(out_msj));
                    
                    while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0)
                    {
                    	printf("escribo el login \n");
                        write(sd_conn,buf_arch,n);
                        i++;
                        
                    }
                }          
                
            }
            
            
            
            close (fd_arch);
            
        }
    }
    else
    {
        
        
        strncpy(index,d_con.ROOT,strlen(d_con.ROOT));
        
        strcat(pedido,"index.html");
        
        if((fd_arch=open(index,O_RDONLY,0666))==-1){
            strcpy(out_msj,OK_HTML);
            
            write(sd_conn,out_msj, strlen(out_msj));
            
            
            while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0){
                write(sd_conn,buf_arch,n);
                i++;
                
            }
        }
        close (fd_arch);
        
        strcpy(out_msj,NOTOK_501);
        
        write(sd_conn,out_msj, strlen(out_msj));
        
        strcpy(out_msj,MESS_501);
        
        write(sd_conn,out_msj, strlen(out_msj));
        i++;
        
        
    }
           
    
    close (sd_conn);
    
}
