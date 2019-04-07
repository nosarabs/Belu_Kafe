#include "Emisor.h"

Emisor::Emisor(){
    this->hilosConstruidos=1;
    this->buzonC= new Buzon();
}

Emisor::~Emisor(){

}

void Emisor::Recibir(){
    cout<<"creado emisor"<<endl;
    while(true){
        this->buzonC->recibir_Mensaje(201+hilosConstruidos);
        cout<<"creare hilo "<<hilosConstruidos<<endl;
        pthread_t newthread;
        //datos[(this->hilosConstruidos)-1].mi_buzon=buzonC;
        thread.push_back(newthread);
        pthread_create(&thread[(this->hilosConstruidos)-1], NULL, &Emisor::hiloArchivo, (void *)this->hilosConstruidos);
        cout<<"creado"<<endl;
        //hiloArchivo((void*)&data);
        ++(this->hilosConstruidos);
    }
        for(int i=0; i<thread.size();++i)   
            pthread_join(thread[i], NULL);
        //delete buzonC;
}
