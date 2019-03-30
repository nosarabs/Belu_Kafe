#ifndef EMISOR_h
#define EMISOR_h

#include <string>

using namespace std;

class Emisor
{

private:
    /* data */
public:    
    Emisor(/* args */);
    virtual ~Emisor();
    void Recibir();
    void Desempaquetar();
    void Guardar(); // en alguna ED conforme se va desempaquetando
    void ReconstruirArchivo();
};

#endif //EMISOR_h