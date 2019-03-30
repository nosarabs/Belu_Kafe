#ifndef CONTRATISTA_H
#define CONTRATISTA_H

#include <string>

using namespace std;

class Contratista
{

private:
    /* data */
public:    
    Contratista(/* La dirección obtenida del lector, lector crea contratistas */);
    virtual ~Contratista();
    void leerArchivo();
    void particionarArchivo();
    void empaquetar();
    void enviarAlEmisor();

};

#endif //CONTRATISTA_H