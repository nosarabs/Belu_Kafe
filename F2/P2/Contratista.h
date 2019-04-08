#ifndef CONTRATISTA_H
#define CONTRATISTA_H

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Buzon.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

class Contratista
{

private:
    char * archivo;
    int id;
    Buzon * buzonC;

public:
    
    Contratista(char * archivo, int id);
    ~Contratista();
    /*lee archivo por partes de 512bytes en 512bytes
     */
    void leerArchivo();
    /*
     * Método de recibe el buffer de 512 y lo particiona en 
     * pedacitos de 128 en 128
     */
    void particionarArchivo(char * archivo, int);
    /*
     * Método que utiliza el struct "mi_mensaje" del mensaje de buzon para 
     * generar el paquete  
     */
    void empaquetar(char * archivo, int chunkNum);
    /*
     * Método que llama al 
     * método recibir_Mensaje de buzon
     */
    void enviarAlEmisor();
    /*
     * Método para limpiar buffer
     */
    void clean_buffer(char * &, size_t);

};

#endif //CONTRATISTA_H
