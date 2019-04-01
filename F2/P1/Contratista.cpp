#include "Contratista.h"

Contratista::Contratista(char * archivo, int id){
    this->archivo = archivo;
    this->id = id;
}

Contratista::~Contratista(){
    
}

void Contratista::leerArchivo(){
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
  ifstream file(archivo, ios::binary );
  clean_buffer(buffer, b_size);
  while (file)
  {
      // lee el segmento de información
      file.read(buffer, b_size);
      // se obtienen los bytes que se leyeron
      size_t count = file.gcount();
      cout<<"count: "<<count<<endl;
      // si no se leyó nada termina
      if (!count){
          break;
      }
      // se hace lo que se quiera con el buffer
      cout<<buffer<<endl;
      //AQUII MANDA A EMPAQUETAR
      empaquetar(buffer,chunkNum);
      ++chunkNum;
      clean_buffer(buffer, b_size);
  }
  file.close();
  delete[] buffer;

}

void Contratista::empaquetar(char * archivo, int chunkNum){
  buzonC.un_Mensaje.id_Contratista= this->id;
  strcpy(buzonC.un_Mensaje.mensaje,archivo);
  buzonC.un_Mensaje.chunk_Num = chunkNum;
  enviarAlEmisor();
}

void Contratista::enviarAlEmisor(){
    buzonC.enviar_Mensaje(1); //un 1 como parametro porque los mensajes tipo 1 van a ser los que se envian de los contratistas
}
