#include "Emisor.h"

Emisor::Emisor(){
    this->hilosConstruidos=1;
    this->buzonC= new Buzon();
}

Emisor::~Emisor(){

}

void Emisor::Recibir(char * server){
	pthread_mutex_t * mutexE = new pthread_mutex_t;
	pthread_mutex_init(mutexE,NULL);
	pthread_t threadSend;
	mi_data2 * data2 = new mi_data2;
	data2->ip= server;
	data2->mensajitos = &this->mensajes;
	pthread_create(&threadSend, NULL, &Emisor::hiloEnviador, (void *)data2);
	
    while(true){
        int recibido = this->buzonC->recibir_Mensaje(201+hilosConstruidos);
        if(recibido == -1){
            break;
        }
        mi_data * data = new mi_data;
        data->id = hilosConstruidos;
        data->mi_buzon = new Buzon();
        data->mutex = mutexE;
        data->mensajes = &this->mensajes;
        pthread_t newthread;
        thread.push_back(newthread);
        pthread_create(&thread[(this->hilosConstruidos)-1], NULL, &Emisor::hiloArchivo, (void *)data);
        ++(this->hilosConstruidos);
    }
	for(int i=0; i<thread.size();++i)
		pthread_join(thread[i], NULL);
}
