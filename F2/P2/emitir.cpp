#include "Emisor.h" 

int main(int argc, char *argv[]){
    char * server;
	if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    server = argv[1];
    Emisor emisor;
    emisor.Recibir(server);
} 
