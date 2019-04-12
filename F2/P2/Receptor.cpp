#include "Receptor.h"

Receptor::Receptor(){
    this->cola=new Cola();
    this->hilosConstruidos=1;
}

Receptor::~Receptor(){
    delete cola;
}

void Receptor::conectar(){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char * buffer = new char[sizeof(mi_Mensaje)];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    } else {
        cout<<"Conexión de la IP: "<<address.sin_addr.s_addr<< " Puerto: "<< address.sin_port<<" ha sido exitosa."<<endl;
    }

    while(true){
        valread = recv( new_socket , buffer, sizeof(mi_Mensaje), MSG_WAITALL);
        if (valread < 0){
            perror("recv");
            exit(EXIT_FAILURE);
        }
       
        desempaquetar(buffer);
        write( new_socket , "ya", 2);
    }
    delete buffer;
}

void Receptor::desempaquetar(char * paquete){
    mi_Mensaje * msj = (mi_Mensaje * )paquete;
    encolar(&(msj->mensaje[0]), msj->id_Mensaje, msj->tamano);
    //cout<<msj->id_Mensaje<<endl;
    //cout<<msj->tamano<<endl;
}

void Receptor::encolar(char * mensajeUtil, long id, int tamano){
    int cont=0;
   bool almacenado = false;
   while(cont<vectorIds.size() && !almacenado){
       if(vectorIds[cont]==id){
           almacenado = true;
       }
       cont++;
   }
   if(!almacenado){
        vectorIds.push_back(id);
        pthread_t newthread;
        cout<<"creando thread "<<id<<endl;
        vectorThreads.push_back(newthread);
        pthread_create(&vectorThreads[(this->hilosConstruidos)-1], NULL, &Receptor::hiloEscritor, (void *)id);
        ++(this->hilosConstruidos);
        // pthread_t threadWriter;
        // pthread_create(&threadWriter, NULL, &Receptor::hiloEscritor, (void *)id);
   }
    cola->encolar_Mensaje(id, mensajeUtil, tamano);
   
}
