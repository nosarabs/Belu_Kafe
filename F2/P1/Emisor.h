#ifndef EMISOR_h
#define EMISOR_h

#include "Buzon.h"
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
    void Desempaquetar();
    void Guardar(); // en alguna ED conforme se va desempaquetando
    void ReconstruirArchivo();
    
    static void* hiloArchivo(void* data){
        mi_data * dt = (mi_data *)data;
        string cadena= "nuevo" + to_string(dt->id) + ".jpg";
        ofstream destino(cadena,ios::binary);
        cout<<"cree archivo"<<endl;
        do{
            dt->mi_buzon->recibir_Mensaje(dt->id);
            destino.write(dt->mi_buzon->un_Mensaje.mensaje, strlen(dt->mi_buzon->un_Mensaje.mensaje));
        }while(true);
        
        cout<<"terminee"<<endl;
        dt->mi_buzon->enviar_Mensaje(90000+dt->id,"Terminee");
        return NULL;
    }
    
};

#endif //EMISOR_h
