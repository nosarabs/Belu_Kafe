#include "Contratista.h"

Contratista::Contratista(char * archivo, int id){
    this->archivo = archivo;
    this->id = id;
    this->buzonC=new Buzon();
}

Contratista::~Contratista(){

}

void Contratista::leerArchivo(){
    //Señal para el emisor de que se creo un contratista
    strcpy(this->buzonC->un_Mensaje.mensaje,"");
    buzonC->enviar_Mensaje(201+this->id,this->buzonC->un_Mensaje.mensaje); 
    //Recibimos señal de emisor de que creó archivo para sincronización
    this->buzonC->recibir_Mensaje(100+this->id); 
    
    size_t b_size = 512;
    char * buffer = new char[b_size];
    int file = open(this->archivo, O_RDONLY);
    clean_buffer(buffer, b_size);
    //Mientras haya bytes, lee 512B y envía a particionar
    while (count = read(file, buffer, b_size)){
        particionarArchivo(buffer, count);
    }

    //Señal para el emisor de que terminó archivo
    strcpy(this->buzonC->un_Mensaje.mensaje,"FIN");
    this->buzonC->enviar_Mensaje(this->id, this->buzonC->un_Mensaje.mensaje); 
     //Recibimos señal de emisor de que terminó escritura
    this->buzonC->recibir_Mensaje(90000+this->id);
    //Enviamos señal al lector de que terminamos proceso contratista
    strcpy(this->buzonC->un_Mensaje.mensaje,"");
    buzonC->enviar_Mensaje(9999, this->buzonC->un_Mensaje.mensaje); 
    delete[] buffer;
}


void Contratista::clean_buffer(char * &buffer, size_t size){
    for(int index=0; index<size; ++index){
        buffer[index]=' ';
    }
}

void Contratista::particionarArchivo(char * archivo, int count){
  size_t b_size = 128;
  char *buffer = new char[b_size];
  if(count == 512){
      for(int i=0; i<4;++i){
         memcpy((void *)buffer, (void *)archivo, b_size);
         buzonC->un_Mensaje.chunk_Num = b_size;
         empaquetar(buffer, b_size);
         archivo+=128;
      }
  }else{
      //Si quedan menos de 512 bytes por mandar
      while(count > 0){
         //Si quedan menos de 128 bytes por mandar
         if(count < 128){
            char * bufferPeq = new char[count];
            memcpy((void *)bufferPeq, (void *)archivo, count);
            buzonC->un_Mensaje.chunk_Num = count;
            empaquetar(bufferPeq, count);
            delete[] bufferPeq;
            count=0;
         }else{
            memcpy((void *)buffer, (void *)archivo, b_size);
            buzonC->un_Mensaje.chunk_Num = b_size;
            empaquetar(buffer, b_size);
            archivo+=128;
            count -= 128;
         }
      }
   }
  delete[] buffer;
}

void Contratista::empaquetar(char * archivo, int chunkNum){
  memcpy(this->buzonC->un_Mensaje.mensaje,archivo, chunkNum);
  this->buzonC->un_Mensaje.chunk_Num = chunkNum;
  enviarAlEmisor();
}

void Contratista::enviarAlEmisor(){
    buzonC->enviar_Mensaje(this->id,this->buzonC->un_Mensaje.mensaje);
}
