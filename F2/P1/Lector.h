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
    void crearContratista(/*Tenemos que definir como le vamos a pasar la dirección del directorio*/);
};

#endif //LECTOR_H