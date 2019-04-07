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

using namespace std;

typedef struct{
    size_t id;
    Buzon * mi_buzon;
}mi_data;

class Emisor
{

private:
    /* data */
    Buzon * buzonC;
    vector<pthread_t> thread;
    size_t hilosConstruidos;
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
        mi_data * dt=new mi_data;
        dt->id =(size_t)data;
        dt->mi_buzon=new Buzon();
        cout<<"dt: "<<dt->id<<endl;
        string cadena = "nuevo" + to_string(dt->id) + ".jpg";
	    int id = open( cadena.data(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
        cout << "Cree archivo " << dt->id << endl;
        dt->mi_buzon->enviar_Mensaje(100+dt->id,"");
        do{
            dt->mi_buzon->recibir_Mensaje(dt->id);
            if(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0){
                write( id, dt->mi_buzon->un_Mensaje.mensaje, dt->mi_buzon->un_Mensaje.chunk_Num);
	     }
        }while(strcmp(dt->mi_buzon->un_Mensaje.mensaje,"FIN")!=0);
        cout<<"Termine de escribir archivo soy hilo "<<dt->id<<endl;
        //dt->mi_buzon->enviar_Mensaje(90000+dt->id,"");
        return NULL;
    }
    
};

#endif //EMISOR_h
