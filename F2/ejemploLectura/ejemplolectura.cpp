#include <iostream>
#include <fstream>
using namespace std;


void clean_buffer(char * &buffer, size_t size){
    for(int index=0; index<size; ++index){
        buffer[index]=' ';
    }
}
//HAY QUE ESCRIBIR COMO ARGUMENTO LA DIRECCION DEL ARCHIVO 
int main(int argc, char * argv[]){
    
    size_t b_size = 512; 
    char *buffer = new char[b_size];
    ifstream fin(argv[1], ios::binary );
    ofstream destino("CopiaFoto.jpg",ios::binary);
    clean_buffer(buffer, b_size);
    while (fin)
    {
        // lee el segmento de información
        fin.read(buffer, b_size);
        // se obtienen los bytes que se leyeron
        size_t count = fin.gcount();
        cout<<"count: "<<count<<endl;
        // si no se leyó nada termina
        if (!count){
            break;
        }
        // se hace lo que se quiera con el buffer
        cout<<buffer<<endl;
        destino.write(buffer, count);//escribe en el archivo
        clean_buffer(buffer, b_size);
    }
    fin.close();
    destino.close();
    delete[] buffer;
        return 0;
}
