#ifndef CONTRATISTA_H
#define CONTRATISTA_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Contratista
{

private:
    /* data */
    char * archivo;
public:    
    Contratista(char * archivo);
    virtual ~Contratista();
    /*lee archivo por partes de 512bytes en 512bytes 
     */
    void leerArchivo();
    void particionarArchivo();
    void empaquetar();
    void enviarAlEmisor();
    void clean_buffer(char * &, size_t);

};

#endif //CONTRATISTA_H
