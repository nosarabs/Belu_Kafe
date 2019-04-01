#include "Buzon.h"

int main(){
    
    Buzon buzon;
    //el primer argumento hace referencia a que envio un mensaje de tipo1, o sea para el proceso 2
    buzon.enviar_Mensaje(1,"Hola proceso 2");
    //que reciba mensaje del proceso 2 
    buzon.recibir_Mensaje(2);
    buzon.enviar_Mensaje(1,"Hola de nuevo");
    return 0;
}
