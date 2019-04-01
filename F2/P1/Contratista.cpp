#include "Contratista.h"

Contratista::Contratista(char * archivo){
    this->archivo = archivo;
}

Contratista::~Contratista(){

}

void Contratista::leerArchivo(){
    size_t b_size = 512; 
    char *buffer = new char[b_size];
    ifstream file(this->archivo, ios::binary );
    clean_buffer(buffer, b_size);
    while (file)
    {
        // lee el segmento de información
        file.read(buffer, b_size);
        // se obtienen los bytes que se leyeron
        size_t count = file.gcount();
        // si no se leyó nada termina
        if (!count){
            break;
        }
        //AQUII DEBERIA PARTIR EN PEDACITOS DE 128
        clean_buffer(buffer, b_size);
    }
    file.close();
    delete[] buffer;
}


void clean_buffer(char * &buffer, size_t size){
    for(int index=0; index<size; ++index){
        buffer[index]=' ';
    }
}

void Contratista::particionarArchivo(){

}

void Contratista::empaquetar(){

}

void Contratista::enviarAlEmisor(){

}

