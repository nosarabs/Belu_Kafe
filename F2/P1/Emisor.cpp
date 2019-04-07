#include "Emisor.h"

Emisor::Emisor(){
    this->hilosConstruidos=1;
    this->buzonC= new Buzon();
}

Emisor::~Emisor(){

}

void Emisor::Recibir(){
    while(true){
        int recibido = this->buzonC->recibir_Mensaje(201+hilosConstruidos);
        if(recibido == -1){
            break;
        }
        pthread_t newthread;
        thread.push_back(newthread);
        pthread_create(&thread[(this->hilosConstruidos)-1], NULL, &Emisor::hiloArchivo, (void *)this->hilosConstruidos);
        ++(this->hilosConstruidos);
    }
        for(int i=0; i<thread.size();++i)   
            pthread_join(thread[i], NULL);
}
