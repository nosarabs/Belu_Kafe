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
#include <list>

using namespace std;

typedef struct{
	int id;
	char msj[128];
}mensaje;

typedef struct{
    size_t id;
    Buzon * mi_buzon;
    pthread_mutex_t * mutex;
    list<mensaje> * mensajes;
    
}mi_data;

class Emisor
{

private:
    /* data */
    Buzon * buzonC;
    vector<pthread_t> thread;
    size_t hilosConstruidos;
    list<mensaje> mensajes;
public:    
    Emisor();
    virtual ~Emisor();
    /*recibe los mensajes tipo 1 (mientras hayan) que le envian los
     * contratistas
     */
    void Recibir();
    /*
     */
    
    static void* hiloArchivo(void * data){
        mi_data * dt=(mi_data *) data;
        //dt->id =(size_t)data;
        //dt->mi_buzon=new Buzon();
        string cadena = "nuevo" + to_string(dt->id) + ".jpg";
	    int id = open( cadena.data(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
        strcpy(dt->mi_buzon->un_Mensaje.mensaje,"");
        dt->mi_buzon->enviar_Mensaje(100+dt->id, dt->mi_buzon->un_Mensaje.mensaje);
        do{
			dt->mi_buzon->recibir_Mensaje(dt->id);
			if(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0){
				write( id, dt->mi_buzon->un_Mensaje.mensaje, dt->mi_buzon->un_Mensaje.chunk_Num);
				pthread_mutex_lock(dt->mutex);
				mensaje men;
				memcpy(men.msj,dt->mi_buzon->un_Mensaje.mensaje, dt->mi_buzon->un_Mensaje.chunk_Num);
				men.id= dt->mi_buzon->un_Mensaje.id_Contratista;
				dt->mensajes->push_back(men);
				pthread_mutex_unlock(dt->mutex);
			}
        }while(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0);
        strcpy(dt->mi_buzon->un_Mensaje.mensaje,"");
        dt->mi_buzon->enviar_Mensaje(90000+dt->id, dt->mi_buzon->un_Mensaje.mensaje);
        return NULL;
    }
    
};

#endif //EMISOR_h
