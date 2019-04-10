#include "Receptor.h"

Receptor::Receptor(){
    this->cola=new Cola();
}

Receptor::~Receptor(){
    delete cola;
}

void Receptor::conectar(){
    
}

void Receptor::desempaquetar(char * paquete){
    
}
void Receptor::encolar(char * mensajeUtil, long id, int tamano){
    
}
