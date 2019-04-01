#ifndef CONTRATISTA_H
#define CONTRATISTA_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Paquete;

class Contratista
{

private:
    char * archivo;
    int id;

public:
    struct Paquete{
        int id = this->id; //
        int chunkNum; //numero de pedacito
        char * chunk;

        Paquete(){};


        Paquete& operator=(const Paquete& orig) {
            id = orig.id;
            chunkNum = orig.chunkNum;
            chunk = orig.chunk;
        };
    };

    Contratista(char * archivo, int id);
    virtual ~Contratista();
    /*lee archivo por partes de 512bytes en 512bytes
     */
    void leerArchivo();
    void particionarArchivo(char * archivo);
    void empaquetar(char * archivo, int chunkNum);
    void enviarAlEmisor(Paquete paquete);
    void clean_buffer(char * &, size_t);

};

#endif //CONTRATISTA_H
