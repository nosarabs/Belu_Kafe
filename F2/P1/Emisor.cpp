#include "Emisor.h"

Emisor::Emisor(){
    hilosConstruidos=1;
    buzonC= new Buzon();
}

Emisor::~Emisor(){

}

void Emisor::Recibir(){
    cout<<"creado emisor"<<endl;
   // while(true){
        buzonC->recibir_Mensaje(10000);
        cout<<"creare hilo"<<endl;
        pthread_t newthread;
        mi_data data;
        data.id=hilosConstruidos;
        data.mi_buzon=buzonC;
        thread.push_back(newthread);
        pthread_create(&thread[hilosConstruidos-1], NULL, &Emisor::hiloArchivo, (void*)&data);
        ++hilosConstruidos;
    //}
     for(int i=0; i<thread.size();++i)   
        pthread_join(thread[i], NULL);
    delete buzonC;
}

void Emisor::Desempaquetar(){

}

void Emisor::Guardar(){ // en alguna ED conforme se va desempaquetando
    
   
}

void Emisor::ReconstruirArchivo(){

}

