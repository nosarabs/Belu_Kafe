#ifndef EMISOR_h
#define EMISOR_h

#include "Buzon.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <fstream>
#include <vector>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#define PORT 9999 

using namespace std;

typedef struct{
    size_t id;
    Buzon * mi_buzon;
    pthread_mutex_t * mutex;
    queue <mi_Mensaje> * mensajes;
    
}mi_data;

typedef struct{
	queue <mi_Mensaje> * mensajitos;
    pthread_mutex_t * mutex2;
	char * ip;
}mi_data2;

class Emisor
{

private:
    /* data */
    Buzon * buzonC;
    vector<pthread_t> thread;
    size_t hilosConstruidos;
    queue <mi_Mensaje> mensajes;
public:    
    Emisor();
    virtual ~Emisor();
    /*recibe los mensajes tipo 1 (mientras hayan) que le envian los
     * contratistas
     */
    void Recibir(char *);
    /*
     */
    
    static void* hiloArchivo(void * data){
        mi_data * dt=(mi_data *) data;
        dt->mi_buzon=new Buzon();
        strcpy(dt->mi_buzon->un_Mensaje.mensaje,"");
        dt->mi_buzon->enviar_Mensaje(100+dt->id, dt->mi_buzon->un_Mensaje.mensaje);
        do{
            dt->mi_buzon->recibir_Mensaje(dt->id);
            if(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0){
                pthread_mutex_lock(dt->mutex);
                mi_Mensaje * men= new mi_Mensaje;
                memcpy(men->mensaje,dt->mi_buzon->un_Mensaje.mensaje, dt->mi_buzon->un_Mensaje.chunk_Num);
                men->id_Mensaje= dt->mi_buzon->un_Mensaje.id_Mensaje;
                men->chunk_Num= dt->mi_buzon->un_Mensaje.chunk_Num;
                dt->mensajes->push(*men);
                pthread_mutex_unlock(dt->mutex);
                delete men;
            }else{
                pthread_mutex_lock(dt->mutex);
                mi_Mensaje * men= new mi_Mensaje;
                strcpy(men->mensaje,"");
                men->id_Mensaje= dt->mi_buzon->un_Mensaje.id_Mensaje;
                men->chunk_Num= 0;
                dt->mensajes->push(*men);
                pthread_mutex_unlock(dt->mutex);
                delete men;
            }
        }while(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0);
        strcpy(dt->mi_buzon->un_Mensaje.mensaje,"");
        dt->mi_buzon->enviar_Mensaje(90000+dt->id, dt->mi_buzon->un_Mensaje.mensaje);
        return NULL;
    }
    
    static void* hiloEnviador(void * data){ //DEBERIA ENVIAR MENSAJE VACIO PARA QUE EL RECEPTOR SEPA QUE ACABOO EL ARCHIVO
        //Y SE DEBE ENVIAR TAMBIEN EL TAMAÑO DEL MENSAJE PARA QUE EL EMISOR LO ESCRIBA
		mi_data2 * dt = (mi_data2 *)data;
		struct sockaddr_in address; 
		int sock = 0, valread; 
		struct sockaddr_in serv_addr;
		
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
			printf("\n Socket creation error \n"); 
			return NULL; 
		}
		
		memset(&serv_addr, '0', sizeof(serv_addr)); 

		serv_addr.sin_family = AF_INET; 
		serv_addr.sin_port = htons(PORT); 
		
		// Convert IPv4 and IPv6 addresses from text to binary form 
		if(inet_pton(AF_INET, dt->ip, &serv_addr.sin_addr) <= 0) { 
			printf("\nInvalid address/ Address not supported \n"); 
			return NULL; 
		} 
		
		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
			printf("\nConnection Failed \n"); 
			return NULL; 
		}
		char m[2];
		while(true){
            if(dt->mensajitos){
                if(!dt->mensajitos->empty()){
                    pthread_mutex_lock(dt->mutex2);
                    mi_Mensaje * msj = &(dt->mensajitos->front());
                    cout<<msj->id_Mensaje<<" ";
                    write(sock , msj , sizeof(mi_Mensaje));
                    recv(sock , &m[0] , 2,MSG_WAITALL);
                    dt->mensajitos->pop();
                    pthread_mutex_unlock(dt->mutex2);
                }
            }else{
                break;
            }
		}
	}
};

#endif //EMISOR_h
