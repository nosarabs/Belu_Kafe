#ifndef BUZON
#define BUZON

#include <iostream>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
using namespace std;
/*
 * Estructura para los mensajes que se quieren enviar o recibir
 * debe tambien llevar el campo del encabezado QUE AUN NO HEMOS DEFINIDO
 */
typedef struct
{
    long id_Mensaje;
    int chunk_Num;
    char mensaje[128];
}mi_Mensaje;
/*
 *Clase Buzon para establecer la comunicacion entre procesos
 */
class Buzon{
    private:
        key_t clave;
        int id_Cola;
    public:
        mi_Mensaje un_Mensaje;
        /*
         * constructor del Buzon
         */
        Buzon();
        /*
         * Envia un mensaje el long es un dentificador del mensaje es decir si la comunicacion
         * es entre dos procesos necesito que el proceso 1 lea mensajes tipo 2
         * y el proceso 2 lea mensajes tipo 1
         */
        void enviar_Mensaje(long, char *);
        /*Recibe mensajes, el parametro long es para el tipo de mensajes
         * que deseo recibir, es decir, si soy proceso 1 recibo mensajes
         * tipo 2, y si soy proceso 2 recibo mensajes tipo 1
         */
        int recibir_Mensaje(long);
        /*
         * Destructor del Buzon
         */
        ~Buzon();
};
#endif
