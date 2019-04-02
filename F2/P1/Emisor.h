#ifndef EMISOR_h
#define EMISOR_h

#include "Buzon.h"
#include <string>
#include <pthread.h>
#include <fstream>

using namespace std;

class Emisor
{

private:
    /* data */
    Buzon buzonE;
    pthread_t thread;
    size_t hilosConstruidos = 1;
public:    
    Emisor(/* args */);
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
    void* hiloArchivo(void * data);
};

#endif //EMISOR_h
