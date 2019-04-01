#ifndef LECTOR_H
#define LECTOR_H
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Contratista.h"
#include <vector>
using namespace std;

class Lector
{

private:
    string directorio;
    int idParaContratista;
    vector<string> directorios;
    int actual;
public:    
    Lector(/* args */);
    ~Lector();
    int  obtenerDirectorio(char *);
    void crearContratista(char *, int);
};

#endif //LECTOR_H
