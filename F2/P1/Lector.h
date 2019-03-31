#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include <iostream>
#include "Contratista.h"

using namespace std;

class Lector
{

private:
    string directorio;
public:    
    Lector(/* args */);
    virtual ~Lector();
    void obtenerDirectorio();
    void crearContratista(char * archivo, int id);
};

#endif //LECTOR_H