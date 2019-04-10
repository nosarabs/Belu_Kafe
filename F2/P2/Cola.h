#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
using namespace std;
/*
 * Estructura para los mensajes que se quieren encolar y desencolar
 */
typedef struct
{
    long id_Mensaje;
    int tamano;
    char mensaje[128];
}mi_Mensaje;
/*
 *Clase Cola para encolar y desencolar mensajes */
class Cola{
    private:
        key_t clave;
        int id_Cola;
    public:
        mi_Mensaje un_Mensaje;
        /*
         * constructor de la cola
         */
        Cola();
        /*Encola un mensaje con prioridad 
         */
        void encolar_Mensaje(long, char *, int);
        /*Desencola un mensaje de la prioridad indicada
         */
        int desencolar_Mensaje(long);
        /*
         * Destructor del Buzon
         */
        ~Cola();
};
#endif
 
