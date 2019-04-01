#ifndef EMISOR_h
#define EMISOR_h

#include <string>
#include <list>
#include <queue>
#include "Buzon.h"
using namespace std;

using namespace std;

class Emisor
{

private:
    Buzon buzon;
    list< queue < char * > > archivos;
public:    
    Emisor(/* args */);
    virtual ~Emisor();
    void Recibir();
    void Desempaquetar();
    void Guardar(); // en alguna ED conforme se va desempaquetando
    void ReconstruirArchivo();
};

#endif //EMISOR_h