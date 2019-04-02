#include "Contratista.h"

Contratista::Contratista(char * archivo, int id){
    this->archivo = archivo;
    this->id = id;
    buzonC=new Buzon();
}

Contratista::~Contratista(){

}

void Contratista::leerArchivo(){
    buzonC->enviar_Mensaje(10000,"listo Creado contratista"); //señal que se creo un contratista
    size_t b_size = 512;
    char * buffer = new char[b_size];
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
        particionarArchivo(buffer);

        clean_buffer(buffer, b_size);
    }
    file.close();
    buzonC->enviar_Mensaje(this->id, "FIN");
    buzonC->recibir_Mensaje(90000+this->id);
    buzonC->enviar_Mensaje(9999, "un contratista terminoo");
    delete buzonC;
    delete[] buffer;
}


void Contratista::clean_buffer(char * &buffer, size_t size){
    for(int index=0; index<size; ++index){
        buffer[index]=' ';
    }
}

void Contratista::particionarArchivo(char * archivo){
  int chunkNum = 0;
  size_t b_size = 128;
  char *buffer = new char[b_size];
  int actual=0;
  int siguiente=128;
  for(int i=0; i<4;++i){
      int index=0;
      for(int j=actual;j<siguiente;++j){
          buffer[index]=archivo[j];
          ++index;
        }
        empaquetar(buffer,chunkNum);
        ++chunkNum;
        clean_buffer(buffer, b_size);
        actual+=128;
        siguiente+=128;
    }
  //file.close();
  delete[] buffer;

}

void Contratista::empaquetar(char * archivo, int chunkNum){
  strcpy(buzonC->un_Mensaje.mensaje,archivo);
  buzonC->un_Mensaje.chunk_Num = chunkNum;
  if(archivo[127] == ' ' || archivo[127] == '\0'){
    buzonC->un_Mensaje.fin = true;
  }else{
    buzonC->un_Mensaje.fin = false;
  }
  enviarAlEmisor();
}

void Contratista::enviarAlEmisor(){
    buzonC->enviar_Mensaje(this->id,buzonC->un_Mensaje.mensaje); //un 1 como parametro porque los mensajes tipo 1 van a ser los que se envian de los contratistas
}
