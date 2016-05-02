
#include "http_worker.h"
#include "func.h"

void http_worker(int sd_conn, void *addr){
                    printf("entra worker\n");   
    char buf[4096]={0},arch_pedido[256]={0};   
    char out_msj[1024]={0},out_msj2[1024]={0},pedido[256]={0}, metodo[256]={0},userTmp[256]={0},cookie[256]={0},passTmp[256]={0},url[256]={0},prueba[512] = {0};   
    int i=0;   
    char *resp = NULL,*result = NULL;
    read (sd_conn, buf,sizeof buf);    
    arch_pedido[255]=0;
    sscanf(buf, "%s /%s" ,metodo,arch_pedido);  
    strncpy(pedido,d_con.ROOT,strlen(d_con.ROOT));    
    strncat(pedido, arch_pedido,strlen(arch_pedido));
    //completo la ruta del archivo pedido
    printf("pedido:%s \n",pedido);   
    
    if((strncmp("GET",metodo,3)==0)){

        sscanf(buf, "%*[^@]%s",cookie);
        if((strncmp(pedido,"www/favicon.ico",strlen("www/favicon.ico"))!=0) )
        {  
            if(strlen(cookie) == 0)
            {                           
              response(sd_conn,1);
              i++;       //1 login          
            }
            sscanf(pedido, "%*[^=]%*c%[^&]%*[^=]%*c%[^&]",userTmp,passTmp);
            printf("user %s y pass %s \n",userTmp,passTmp);
            if((strncmp(cookie,"@00",strlen("@00"))==0) && (strlen(userTmp) > 0) && (strlen(passTmp) > 0))
            {
			result = InitLogin(userTmp,passTmp);      
						if(strncmp("true",result,strlen(result)) == 0)
						{	            
						     response(sd_conn,2);       //2 index true        
						     i++;            
				        }
				        else
				        {	            
						   response(sd_conn,3); //3 index mensaje
						   i++;            
				        }          
            }
            if((strncmp(cookie,"@11",strlen("@11"))==0))
            {
             sscanf(pedido, "%*[^/]%*c%[^&]",url);       
             printf("pedido en worker %s\n",pedido);                         
             if((strncmp(pedido,"www/logOut",strlen("www/logOut")))==0 || (strncmp(pedido,"logOut",strlen("logOut")))==0)
             {             
                response(sd_conn,1);       //1 login   
                i++;                   
             }
             else
             {
                sscanf(pedido, "%*[^/]%*c%[^&]",url);                                
                resp = command(pedido);
                    strncat(prueba,INIT,strlen(INIT));                 
                    strncat(prueba,resp,strlen(resp));                  
                    strncat(prueba,CLOSE,strlen(CLOSE));                    
                    strncpy(out_msj2,OK_HTML_LTRUE,strlen(OK_HTML_LTRUE));                    
					write(sd_conn,out_msj2, strlen(out_msj2));                    
                    write(sd_conn,prueba, strlen(prueba));
                    i++;
              }
            }                        
            if(i == 0)
            {                            
              response(sd_conn,1);
              i++;       //1 login                           
            }           
        }
    }
    else
    { 
        response(sd_conn,1);      //1 login      
        i++;            
        strncpy(out_msj,NOTOK_501,strlen(NOTOK_501));        
        write(sd_conn,out_msj, strlen(out_msj));        
        strncpy(out_msj,MESS_501,strlen(MESS_501));        
        write(sd_conn,out_msj, strlen(out_msj));
        i++;              
    }               
    close (sd_conn);    
}
