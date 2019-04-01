#include "Lector.h" 

int main(int argc, char *argv[]){
    Lector lector;
    if(argc>1){
        int pude= lector.obtenerDirectorio(argv[1]);
    }else
        cout<<"Debe ingresar un directorio como argumento en linea de comandos";
}
