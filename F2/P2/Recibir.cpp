#include "Receptor.h" 

int main(int argc, char *argv[]){
    Receptor * receptor= new Receptor();
    receptor->conectar();
    delete receptor;
}  
