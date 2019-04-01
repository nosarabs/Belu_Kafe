#include "Buzon.h"

int main(){
    
    Buzon buzon;
    //el id para que reciba mensaje de tipo 1
    buzon.recibir_Mensaje(1);
    //que envie mensaje de tipo 2 al proceso 1
    buzon.enviar_Mensaje(2,"Hola proceso 1");
    buzon.recibir_Mensaje(1);
    return 0;
}
