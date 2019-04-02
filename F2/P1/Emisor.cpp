#include "Emisor.h"

Emisor::Emisor(){

}

Emisor::~Emisor(){

}

void Emisor::Recibir(){
    void* (*hiloArchivo)(void*);
    while(true){
        buzonE.recibir_Mensaje(10000);
        pthread_create(&thread, NULL, hiloArchivo, (void*)(hilosConstruidos));
    }
    
}

void Emisor::Desempaquetar(){

}

void Emisor::Guardar(){ // en alguna ED conforme se va desempaquetando
    
   
}

void Emisor::ReconstruirArchivo(){

}

void* Emisor::hiloArchivo(void* data){
    size_t idThread = (size_t)data;
    ofstream destino(string("nuevo" + to_string(idThread) + ".jpg"),ios::binary);
    do{
        buzonE.recibir_Mensaje(idThread);
        destino.write(buzonE.un_Mensaje.mensaje, strlen(buzonE.un_Mensaje.mensaje));
    } while (!buzonE.un_Mensaje.fin);
    
    return NULL;
}
