#ifndef _FUNC_H_
#define _FUNC_H_

	#define OK_JPEG    "HTTP/1.0 200 OK\nContent-Type:image/jpeg\nContent-Length:%d\n\n"
	#define OK_HTML    "HTTP/1.0 200 OK\nContent-Type:text/html\nSet-Cookie: sessionToken=@00; max-age=<40>\nContent-Length:%d\n\n"
	#define OK_HTML_LTRUE    "HTTP/1.0 200 OK\nContent-Type:text/html\nSet-Cookie: sessionToken=@11; max-age=<5000>\nContent-Length:%d\n\n"
	#define OK_CSS    "HTTP/1.0 200 OK\nContent-Type:text/css\nContent-Length:%d\n\n"
	#define OK_TXT    "HTTP/1.0 200 OK\nContent-Type:text/plain\nContent-Length:%d\n\n"
	#define OK_PDF     "HTTP/1.0 200 OK\nContent-Type:application/pdf\nContent-Leng:%d\n\n"

	#define NOTOK_404   "HTTP/1.0 404 Not Found\nContent-Type:text/html\n\n"
	#define MESS_404    "<html><body><h1>FILE NOT FOUND</h1></body></html>"
	#define NOTOK_500   "HTTP/1.0 500 Internal Server Error\nContent-Type:text/html\n\n"
	#define MESS_500    "<html><body><h1>Internal Server Error</h1></body></html>"
	#define NOTOK_501   "HTTP/1.0 501 Not Implemented\nContent-Type:text/html\n\n"
	#define MESS_501    "<html><body><h1>Not Implemented</h1></body></html>"
	#define HTTP_V	"HTTP/1.0"
	
	#define USER     "jp"
	#define PASS     "1234"
	#define FUNC1     "test.html"
	#define INIT     "<html><body><h1><li>" 
	#define CLOSE     "</h1></body></html>"
	#define EMPTY   "<html><body><h1>Not Implemented</h1></body></html>"
	#define DIRLOG   "/home/jpfernandez/Escritorio/Compu/www/log.txt"
	#define DIRUSER 	"/home/jpfernandez/Escritorio/Compu/www/user.txt"
	#define DIRRAM 	"/home/jpfernandez/Escritorio/Compu/www/ram.txt"
	#define DIRMEMORY 	"/home/jpfernandez/Escritorio/Compu/www/memory.txt"
	#define LOGIN 	"/home/jpfernandez/Escritorio/Compu/www/login.html"
	#define INDEX 	"/home/jpfernandez/Escritorio/Compu/www/index.html"
	#define INDEXMENSAJE 	"/home/jpfernandez/Escritorio/Compu/www/loginMensaje.html"
	#define COLAMSJ 	"/home"
	#define COLAMSJ2 	"/bin"
	#define COLAMSJ3 	"/tmp"
	#define PUERTOI 	3470
	#define PUERTO	"3485"
#endif



