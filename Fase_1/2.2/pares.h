#include <ostream>
#include <string.h>

using namespace std;
class pares{
   public:
       string palabra;
       int cantidad;
      // Funciones miembro de la clase "pares"
    pares(string palabra, int cantidad){
            this->palabra=palabra;
            this->cantidad=cantidad;
    }
    
    ~pares(){

    }
    
    int cantidad_palabras(){
        int cantidad=0;
        int contador=0;
        while(palabra[contador]!='\0'){ //Mientras no lleguemos al final
            while(palabra[contador]==' '){ //Mientras haya espacios
                ++contador;
            }
            if(palabra[contador]!='\0'){ //Si no estamos al final de la hilera 
                ++cantidad; //+1 a la cantidad de palabras
                while(palabra[contador]!=' ' && palabra[contador]!='\0'){ //Mientras haya letras
                    contador++; //Nos saltamos el resto de la palabras
                }
            }
        }
        return cantidad;
    }
    
};
 
