
#include "http_worker.h"
#include "func.h"

void http_worker(int sd_conn, void *addr){
    
    char buf[4096]={0}, buf_arch[4096]={0}, buf_arch2[4096]={0}, arch_pedido[256]={0};   
    char out_msj[1024]={0},out_msj2[1024]={0},login[256]={0},index[256]={0},pedido[256]={0}, metodo[256]={0},userTmp[256]={0},cookie[256]={0},passTmp[256]={0},url[256]={0};   
    int n,n2,fd_arch,fd_arch2;   
    int sd_conn2 = sd_conn;  
    char *resp = NULL;
    char *result = NULL;
    char prueba[512] = {0};
	int i = 0;
	char *lg = NULL;        
    read (sd_conn, buf,sizeof buf);    
    arch_pedido[255]=0;
    sscanf(buf, "%s /%s" ,metodo,arch_pedido);  
    strncpy(pedido,d_con.ROOT,strlen(d_con.ROOT));    
    strcat(pedido, arch_pedido);
    //completo la ruta del archivo pedido
    printf("pedido:%s \n",pedido);   
    
    if((strncmp("GET",metodo,3)==0)){

        sscanf(buf, "%*[^@]%s",cookie);
        //printf("cookie %s \n",cookie);
        if((strncmp(pedido,"www/favicon.ico",strlen("www/favicon.ico"))!=0) )
        {  
            if(strlen(cookie) == 0)
            {              
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
                        i++;                       
                    }
                }                         
            }
            sscanf(pedido, "%*[^=]%*c%[^&]%*[^=]%*c%[^&]",userTmp,passTmp);
            printf("user %s y pass %s \n",userTmp,passTmp);
            if((strncmp(cookie,"@00",strlen("@00"))==0) && (strlen(userTmp) > 0) && (strlen(passTmp) > 0))
            {
			result = InitLogin(userTmp,passTmp);      
						if(strncmp("true",result,strlen(result)) == 0)
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
            if((strncmp(cookie,"@11",strlen("@11"))==0))
            {
                sscanf(pedido, "%*[^/]%*c%[^&]",url);                                
                resp = command(pedido);
                    strcat(prueba,INIT);                 
                    strcat(prueba,resp);                  
                    strcat(prueba,CLOSE);                    
                    strcpy(out_msj2,OK_HTML_LTRUE);                    
					write(sd_conn,out_msj2, strlen(out_msj2));                    
                    write(sd_conn,prueba, strlen(prueba));
                    i++;
            }                        
            if(i == 0)
            {               
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
