#include "Receptor.h"

Receptor::Receptor(){
    this->cola=new Cola();
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

  int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
  if (new_socket < 0){
      perror("accept");
      exit(EXIT_FAILURE);
  } else {
    printf("Conexión de la IP: ", address.sin_addr.s_addr, "Puerto: ", address.sin_port, " ha sido exitosa.");
  }

  while(true){
    valread = read( new_socket , buffer, sizeof(mi_Mensaje));
    if (valread < 0){
        perror("read");
        exit(EXIT_FAILURE);
    }
    desempaquetar(buffer);
  }
}

void Receptor::desempaquetar(char * paquete){
  mi_Mensaje * msj = (mi_Mensaje * )paquete;
  encolar(&(msj->mensaje), msj->id_Mensaje, sizeof(msj->tamano));
  cout<<msj->mensaje<<endl;
}
void Receptor::encolar(char * mensajeUtil, long id, int tamano){
    
}
