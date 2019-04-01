#ifndef EMISOR_h
#define EMISOR_h

#include <string>
#include "Buzon.h"
using namespace std;

class Emisor
{

private:
    /* data */
    Buzon buzonE;
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
};

#endif //EMISOR_h
